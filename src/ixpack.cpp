// $Id$
// Author: John Wu <John.Wu@ACM.org>
// Copyright 2000-2008 the Regents of the University of California
//
// This file contains the implementation of the class ibis::pack.  It defines
// a two-level index where the coarse level is formed with cumulative ranges,
// but the lower level contains only the simple bins.
//
#if defined(_WIN32) && defined(_MSC_VER)
#pragma warning(disable:4786)	// some identifier longer than 256 characters
#endif
#include "ibin.h"
#include "part.h"
#include "column.h"
#include "resource.h"

#include <string>
//
// generate an ibis::pack from ibis::bin
ibis::pack::pack(const ibis::bin& rhs) {
    if (rhs.col == 0) return;
    if (rhs.nobs <= 1) return; // rhs does not contain an valid index
    col = rhs.col;

    try {
	// decide how many corase and fine bins to use
	uint32_t nbins = rhs.nobs - 2, i, j, k;
	const char* spec = col->indexSpec();
	if (strstr(spec, "nrefine=") != 0) {
	    // number of fine bins per coarse bin
	    const char* tmp = 8+strstr(spec, "nrefine=");
	    i = atoi(tmp);
	    if (i > 1)
		j = (nbins > i ? (nbins+i-1)/i : nbins);
	    else
		j = (nbins > 16 ? 16 : nbins);
	}
	else if (strstr(spec, "ncoarse=") != 0) { // number of coarse bins
	    const char* tmp = 8+strstr(spec, "ncoarse=");
	    j = atoi(tmp);
	    if (j <= 2)
		j = (nbins > 16 ? 16 : nbins);
	}
	else { // default -- 16 coarse bins
	    if (nbins > 31) {
		j = 16;
	    }
	    else {
		j = nbins;
	    }
	}

	// partition boundaries so that each part has the same total bytes
	// of compressed bitvectors.
	// NOTE: parts must be initialized to j+1 to allow for the correct
	// handling of two overflow bins!
	std::vector<unsigned> parts(j+1);
	divideBitmaps(rhs.bits, parts);

	// prepare the arrays
	nobs = j + 1;
	nrows = rhs.nrows;
	sub.resize(nobs);
	bits.resize(nobs);
	bounds.resize(nobs);
	maxval.resize(nobs);
	minval.resize(nobs);
	max1 = rhs.maxval.back();
	min1 = rhs.minval.back();
	if (nobs+1 < rhs.nobs) {
	    sub.resize(nobs);
	    for (i=0; i<nobs; ++i) sub[i] = 0;
	}
	else {
	    sub.clear();
	}
	LOGGER(3) << "ibis::pack::ctor starting to convert " << rhs.nobs
		  << " bitvectors into " << nobs << " coarse bins";

	// copy the first bin, it never has a subrange.
	bounds[0] = rhs.bounds[0];
	maxval[0] = rhs.maxval[0];
	minval[0] = rhs.minval[0];
	bits[0] = new ibis::bitvector;
	bits[0]->copy(*(rhs.bits[0]));

	// copy the majority of bins
	if (nobs+1 < rhs.nobs) { // two levels
	    k = 1;
	    for (i = 1; i < nobs; ++i) {
		uint32_t nbi = parts[i] - parts[i-1];
		if (nbi > 1) {
		    sub[i] = new ibis::bin;
		    sub[i]->col = col;
		    sub[i]->nobs = nbi;
		    sub[i]->nrows = nrows;
		    sub[i]->bits.resize(nbi);
		    for (unsigned ii = 0; ii < nbi-1; ++ ii)
			sub[i]->bits[ii] = 0;
		    sub[i]->bounds.resize(nbi);
		    sub[i]->maxval.resize(nbi);
		    sub[i]->minval.resize(nbi);

		    // copy the first bin
		    sub[i]->bounds[0] = rhs.bounds[k];
		    sub[i]->maxval[0] = rhs.maxval[k];
		    sub[i]->minval[0] = rhs.minval[k];
		    sub[i]->bits[0] = new ibis::bitvector;
		    sub[i]->bits[0]->copy(*(rhs.bits[k]));
		    bits[i] = *(bits[i-1]) | *(rhs.bits[k]);
		    minval[i] = rhs.minval[k];
		    maxval[i] = rhs.maxval[k];
		    ++k;

		    // copy nbi-1 bins to the subrange
		    for (j = 1; j < nbi; ++j, ++k) {
			sub[i]->bounds[j] = rhs.bounds[k];
			sub[i]->maxval[j] = rhs.maxval[k];
			sub[i]->minval[j] = rhs.minval[k];
			sub[i]->bits[j] = new ibis::bitvector;
			sub[i]->bits[j]->copy(*(rhs.bits[k]));

			if (minval[i] > rhs.minval[k])
			    minval[i] = rhs.minval[k];
			if (maxval[i] < rhs.maxval[k])
			    maxval[i] = rhs.maxval[k];
			*(bits[i]) |= *(rhs.bits[k]);
		    }
		    bounds[i] = rhs.bounds[k-1];
		}
		else {
		    sub[i] = 0;
		    bounds[i] = rhs.bounds[k];
		    maxval[i] = rhs.maxval[k];
		    minval[i] = rhs.minval[k];
		    bits[i] = *(bits[i-1]) | *(rhs.bits[k]);
		    ++ k;
		}
	    }
	}
	else { // one level
	    for (i = 1; i < nobs; ++i) {
		bounds[i] = rhs.bounds[i];
		maxval[i] = rhs.maxval[i];
		minval[i] = rhs.minval[i];
		bits[i] = *(bits[i-1]) | *(rhs.bits[i]);
	    }
	}

	for (i = 0; i < nobs; ++ i)
	    if (bits[i])
		bits[i]->compress();
	if (ibis::gVerbose > 4) {
	    ibis::util::logger lg(4);
	    print(lg.buffer());
	}
    }
    catch (...) {
	clear();
	throw;
    }
} // copy from ibis::bin

//
// (de-serialization) reconstruct pack from content of a file
// In addition to the common content for index::bin, the following are
// inserted after minval array: (this constructor relies the fact that max1
// and min1 follow minval immediately without any separation or padding)
// max1 (double) -- the maximum value of all data entry
// min1 (double) -- the minimum value of those larger than or equal to the
// largest bounds value (bounds[nobs-1])
// offsets_for_next_level (uint32_t[nobs]) -- as the name suggests, these are
// the offsets (in this file) for the next level ibis::pack.
// after the bit vectors of this level are written, the next level ibis::pack
// are written without header.
ibis::pack::pack(const ibis::column* c, ibis::fileManager::storage* st,
		 uint32_t offset)
     : ibis::bin(c, st, offset), max1(*(minval.end())),
       min1(*(1+minval.end())) {
    try {
	array_t<int32_t>
	    offs(st,
		 8*((offset+sizeof(int32_t)*(nobs+1)+2*sizeof(uint32_t)+7)/8)+
		 sizeof(double)*(nobs*3+2), nobs+1);
#ifdef DEBUG
	if (ibis::gVerbose > 5) {
	    ibis::util::logger lg(ibis::gVerbose);
	    lg.buffer() << "DEBUG  from ibis::pack::pack("
			<< col->partition()->name() << '.' << col->name()
			<< ", " << offset << ") -- offsets of subranges\n";
	    for (uint32_t i=0; i<=nobs; ++i)
		lg.buffer() << "offset[" << i << "] = " << offs[i] << "\n";
	}
#endif

	if (offs[nobs] > offs[0]) {
	    sub.resize(nobs);
	    for (uint32_t i=0; i<nobs; ++i) {
		if (offs[i+1] > offs[i]) {
		    sub[i] = new ibis::bin(c, st, offs[i]);
		}
		else {
		    sub[i] = 0;
		}
	    }
	}
	if (ibis::gVerbose > 4) {
	    ibis::util::logger lg;
	    print(lg.buffer());
	}
    }
    catch (...) {
	clear();
	throw;
    }
}

void ibis::pack::write(const char* dt) const {
    if (nobs <= 1) return;

    std::string fnm;
    indexFileName(dt, fnm);
    if (fname != 0 && fnm.compare(fname) == 0)
	return;

    int fdes = UnixOpen(fnm.c_str(), OPEN_WRITEONLY, OPEN_FILEMODE);
    if (fdes < 0) {
	col->logWarning("pack::write", "unable to open \"%s\" for write",
			fnm.c_str());
	return;
    }
#if defined(_WIN32) && defined(_MSC_VER)
    (void)_setmode(fdes, _O_BINARY);
#endif

    char header[] = "#IBIS\4\0\0";
    header[5] = (char)ibis::index::PACK;
    header[6] = (char)sizeof(int32_t);
    int32_t ierr = UnixWrite(fdes, header, 8);
    write(fdes); // wrtie recursively
#if _POSIX_FSYNC+0 > 0
    (void) fsync(fdes); // write to disk
#endif
    ierr = UnixClose(fdes);
} // ibis::pack::write

void ibis::pack::write(int fdes) const {
    const int32_t start = UnixSeek(fdes, 0, SEEK_CUR);
    if (start < 8) {
	ibis::util::logMessage("Warning", "ibis::pack::write call to UnixSeek"
			       "(%d, 0, SEEK_CUR) failed ... %s",
			       fdes, strerror(errno));
	return;
    }

    uint32_t i;
    array_t<int32_t> offs(nobs+1);
    // write out bit sequences of this level of the index
    int32_t ierr = UnixWrite(fdes, &nrows, sizeof(uint32_t));
    ierr = UnixWrite(fdes, &nobs, sizeof(uint32_t));
    ierr = UnixSeek(fdes,
		    ((start+sizeof(int32_t)*(nobs+1)+
		      2*sizeof(uint32_t)+7)/8)*8,
		    SEEK_SET);
    ierr = UnixWrite(fdes, bounds.begin(), sizeof(double)*nobs);
    ierr = UnixWrite(fdes, maxval.begin(), sizeof(double)*nobs);
    ierr = UnixWrite(fdes, minval.begin(), sizeof(double)*nobs);
    ierr = UnixWrite(fdes, &max1, sizeof(double));
    ierr = UnixWrite(fdes, &min1, sizeof(double));
    ierr = UnixSeek(fdes, sizeof(int32_t)*(nobs+1), SEEK_CUR);
    for (i = 0; i < nobs; ++i) {
	offs[i] = UnixSeek(fdes, 0, SEEK_CUR);
	bits[i]->write(fdes);
    }
    offs[nobs] = UnixSeek(fdes, 0, SEEK_CUR);
    ierr = UnixSeek(fdes, start+sizeof(uint32_t)*2, SEEK_SET);
    ierr = UnixWrite(fdes, offs.begin(), sizeof(int32_t)*(nobs+1));
    ierr = UnixSeek(fdes, offs[nobs], SEEK_SET); // move to the end

    // write the sub-ranges
    if (sub.size() == nobs) { // subrange defined
	for (i = 0; i < nobs; ++i) {
	    offs[i] = UnixSeek(fdes, 0, SEEK_CUR);
	    if (sub[i])
		sub[i]->write(fdes);
	}
	offs[nobs] = UnixSeek(fdes, 0, SEEK_CUR);
    }
    else { // subrange not defined
	offs[nobs] = UnixSeek(fdes, 0, SEEK_CUR);
	for (i = 0; i < nobs; ++i)
	    offs[i] = offs[nobs];
    }

    // write the offsets for the subranges
    ierr = UnixSeek(fdes,
		    8*((start+sizeof(int32_t)*(nobs+1)+
			2*sizeof(uint32_t)+7)/8)+
		    sizeof(double)*(nobs*3+2), SEEK_SET);
    ierr = UnixWrite(fdes, offs.begin(), sizeof(int32_t)*(nobs+1));
    ierr = UnixSeek(fdes, offs[nobs], SEEK_SET); // move to the end
#ifdef DEBUG
    if (ibis::gVerbose > 5) {
	ibis::util::logger lg(ibis::gVerbose);
	lg.buffer() << "DEBUG  from ibis::pack::write(" << col->name() << ", "
		    << start << ") -- offsets to the subranges\n";
	for (i=0; i<=nobs; ++i)
	    lg.buffer() << "offset[" << i << "] = " << offs[i] << "\n";
    }
#endif
} // ibis::pack::write

// read the content of a file
void ibis::pack::read(const char* f) {
    std::string fnm;
    indexFileName(f, fnm);

    int fdes = UnixOpen(fnm.c_str(), OPEN_READONLY);
    if (fdes < 0)
	return;

    char header[8];
#if defined(_WIN32) && defined(_MSC_VER)
    (void)_setmode(fdes, _O_BINARY);
#endif
    if (8 != UnixRead(fdes, static_cast<void*>(header), 8)) {
	UnixClose(fdes);
	return;
    }

    if (false == (header[0] == '#' && header[1] == 'I' &&
		  header[2] == 'B' && header[3] == 'I' &&
		  header[4] == 'S' &&
		  header[5] == static_cast<char>(ibis::index::PACK) &&
		  header[6] == static_cast<char>(sizeof(int32_t)) &&
		  header[7] == static_cast<char>(0))) {
	UnixClose(fdes);
	return;
    }

    clear(); // clear the existing content
    uint32_t begin, end;
    fname = ibis::util::strnewdup(fnm.c_str());

    // read nobs
    int ierr = UnixRead(fdes, static_cast<void*>(&nrows), sizeof(uint32_t));
    if (ierr < static_cast<int>(sizeof(uint32_t))) {
	UnixClose(fdes);
	nrows = 0;
	return;
    }
    ierr = UnixRead(fdes, static_cast<void*>(&nobs), sizeof(uint32_t));
    if (ierr < static_cast<int>(sizeof(uint32_t))) {
	UnixClose(fdes);
	nrows = 0;
	nobs = 0;
	return;
    }
    bool trymmap = false;
#if defined(HAS_FILE_MAP)
    trymmap = (nobs > ibis::fileManager::pageSize());
#endif
    begin = 8 + 2 * sizeof(uint32_t);
    end = begin + (nobs+1) * sizeof(int32_t);
    if (trymmap) {
	array_t<int32_t> tmp(fname, begin, end);
	offsets.swap(tmp);
    }
    else {
	array_t<int32_t> tmp(fdes, begin, end);
	offsets.swap(tmp);
    }

    // read bounds
    begin = 8 * ((sizeof(int32_t)*(nobs+1)+2*sizeof(uint32_t)+15)/8);
    end = begin + sizeof(double)*nobs;
    if (trymmap) {
	array_t<double> dbl(fname, begin, end);
	bounds.swap(dbl);
    }
    else {
	array_t<double> dbl(fdes, begin, end);
	bounds.swap(dbl);
    }

    // read maxval
    begin = end;
    end += sizeof(double) * nobs;
    if (trymmap) {
	array_t<double> dbl(fname, begin, end);
	maxval.swap(dbl);
    }
    else {
	array_t<double> dbl(fdes, begin, end);
	maxval.swap(dbl);
    }

    // read minval
    begin = end;
    end += sizeof(double) * nobs;
    if (trymmap) {
	array_t<double> dbl(fname, begin, end);
	minval.swap(dbl);
    }
    else {
	array_t<double> dbl(fdes, begin, end);
	minval.swap(dbl);
    }
    UnixSeek(fdes, end, SEEK_SET);
    ierr = UnixRead(fdes, static_cast<void*>(&max1), sizeof(double));
    if (ierr < static_cast<int>(sizeof(double))) {
	UnixClose(fdes);
	clear();
	return;
    }
    ierr = UnixRead(fdes, static_cast<void*>(&min1), sizeof(double));
    if (ierr < static_cast<int>(sizeof(double))) {
	UnixClose(fdes);
	clear();
	return;
    }

    begin = end + 2*sizeof(double);
    end += 2*sizeof(double) + (nobs+1)*sizeof(int32_t);
    array_t<int32_t> nextlevel;
    if (trymmap) {
	array_t<int32_t> tmp(fname, begin, end);
	nextlevel.swap(tmp);
    }
    else {
	array_t<int32_t> tmp(fdes, begin, end);
	nextlevel.swap(tmp);
    }
#if defined(DEBUG)
    if (ibis::gVerbose > 3) {
	ibis::util::logger lg(ibis::gVerbose);
	lg.buffer() << "DEBUG -- ibis::pack::read(";
	if (fname)
	    lg.buffer() << fname;
	else
	    lg.buffer() << fdes;
	lg.buffer() << ") got the starting positions of the fine levels\n";
	for (uint32_t i = 0; i <= nobs; ++ i)
	    lg.buffer() << "offset[" << i << "] = " << nextlevel[i] << "\n";
    }
#endif
    ibis::fileManager::instance().recordPages(0, end);

    // initialized bits with nil pointers
    for (uint32_t i = 0; i < bits.size(); ++i)
	delete bits[i];
    bits.resize(nobs);
#if defined(ALWAY_READ_BITVECTOR0)
    if (offsets[1] > offsets[0]) {
	array_t<ibis::bitvector::word_t> a0(fdes, offsets[0], offsets[1]);
	ibis::bitvector* tmp = new ibis::bitvector(a0);
	bits[0] = tmp;
#if defined(WAH_CHECK_SIZE)
	if (tmp->size() != nrows)
	    col->logWarning("readIndex", "the length (%lu) of "
			    "bitvector 0 (from \"%s\") "
			    "differs from nRows (%lu)",
			    static_cast<long unsigned>(tmp->size()),
			    fnm.c_str(),
			    static_cast<long unsigned>(nrows));
#else
	bits[0]->setSize(nrows);
#endif
    }
    else {
	bits[0] = new ibis::bitvector;
	bits[0]->set(0, nrows);
    }
#endif
    // dealing with next levels
    for (uint32_t i = 0; i < sub.size(); ++i)
	delete sub[i];
    if (nextlevel[0] > nextlevel[nobs]) {
	clear();
	if (ibis::gVerbose > 0) {
	    ibis::util::logger lg(ibis::gVerbose);
	    lg.buffer() << " Error *** ibis::pack::read(";
	    if (fname)
		lg.buffer() << fname;
	    else
		lg.buffer() << fdes;
	    lg.buffer() << ") internal error, offset[0](" << nextlevel[0]
			<< ") is expected to be no less than offset["
			<< nobs << "](" << nextlevel[nobs]
			<< "), but it is not";
	}
    }
    else if (nextlevel[0] == nextlevel[nobs]) {
	sub.clear();
    }
    else {
	sub.resize(nobs);
    }

    for (uint32_t i = 0; i < sub.size(); ++i) {
	if (nextlevel[i] < nextlevel[i+1]) {
	    sub[i] = new ibis::bin(0);
	    sub[i]->col = col;
	    sub[i]->read(fdes, nextlevel[i], fname);
	}
	else if (nextlevel[i] == nextlevel[i+1]) {
	    sub[i] = 0;
	}
	else {
	    if (ibis::gVerbose > -1) {
		ibis::util::logger lg(ibis::gVerbose);
		lg.buffer() << " Error *** ibis::pack::read(";
		if (fname)
		    lg.buffer() << fname;
		else
		    lg.buffer() << fdes;
		lg.buffer() << ") offset[" << i << "] (" << nextlevel[i]
			    << ") is expected to less or equal to offset["
			    << i+1 << "] (" << nextlevel[i+1]
			    << "), but it is not! Can not use the index file.";
	    }
	    UnixClose(fdes);
	    throw "ibis::zone::read bad offsets(nextlevel)";
	}
    }
    UnixClose(fdes);
    if (ibis::gVerbose > 7)
	col->logMessage("readIndex", "finished reading '%s' header from %s",
			name(), fname);
} // ibis::pack::read

void ibis::pack::read(ibis::fileManager::storage* st) {
    ibis::bin::read(st);
    max1 = *(minval.end());
    min1 = *(1+minval.end());

    array_t<int32_t> offs(st, 8*((sizeof(int32_t)*(nobs+1)+
				  sizeof(uint32_t)+15)/8)+
			  sizeof(double)*(nobs*3+2), nobs+1);
    for (uint32_t i = 0; i < sub.size(); ++i)
	delete sub[i];
    if (offs[0] > offs[nobs]) {
	clear();
	if (ibis::gVerbose > 0) {
	    ibis::util::logger lg(ibis::gVerbose);
	    lg.buffer() << " Error *** ibis::pack::read(";
	    if (st->unnamed())
		lg.buffer() << static_cast<void*>(st->begin());
	    else
		lg.buffer() << st->filename();
	    lg.buffer() << ") internal error, offset[0](" << offs[0]
			<< ") is expected to be no less than offset["
			<< nobs << "](" << offs[nobs] << "), but it is not";
	}
    }
    else if (offs[0] == offs[nobs]) {
	sub.clear();
    }
    else {
	sub.resize(nobs);
    }

    for (uint32_t i = 0; i < sub.size(); ++ i) {
	if (offs[i+1] > offs[i]) {
	    sub[i] = new ibis::bin(col, st, offs[i]);
	}
	else if (offs[i] == offs[i+1]) {
	    sub[i] = 0;
	}
	else {
	    if (ibis::gVerbose> -1) {
		ibis::util::logger lg(0);
		lg.buffer() << " Error *** ibis::pack::read(";
		if (st->filename())
		    lg.buffer() << st->filename();
		else
		    lg.buffer() << static_cast<const void*>(st->begin());
		lg.buffer() << ") offset[" << i << "] (" << offs[i]
			    << ") is expected to less or equal to offset["
			    << i+1 << "] (" << offs[i+1]
			    << "), but it is not! Can not use the index file.";
	    }
	    throw "ibis::pack::read bad offsets(nextlevel)";
	}
    }
} // ibis::pack::read

void ibis::pack::clear() {
    for (std::vector<ibis::bin*>::iterator it1 = sub.begin();
	 it1 != sub.end(); ++it1) {
	delete *it1;
    }
    sub.clear();
    ibis::bin::clear();
} // ibis::pack::clear

// fill with zero bits or truncate
void ibis::pack::adjustLength(uint32_t nr) {
    ibis::bin::adjustLength(nr); // the top level
    if (sub.size() == nobs) {
	for (std::vector<ibis::bin*>::iterator it = sub.begin();
	     it != sub.end(); ++it) {
	    if (*it)
		(*it)->adjustLength(nr);
	}
    }
    else {
	for (std::vector<ibis::bin*>::iterator it = sub.begin();
	     it != sub.end(); ++it) {
	    delete *it;
	}
	sub.clear();
    }
} // ibis::pack::adjustLength

void ibis::pack::binBoundaries(std::vector<double>& ret) const {
    ret.clear();
    if (sub.size() == nobs) {
	for (uint32_t i = 0; i < nobs; ++i) {
	    if (sub[i]) {
		for (uint32_t j = 0; j < sub[i]->nobs; ++j)
		    ret.push_back(sub[i]->bounds[j]);
	    }
	    else {
		ret.push_back(bounds[i]);
	    }
	}
    }
    else { // assume no sub intervals
	ret.resize(bounds.size());
	for (uint32_t i = 0; i < bounds.size(); ++ i)
	    ret[i] = bounds[i];
    }
} // ibis::pack::binBoundaries

void ibis::pack::binWeights(std::vector<uint32_t>& ret) const {
    ret.clear();
    ret.push_back(bits[0] ? bits[0]->cnt() : 0U);
    for (uint32_t i=1; i < nobs; ++i) {
	if (sub[i]) {
	    for (uint32_t j = 0; j < sub[i]->nobs; ++j)
		ret.push_back(sub[i]->bits[j]->cnt());
	}
	else {
	    ret.push_back(bits[i]->cnt());
	}
    }
} //ibis::pack::binWeights

// a simple function to test the speed of the bitvector operations
void ibis::pack::speedTest(std::ostream& out) const {
    if (nrows == 0) return;
    uint32_t i, nloops = 1000000000 / nrows;
    if (nloops < 2) nloops = 2;
    ibis::horometer timer;
    col->logMessage("pack::speedTest", "testing the speed of operator -");

    for (i = 0; i < nobs-1; ++i) {
	ibis::bitvector* tmp;
	tmp = *(bits[i+1]) - *(bits[i]);
	delete tmp;

	timer.start();
	for (uint32_t j=0; j<nloops; ++j) {
	    tmp = *(bits[i+1]) - *(bits[i]);
	    delete tmp;
	}
	timer.stop();
	{
	    ibis::util::ioLock lock;
	    out << bits[i]->size() << " "
		<< static_cast<double>(bits[i]->bytes() + bits[i+1]->bytes())
		* 4.0 / static_cast<double>(bits[i]->size()) << " "
		<< bits[i]->cnt() << " " << bits[i+1]->cnt() << " "
		<< timer.CPUTime() / nloops << "\n";
	}
    }
} // ibis::pack::speedTest

// the printing function
void ibis::pack::print(std::ostream& out) const {
    out << "index (binned range-equality code) for "
	<< col->partition()->name() << '.' << col->name()
	<< " contains " << nobs+1 << " coarse bins for "
	<< nrows << " objects \n";
    if (ibis::gVerbose > 4) { // the long format
	if (bits[0])
	    out << "0: " << bits[0]->cnt() << "\t(..., " << bounds[0]
		<< ")\t\t\t["<< minval[0] << ", " << maxval[0] << "]\n";
	uint32_t i, cnt = nrows;
	for (i = 1; i < nobs; ++i) {
	    if (bits[i] == 0) continue;
	    out << i << ": " << bits[i]->cnt() << "\t(..., " << bounds[i]
		<< ");\t" << bits[i]->cnt() - bits[i-1]->cnt() << "\t["
		<< bounds[i-1] << ", " << bounds[i] << ")\t[" << minval[i]
		<< ", " << maxval[i] << "]\n";
	    if (cnt != bits[i]->size())
		out << "Warning: bits[" << i << "] contains "
		    << bits[i]->size()
		    << " bits, but " << cnt << " are expected\n";
	    if (sub.size() == nobs && sub[i] && bits[i-1])
		sub[i]->print(out, bits[i]->cnt() - bits[i-1]->cnt(),
			      bounds[i-1], bounds[i]);
	}
	if (bits[nobs-1])
	    out << nobs << ": " << cnt << "\t(..., ...);\t"
		<< cnt-bits[nobs-1]->cnt() << "\t[" << bounds[nobs-1]
		<< ", ...)\t[" << min1 << ", " << max1 << "]\n";
    }
    else if (sub.size() == nobs) { // the short format -- with subranges
	out << "right end of bin, bin weight, bit vector size (bytes)\n";
	for (uint32_t i=0; i<nobs; ++i) {
	    if (bits[i] == 0) continue;
	    out.precision(12);
	    out << (maxval[i]!=-DBL_MAX?maxval[i]:bounds[i]) << ' '
		<< bits[i]->cnt() << ' ' << bits[i]->bytes() << "\n";
	    if (sub[i] && bits[i-1])
		sub[i]->print(out, bits[i]->cnt() - bits[i-1]->cnt(),
			      bounds[i-1], bounds[i]);
	}
    }
    else { // the short format -- without subranges
	out << "The three columns are (1) center of bin, (2) bin weight, "
	    "and (3) bit vector size (bytes)\n";
	for (uint32_t i=0; i<nobs; ++i) {
	    if (bits[i] && bits[i]->cnt()) {
		out.precision(12);
		out << 0.5*(minval[i]+maxval[i]) << '\t'
		    << bits[i]->cnt() << '\t' << bits[i]->bytes() << "\n";
	    }
	}
    }
    out << "\n";
} // ibis::pack::print

long ibis::pack::append(const char* dt, const char* df, uint32_t nnew) {
    std::string fnm = df;
    indexFileName(df, fnm);

    ibis::pack* bin0=0;
    ibis::fileManager::storage* st0=0;
    long ierr = ibis::fileManager::instance().getFile(fnm.c_str(), &st0);
    if (ierr == 0 && st0 != 0) {
	const char* header = st0->begin();
	if (header[0] == '#' && header[1] == 'I' && header[2] == 'B' &&
	    header[3] == 'I' && header[4] == 'S' &&
	    header[5] == ibis::index::PACK &&
	    header[7] == static_cast<char>(0)) {
	    bin0 = new ibis::pack(col, st0);
	}
	else {
	    if (ibis::gVerbose > 5)
		col->logMessage("pack::append", "file \"%s\" has unexecpted "
				"header -- it will be removed", fnm.c_str());
	    ibis::fileManager::instance().flushFile(fnm.c_str());
	    remove(fnm.c_str());
	}
    }
    if (bin0 == 0) {
	ibis::bin bin1(col, df, bounds);
	bin0 = new ibis::pack(bin1);
    }

    ierr = append(*bin0);
    delete bin0;
    if (ierr == 0) {
	write(dt); // write out the new content
	return nnew;
    }
    else {
	return ierr;
    }
} // ibis::pack::append

long ibis::pack::append(const ibis::pack& tail) {
    uint32_t i;
    if (tail.col != col) return -1;
    if (tail.nobs != nobs) return -2;
    if (tail.bits.empty()) return -3;
    if (tail.bits[0]->size() != tail.bits[1]->size()) return -4;
    for (i = 0; i < nobs; ++i)
	if (tail.bounds[i] != bounds[i]) return -5;

    array_t<double> max2, min2;
    std::vector<ibis::bitvector*> bin2;
    max2.resize(nobs);
    min2.resize(nobs);
    bin2.resize(nobs);
    activate();
    tail.activate();

    for (i = 0; i < nobs; ++i) {
	if (tail.maxval[i] > maxval[i])
	    max2[i] = tail.maxval[i];
	else
	    max2[i] = maxval[i];
	if (tail.minval[i] < minval[i])
	    min2[i] = tail.minval[i];
	else
	    min2[i] = minval[i];
	bin2[i] = new ibis::bitvector;
	bin2[i]->copy(*bits[i]);
	*bin2[i] += *(tail.bits[i]);
    }

    // replace the current content with the new one
    maxval.swap(max2);
    minval.swap(min2);
    bits.swap(bin2);
    nrows += tail.nrows;
    max1 = (max1<tail.max1?tail.max1:max1);
    min1 = (min1<tail.min1?tail.min1:min1);
    // clearup bin2
    for (i = 0; i < nobs; ++i)
	delete bin2[i];
    max2.clear();
    min2.clear();
    bin2.clear();

    if (sub.size() == nobs && tail.sub.size() == nobs) {
	long ierr = 0;
	for (i = 0; i < nobs; ++i) {
	    if (sub[i] != 0 && tail.sub[i] != 0) {
		ierr -= sub[i]->append(*(tail.sub[i]));
	    }
	    else if (sub[i] != 0 || tail.sub[i] != 0) {
		col->logWarning("pack::append", "index for the two subrange "
				"%lu must of nil at the same time",
				static_cast<long unsigned>(i));
		delete sub[i];
		sub[i] = 0;
	    }
	}
	if (ierr != 0) return ierr;
    }
    return 0;
} // ibis::pack::append

long ibis::pack::evaluate(const ibis::qContinuousRange& expr,
			  ibis::bitvector& lower) const {
    if (col == 0 || col->partition() == 0) return -1;
    ibis::bitvector tmp;
    estimate(expr, lower, tmp);
    if (tmp.size() == lower.size() && tmp.cnt() > lower.cnt()) {
	tmp -= lower;
	ibis::bitvector delta;
	col->partition()->doScan(expr, tmp, delta);
	if (delta.size() == lower.size() && delta.cnt() > 0)
	    lower |= delta;
    }
    return lower.cnt();
} // ibis::pack::evaluate

// compute the lower and upper bound of the hit vector for the range
// expression
void ibis::pack::estimate(const ibis::qContinuousRange& expr,
			  ibis::bitvector& lower,
			  ibis::bitvector& upper) const {
    if (bits.empty()) {
	lower.set(0, nrows);
	upper.clear();
	return;
    }

    // when used to decide the which bins to use on the finer level, the range
    // to be searched to assumed to be [lbound, rbound).
    double lbound=-DBL_MAX, rbound=DBL_MAX;
    // bins in the range of [hit0, hit1) are hits
    // bins in the range of [cand0, cand1) are candidates
    uint32_t cand0=0, hit0=0, hit1=0, cand1=0;
    uint32_t bin0 = (expr.leftOperator()!=ibis::qExpr::OP_UNDEFINED) ?
	locate(expr.leftBound()) : 0;
    uint32_t bin1 = (expr.rightOperator()!=ibis::qExpr::OP_UNDEFINED) ?
	locate(expr.rightBound()) : 0;
    switch (expr.leftOperator()) {
    default:
    case ibis::qExpr::OP_UNDEFINED:
	switch (expr.rightOperator()) {
	default:
	case ibis::qExpr::OP_UNDEFINED:
	    col->logWarning("pack::estimate", "operators for the range not "
			    "specified");
	    return;
	case ibis::qExpr::OP_LT:
	    rbound = expr.rightBound();
	    hit0 = 0;
	    cand0 = 0;
	    if (bin1 >= nobs) {
		if (expr.rightBound() > max1) {
		    hit1 = nobs + 1;
		    cand1 = nobs + 1;
		}
		else if (expr.rightBound() > min1) {
		    hit1 = nobs;
		    cand1 = nobs + 1;
		}
		else {
		    hit1 = nobs;
		    cand1 = nobs;
		}
	    }
	    else if (expr.rightBound() > maxval[bin1]) {
		hit1 = bin1 + 1;
		cand1 = bin1 + 1;
	    }
	    else if (expr.rightBound() <= minval[bin1]) {
		hit1 = bin1;
		cand1 = bin1;
	    }
	    else {
		hit1 = bin1;
		cand1 = bin1 + 1;
	    }
	    break;
	case ibis::qExpr::OP_LE:
	    rbound = ibis::util::incrDouble(expr.rightBound());
	    hit0 = 0;
	    cand0 = 0;
	    if (bin1 >= nobs) {
		if (expr.rightBound() >= max1) {
		    hit1 = nobs + 1;
		    cand1 = nobs + 1;
		}
		else if (expr.rightBound() >= min1) {
		    hit1 = nobs;
		    cand1 = nobs + 1;
		}
		else {
		    hit1 = nobs;
		    cand1 = nobs;
		}
	    }
	    else if (expr.rightBound() >= maxval[bin1]) {
		hit1 = bin1 + 1;
		cand1 = bin1 + 1;
	    }
	    else if (expr.rightBound() < minval[bin1]) {
		hit1 = bin1;
		cand1 = bin1;
	    }
	    else {
		hit1 = bin1;
		cand1 = bin1 + 1;
	    }
	    break;
	case ibis::qExpr::OP_GT:
	    lbound = ibis::util::incrDouble(expr.rightBound());
	    hit1 = nobs + 1;
	    cand1 = nobs + 1;
	    if (bin1 >= nobs) {
		if (expr.rightBound() >= max1) {
		    hit0 = nobs + 1;
		    cand0 = nobs + 1;
		}
		else if (expr.rightBound() >= min1) {
		    hit0 = nobs + 1;
		    cand0 = nobs;
		}
		else {
		    hit0 = nobs;
		    cand0 = nobs;
		}
	    }
	    else if (expr.rightBound() >= maxval[bin1]) {
		hit0 = bin1 + 1;
		cand0 = bin1 + 1;
	    }
	    else if (expr.rightBound() < minval[bin1]) {
		hit0 = bin1;
		cand0 = bin1;
	    }
	    else {
		hit0 = bin1 + 1;
		cand0 = bin1;
	    }
	    break;
	case ibis::qExpr::OP_GE:
	    lbound = expr.rightBound();
	    hit1 = nobs + 1;
	    cand1 = nobs + 1;
	    if (bin1 >= nobs) {
		if (expr.rightBound() > max1) {
		    hit0 = nobs + 1;
		    cand0 = nobs + 1;
		}
		else if (expr.rightBound() > min1) {
		    hit0 = nobs + 1;
		    cand0 = nobs;
		}
		else {
		    hit0 = nobs;
		    cand0 = nobs;
		}
	    }
	    else if (expr.rightBound() > maxval[bin1]) {
		hit0 = bin1 + 1;
		cand0 = bin1 + 1;
	    }
	    else if (expr.rightBound() >= minval[bin1]) {
		hit0 = bin1;
		cand0 = bin1;
	    }
	    else {
		hit0 = bin1 + 1;
		cand0 = bin1;
	    }
	    break;
	case ibis::qExpr::OP_EQ:
	    ibis::util::eq2range(expr.rightBound(), lbound, rbound);
	    if (bin1 >= nobs) {
		if (expr.rightBound() <= max1 &&
		    expr.rightBound() >= min1) {
		    hit0 = nobs; hit1 = nobs;
		    cand0 = nobs; cand1 = nobs + 1;
		    if (max1 == min1) hit1 = cand1;
		}
		else {
		    hit0 = hit1 = cand0 = cand1 = 0;
		}
	    }
	    else if (expr.rightBound() <= maxval[bin1] &&
		     expr.rightBound() >= minval[bin1]) {
		hit0 = bin1; hit1 = bin1;
		cand0 = bin1; cand1 = bin1 + 1;
		if (maxval[bin1] == minval[bin1]) hit1 = cand1;
	    }
	    else {
		hit0 = hit1 = cand0 = cand1 = 0;
	    }
	    break;
	} // switch (expr.rightOperator())
	break; // case ibis::qExpr::OP_UNDEFINED
    case ibis::qExpr::OP_LT:
	lbound = ibis::util::incrDouble(expr.leftBound());
	if (bin0 >= nobs) {
	    if (expr.leftBound() >= max1) {
		hit0 = nobs + 1;
		cand0 = nobs + 1;
	    }
	    else if (expr.leftBound() >= min1) {
		hit0 = nobs + 1;
		cand0 = nobs;
	    }
	    else {
		hit0 = nobs;
		cand0 = nobs;
	    }
	}
	else if (expr.leftBound() >= maxval[bin0]) {
	    hit0 = bin0 + 1;
	    cand0 = bin0 + 1;
	}
	else if (expr.leftBound() < minval[bin0]) {
	    hit0 = bin0;
	    cand0 = bin0;
	}
	else {
	    hit0 = bin0 + 1;
	    cand0 = bin0;
	}
	switch (expr.rightOperator()) {
	default:
	case ibis::qExpr::OP_UNDEFINED:
	    hit1 = nobs + 1;
	    cand1 = nobs + 1;
	    break;
	case ibis::qExpr::OP_LT:
	    rbound = expr.rightBound();
	    if (bin1 >= nobs) {
		if (expr.rightBound() > max1) {
		    hit1 = nobs + 1;
		    cand1 = nobs + 1;
		}
		else if (expr.rightBound() > min1) {
		    hit1 = nobs;
		    cand1 = nobs + 1;
		}
		else {
		    hit1 = nobs;
		    cand1 = nobs;
		}
	    }
	    else if (expr.rightBound() > maxval[bin1]) {
		hit1 = bin1 + 1;
		cand1 = bin1 + 1;
	    }
	    else if (expr.rightBound() <= minval[bin1]) {
		hit1 = bin1;
		cand1 = bin1;
	    }
	    else {
		hit1 = bin1;
		cand1 = bin1 + 1;
	    }
	    break;
	case ibis::qExpr::OP_LE:
	    rbound = ibis::util::incrDouble(expr.rightBound());
	    if (bin1 >= nobs) {
		if (expr.rightBound() >= max1) {
		    hit1 = nobs + 1;
		    cand1 = nobs + 1;
		}
		else if (expr.rightBound() >= min1) {
		    hit1 = nobs;
		    cand1 = nobs  + 1;
		}
		else {
		    hit1 = nobs;
		    cand1 = nobs;
		}
	    }
	    else if (expr.rightBound() >= maxval[bin1]) {
		hit1 = bin1 + 1;
		cand1 = bin1 + 1;
	    }
	    else if (expr.rightBound() < minval[bin1]) {
		hit1 = bin1;
		cand1 = bin1;
	    }
	    else {
		hit1 = bin1;
		cand1 = bin1 + 1;
	    }
	    break;
	case ibis::qExpr::OP_GT:
	    if (lbound <= expr.rightBound())
		lbound = ibis::util::incrDouble(expr.rightBound());
	    hit1 = nobs + 1;
	    cand1 = nobs + 1;
	    if (expr.rightBound() > expr.leftBound()) {
		if (bin1 >= nobs) {
		    if (expr.rightBound() >= max1) {
			hit0 = nobs + 1;
			cand0 = nobs + 1;
		    }
		    else if (expr.rightBound() >= min1) {
			hit0 = nobs + 1;
			cand0 = nobs;
		    }
		    else {
			hit0 = nobs;
			cand0 = nobs;
		    }
		}
		else if (expr.rightBound() >= maxval[bin1]) {
		    hit0 = bin1 + 1;
		    cand0 = bin1 + 1;
		}
		else if (expr.rightBound() < minval[bin1]) {
		    hit0 = bin1;
		    cand0 = bin1;
		}
		else {
		    hit0 = bin1 + 1;
		    cand0 = bin1;
		}
	    }
	    break;
	case ibis::qExpr::OP_GE:
	    hit1 = nobs + 1;
	    cand1 = nobs + 1;
	    if (expr.rightBound() > expr.leftBound()) {
		lbound = expr.rightBound();
		if (bin1 >= nobs) {
		    if (expr.rightBound() > max1) {
			hit0 = nobs + 1;
			cand0 = nobs + 1;
		    }
		    else if (expr.rightBound() > min1) {
			hit0 = nobs + 1;
			cand0 = nobs;
		    }
		    else {
			hit0 = nobs;
			cand0 = nobs;
		    }
		}
		else if (expr.rightBound() > maxval[bin1]) {
		    hit0 = bin1 + 1;
		    cand0 = bin1 + 1;
		}
		else if (expr.rightBound() >= minval[bin1]) {
		    hit0 = bin1;
		    cand0 = bin1;
		}
		else {
		    hit0 = bin1 + 1;
		    cand0 = bin1;
		}
	    }
	    break;
	case ibis::qExpr::OP_EQ:
	    ibis::util::eq2range(expr.rightBound(), lbound, rbound);
	    if (expr.rightBound() < expr.leftBound()) {
		if (bin1 >= nobs) {
		    if (expr.rightBound() <= max1 &&
			expr.rightBound() >= min1) {
			hit0 = nobs; hit1 = nobs;
			cand0 = nobs; cand1 = nobs + 1;
			if (max1 == min1) hit1 = cand1;
		    }
		    else {
			hit0 = hit1 = cand0 = cand1 = 0;
		    }
		}
		else if (expr.rightBound() <= maxval[bin1] &&
			 expr.rightBound() >= maxval[bin1]) {
		    hit0 = bin1; hit1 = bin1;
		    cand0 = bin1; cand1 = bin1 + 1;
		    if (maxval[bin1] == minval[bin1]) hit1 = cand1;
		}
		else {
		    hit0 = hit1 = cand0 = cand1 = 0;
		}
	    }
	    else {
		hit0 = hit1 = cand0 = cand1 = 0;
	    }
	    break;
	} // switch (expr.rightOperator())
	break; // case ibis::qExpr::OP_LT
    case ibis::qExpr::OP_LE:
	lbound = expr.leftBound();
	if (bin0 >= nobs) {
	    if (expr.leftBound() > max1) {
		hit0 = nobs + 1;
		cand0 = nobs + 1;
	    }
	    else if (expr.leftBound() > min1) {
		hit0 = nobs + 1;
		cand0 = nobs;
	    }
	    else {
		hit0 = nobs;
		cand0 = nobs;
	    }
	}
	else if (expr.leftBound() > maxval[bin0]) {
	    hit0 = bin0 + 1;
	    cand0 = bin0 + 1;
	}
	else if (expr.leftBound() <= minval[bin0]) {
	    hit0 = bin0;
	    cand0 = bin0;
	}
	else {
	    hit0 = bin0 + 1;
	    cand0 = bin0;
	}
	switch (expr.rightOperator()) {
	default:
	case ibis::qExpr::OP_UNDEFINED:
	    hit1 = nobs + 1;
	    cand1 = nobs + 1;
	    break;
	case ibis::qExpr::OP_LT:
	    rbound = expr.rightBound();
	    if (bin1 >= nobs) {
		if (expr.rightBound() > max1) {
		    hit1 = nobs + 1;
		    cand1 = nobs + 1;
		}
		else if (expr.rightBound() > min1) {
		    hit1 = nobs;
		    cand1 = nobs + 1;
		}
		else {
		    hit1 = nobs;
		    cand1 = nobs;
		}
	    }
	    else if (expr.rightBound() > maxval[bin1]) {
		hit1 = bin1 + 1;
		cand1 = bin1 + 1;
	    }
	    else if (expr.rightBound() <= minval[bin1]) {
		hit1 = bin1;
		cand1 = bin1;
	    }
	    else {
		hit1 = bin1;
		cand1 = bin1 + 1;
	    }
	    break;
	case ibis::qExpr::OP_LE:
	    rbound = ibis::util::incrDouble(expr.rightBound());
	    if (bin1 > nobs) {
		hit1 = nobs;
		cand1 = nobs;
	    }
	    else if (expr.rightBound() >= maxval[bin1]) {
		hit1 = bin1 + 1;
		cand1 = bin1 + 1;
	    }
	    else if (expr.rightBound() < minval[bin1]) {
		hit1 = bin1;
		cand1 = bin1;
	    }
	    else {
		hit1 = bin1;
		cand1 = bin1 + 1;
	    }
	    break;
	case ibis::qExpr::OP_GT:
	    hit1 = nobs + 1;
	    cand1 = nobs + 1;
	    if (expr.rightBound() >= expr.leftBound()) {
		lbound = ibis::util::incrDouble(expr.rightBound());
		if (bin1 >= nobs) {
		    if (expr.rightBound() >= max1) {
			hit0 = nobs + 1;
			cand0 = nobs + 1;
		    }
		    else if (expr.rightBound() >= min1) {
			hit0 = nobs + 1;
			cand0 = nobs;
		    }
		    else {
			hit0 = nobs;
			cand0 = nobs;
		    }
		}
		else if (expr.rightBound() >= maxval[bin1]) {
		    hit0 = bin1 + 1;
		    cand0 = bin1 + 1;
		}
		else if (expr.rightBound() < minval[bin1]) {
		    hit0 = bin1;
		    cand0 = bin1;
		}
		else {
		    hit0 = bin1 + 1;
		    cand0 = bin1;
		}
	    }
	    break;
	case ibis::qExpr::OP_GE:
	    if (lbound < expr.rightBound())
		lbound = expr.rightBound();
	    hit1 = nobs + 1;
	    cand1 = nobs + 1;
	    if (expr.rightBound() > expr.leftBound()) {
		if (bin1 >= nobs) {
		    if (expr.rightBound() > max1) {
			hit0 = nobs + 1;
			cand0 = nobs + 1;
		    }
		    else if (expr.rightBound() > min1) {
			hit0 = nobs + 1;
			cand0 = nobs;
		    }
		    else {
			hit0 = nobs;
			cand0 = nobs;
		    }
		}
		else if (expr.rightBound() > maxval[bin1]) {
		    hit0 = bin1 + 1;
		    cand0 = bin1 + 1;
		}
		else if (expr.rightBound() <= minval[bin1]) {
		    hit0 = bin1;
		    cand0 = bin1;
		}
		else {
		    hit0 = bin1 + 1;
		    cand0 = bin1;
		}
	    }
	    break;
	case ibis::qExpr::OP_EQ:
	    ibis::util::eq2range(expr.rightBound(), lbound, rbound);
	    if (expr.rightBound() <= expr.leftBound()) {
		if (bin1 >= nobs) {
		    if (expr.rightBound() <= max1 &&
			expr.rightBound() >= min1) {
			hit0 = nobs; hit1 = nobs;
			cand0 = nobs; cand1 = nobs + 1;
			if (max1 == min1) hit1 = cand1;
		    }
		    else {
			hit0 = hit1 = cand0 = cand1 = 1;
		    }
		}
		else if (expr.rightBound() <= maxval[bin1] &&
			 expr.rightBound() >= minval[bin1]) {
		    hit0 = bin1; hit1 = bin1;
		    cand0 = bin1; cand1 = bin1 + 1;
		    if (maxval[bin1] == minval[bin1]) hit1 = cand1;
		}
		else {
		    hit0 = hit1 = cand0 = cand1 = 0;
		}
	    }
	    else {
		hit0 = hit1 = cand0 = cand1 = 0;
	    }
	    break;
	} // switch (expr.rightOperator())
	break; // case ibis::qExpr::OP_LE
    case ibis::qExpr::OP_GT:
	rbound = expr.leftBound();
	if (bin0 >= nobs) {
	    if (expr.rightBound() > max1) {
		hit1 = nobs + 1;
		cand1 = nobs + 1;
	    }
	    else if (expr.rightBound() > min1) {
		hit1 = nobs;
		cand1 = nobs + 1;
	    }
	    else {
		hit1 = nobs;
		cand1 = nobs;
	    }
	}
	else if (expr.leftBound() > maxval[bin0]) {
	    hit1 = bin0 + 1;
	    cand1 = bin0 + 1;
	}
	else if (expr.leftBound() <= minval[bin0]) {
	    hit1 = bin0;
	    cand1 = bin0;
	}
	else {
	    hit1 = bin0;
	    cand1 = bin0 + 1;
	}
	switch (expr.rightOperator()) {
	default:
	case ibis::qExpr::OP_UNDEFINED:
	    cand0 = 0; hit0 = 0;
	    break;
	case ibis::qExpr::OP_LT:
	    if (rbound > expr.rightBound()) rbound = expr.rightBound();
	    hit0 = 0;
	    cand0 = 0;
	    if (bin1 < bin0) {
		if (expr.rightBound() > maxval[bin1]) {
		    hit1 = bin1 + 1;
		    cand1 = bin1 + 1;
		}
		else if (expr.rightBound() <= minval[bin1]) {
		    hit1 = bin1;
		    cand1 = bin1;
		}
		else {
		    hit1 = bin1;
		    cand1 = bin1 + 1;
		}
	    }
	    break;
	case ibis::qExpr::OP_LE:
	    hit0 = 0;
	    cand0 = 0;
	    if (expr.rightBound() < expr.leftBound()) {
		rbound = ibis::util::incrDouble(expr.rightBound());
		if (bin1 >= nobs) {
		    if (expr.rightBound() >= max1) {
			hit1 = nobs + 1;
			cand1 = nobs + 1;
		    }
		    else if (expr.rightBound() >= min1) {
			hit1 = nobs;
			cand1 = nobs + 1;
		    }
		    else {
			hit1 = nobs;
			cand1 = nobs;
		    }
		}
		else if (expr.rightBound() >= maxval[bin1]) {
		    hit1 = bin1 + 1;
		    cand1 = bin1 + 1;
		}
		else if (expr.rightBound() < minval[bin1]) {
		    hit1 = bin1;
		    cand1 = bin1;
		}
		else {
		    hit1 = bin1;
		    cand1 = bin1 + 1;
		}
	    }
	    break;
	case ibis::qExpr::OP_GT:
	    lbound = ibis::util::incrDouble(expr.rightBound());
	    if (bin1 >= nobs) {
		if (expr.rightBound() >= max1) {
		    hit0 = nobs + 1;
		    cand0 = nobs + 1;
		}
		else if (expr.rightBound() >= min1) {
		    hit0 = nobs + 1;
		    cand0 = nobs;
		}
		else {
		    hit0 = nobs;
		    cand0 = nobs;
		}
	    }
	    else if (expr.rightBound() >= maxval[bin1]) {
		hit0 = bin1 + 1;
		cand0 = bin1 + 1;
	    }
	    else if (expr.rightBound() < minval[bin1]) {
		hit0 = bin1;
		cand0 = bin1;
	    }
	    else {
		hit0 = bin1 + 1;
		cand0 = bin1;
	    }
	    break;
	case ibis::qExpr::OP_GE:
	    lbound = expr.rightBound();
	    if (bin1 >= nobs) {
		if (expr.rightBound() > max1) {
		    hit0 = nobs + 1;
		    cand0 = nobs + 1;
		}
		else if (expr.rightBound() > min1) {
		    hit0 = nobs + 1;
		    cand0 = nobs;
		}
		else {
		    hit0 = nobs;
		    cand0 = nobs;
		}
	    }
	    else if (expr.rightBound() > maxval[bin1]) {
		hit0 = bin1 + 1;
		cand0 = bin1 + 1;
	    }
	    else if (expr.rightBound() <= minval[bin1]) {
		hit0 = bin1;
		cand0 = bin1;
	    }
	    else {
		hit0 = bin1 + 1;
		cand0 = bin1;
	    }
	    break;
	case ibis::qExpr::OP_EQ:
	    ibis::util::eq2range(expr.rightBound(), lbound, rbound);
	    if (expr.rightBound() < expr.leftBound()) {
		if (bin1 >= nobs) {
		    if (expr.rightBound() <= max1 &&
			expr.rightBound() >= min1) {
			hit0 = nobs; hit1 = nobs;
			cand0 = nobs; cand1 = nobs + 1;
			if (max1 == min1) hit1 = cand1;
		    }
		    else {
			hit0 = hit1 = cand0 = cand1 = 0;
		    }
		}
		else if (expr.rightBound() <= maxval[bin1] &&
			 expr.rightBound() >= minval[bin1]) {
		    hit0 = bin1; hit1 = bin1;
		    cand0 = bin1; cand1 = bin1 + 1;
		    if (maxval[bin1] == minval[bin1]) hit1 = cand1;
		}
		else {
		    hit0 = hit1 = cand0 = cand1 = 0;
		}
	    }
	    else {
		hit0 = hit1 = cand0 = cand1 = 0;
	    }
	    break;
	} // switch (expr.rightOperator())
	break; // case ibis::qExpr::OP_GT
    case ibis::qExpr::OP_GE:
	rbound = ibis::util::incrDouble(expr.leftBound());
	if (bin0 >= nobs) {
	    if (expr.leftBound() > max1) {
		hit1 = nobs + 1;
		cand1 = nobs + 1;
	    }
	    else if (expr.leftBound() > min1) {
		hit1 = nobs;
		cand1 = nobs + 1;
	    }
	    else {
		hit1 = nobs;
		cand1 = nobs;
	    }
	}
	else if (expr.leftBound() > maxval[bin0]) {
	    hit1 = bin0 + 1;
	    cand1 = bin0 + 1;
	}
	else if (expr.leftBound() <= minval[bin0]) {
	    hit1 = bin0;
	    cand1 = bin0;
	}
	else {
	    hit1 = bin0;
	    cand1 = bin0 + 1;
	}
	switch (expr.rightOperator()) {
	default:
	case ibis::qExpr::OP_UNDEFINED:
	    hit0 = 0; cand0 = 0;
	    break;
	case ibis::qExpr::OP_LT:
	    hit0 = 0;
	    cand0 = 0;
	    if (expr.rightBound() < expr.leftBound()) {
		rbound = expr.rightBound();
		if (bin1 >= nobs) {
		    if (expr.rightBound() > max1) {
			hit1 = nobs + 1;
			cand1 = nobs + 1;
		    }
		    else if (expr.rightBound() > min1) {
			hit1 = nobs;
			cand1 = nobs + 1;
		    }
		    else {
			hit1 = nobs;
			cand1 = nobs;
		    }
		}
		else if (expr.rightBound() > maxval[bin1]) {
		    hit1 = bin1 + 1;
		    cand1 = bin1 + 1;
		}
		else if (expr.rightBound() <= minval[bin1]) {
		    hit1 = bin1;
		    cand1 = bin1;
		}
		else {
		    hit1 = bin1;
		    cand1 = bin1 + 1;
		}
	    }
	    break;
	case ibis::qExpr::OP_LE:
	    if (rbound > expr.rightBound())
		rbound = ibis::util::incrDouble(expr.rightBound());
	    hit0 = 0;
	    cand0 = 0;
	    if (bin1 < bin0) {
		if (expr.rightBound() >= maxval[bin1]) {
		    hit1 = bin1 + 1;
		    cand1 = bin1 + 1;
		}
		else if (expr.rightBound() < minval[bin1]) {
		    hit1 = bin1;
		    cand1 = bin1;
		}
		else {
		    hit1 = bin1;
		    cand1 = bin1 + 1;
		}
	    }
	    break;
	case ibis::qExpr::OP_GT:
	    lbound = ibis::util::incrDouble(expr.rightBound());
	    if (bin1 >= nobs) {
		if (expr.rightBound() > max1) {
		    hit0 = nobs + 1;
		    cand0 = nobs + 1;
		}
		else if (expr.rightBound() > min1) {
		    hit0 = nobs + 1;
		    cand0 = nobs;
		}
		else {
		    hit0 = nobs;
		    cand0 = nobs;
		}
	    }
	    else if (expr.rightBound() >= maxval[bin1]) {
		hit0 = bin1 + 1;
		cand0 = bin1 + 1;
	    }
	    else if (expr.rightBound() < minval[bin1]) {
		hit0 = bin1;
		cand0 = bin1;
	    }
	    else {
		hit0 = bin1 + 1;
		cand0 = bin1;
	    }
	    break;
	case ibis::qExpr::OP_GE:
	    lbound = expr.rightBound();
	    if (bin1 >= nobs) {
		if (expr.rightBound() > max1) {
		    hit0 = nobs + 1;
		    cand0 = nobs + 1;
		}
		else if (expr.rightBound() > min1) {
		    hit0 = nobs + 1;
		    cand0 = nobs;
		}
		else {
		    hit0 = nobs;
		    cand0 = nobs;
		}
	    }
	    else if (expr.rightBound() > maxval[bin1]) {
		hit0 = bin1 + 1;
		cand0 = bin1 + 1;
	    }
	    else if (expr.rightBound() <= minval[bin1]) {
		hit0 = bin1;
		cand0 = bin1;
	    }
	    else {
		hit0 = bin1 + 1;
		cand0 = bin1;
	    }
	    break;
	case ibis::qExpr::OP_EQ:
	    ibis::util::eq2range(expr.rightBound(), lbound, rbound);
	    if (expr.rightBound() <= expr.leftBound()) {
		if (bin1 >= nobs) {
		    if (expr.rightBound() <= max1 &&
			expr.rightBound() >= min1) {
			hit0 = nobs; hit1 = nobs;
			cand0 = nobs; cand1 = nobs + 1;
			if (max1 == min1) hit1 = cand1;
		    }
		    else {
			hit0 = hit1 = cand0 = cand1 = 0;
		    }
		}
		else if (expr.rightBound() <= maxval[bin1] &&
			 expr.rightBound() >= minval[bin1]) {
		    hit0 = bin1; hit1 = bin1;
		    cand0 = bin1; cand1 = bin1 + 1;
		    if (maxval[bin1] == minval[bin1]) hit1 = cand1;
		}
		else {
		    hit0 = hit1 = cand0 = cand1 = 0;
		}
	    }
	    else {
		hit0 = hit1 = cand0 = cand1 = 0;
	    }
	    break;
	} // switch (expr.rightOperator())
	break; // case ibis::qExpr::OP_GE
    case ibis::qExpr::OP_EQ:
	ibis::util::eq2range(expr.leftBound(),lbound, rbound);
	switch (expr.rightOperator()) {
	default:
	case ibis::qExpr::OP_UNDEFINED:
	    if (bin0 >= nobs) {
		if (expr.leftBound() <= max1 &&
		    expr.leftBound() >= min1) {
		    hit0 = nobs; hit1 = nobs;
		    cand0 = nobs; cand1 = nobs + 1;
		    if (max1 == min1) hit1 = cand1;
		}
		else {
		    hit0 = hit1 = cand0 = cand1 = 0;
		}
	    }
	    else if (expr.leftBound() <= maxval[bin0] &&
		     expr.leftBound() >= minval[bin0]) {
		hit0 = bin0; hit1 = bin0;
		cand0 = bin0; cand1 = bin0 + 1;
		if (maxval[bin0] == minval[bin0]) hit1 = cand1;
	    }
	    else {
		hit0 = hit1 = cand0 = cand1 = 0;
	    }
	    break;
	case ibis::qExpr::OP_LT:
	    if (expr.leftBound() < expr.rightBound()) {
		if (bin1 >= nobs) {
		    if (expr.leftBound() <= max1 &&
			expr.leftBound() >= min1) {
			hit0 = nobs; hit1 = nobs;
			cand0 = nobs; cand1 = nobs + 1;
			if (max1 == min1) hit1 = cand1;
		    }
		    else {
			hit0 = hit1 = cand0 = cand1 = 0;
		    }
		}
		else if (expr.leftBound() <= maxval[bin0] &&
			 expr.leftBound() >= minval[bin0]) {
		    hit0 = bin0; hit1 = bin0;
		    cand0 = bin0; cand1 = bin0 + 1;
		    if (maxval[bin0] == minval[bin0]) hit1 = cand1;
		}
		else {
		    hit0 = hit1 = cand0 = cand1 = 0;
		}
	    }
	    else {
		hit0 = hit1 = cand0 = cand1 = 0;
	    }
	    break;
	case ibis::qExpr::OP_LE:
	    if (expr.leftBound() <= expr.rightBound()) {
		if (bin1 >= nobs) {
		    if (expr.leftBound() <= max1 &&
			expr.leftBound() >= min1) {
			hit0 = nobs; hit1 = nobs;
			cand0 = nobs; cand1 = nobs + 1;
			if (max1 == min1) hit1 = cand1;
		    }
		    else {
			hit0 = hit1 = cand0 = cand1 = 0;
		    }
		}
		else if (expr.leftBound() <= maxval[bin0] &&
			 expr.leftBound() >= maxval[bin0]) {
		    hit0 = bin0; hit1 = bin0;
		    cand0 = bin0; cand1 = bin0 + 1;
		    if (maxval[bin0] == minval[bin0]) hit1 = cand1;
		}
		else {
		    hit0 = hit1 = cand0 = cand1 = 0;
		}
	    }
	    else {
		hit0 = hit1 = cand0 = cand1 = 0;
	    }
	    break;
	case ibis::qExpr::OP_GT:
	    if (expr.leftBound() > expr.rightBound()) {
		if (bin1 >= nobs) {
		    if (expr.leftBound() <= max1 &&
			expr.leftBound() >= min1) {
			hit0 = nobs; hit1 = nobs;
			cand0 = nobs; cand1 = nobs + 1;
			if (max1 == min1) hit1 = cand1;
		    }
		    else {
			hit0 = hit1 = cand0 = cand1 = 0;
		    }
		}
		else if (expr.leftBound() <= maxval[bin0] &&
			 expr.leftBound() >= maxval[bin0]) {
		    hit0 = bin0; hit1 = bin0;
		    cand0 = bin0; cand1 = bin0 + 1;
		    if (maxval[bin0] == minval[bin0]) hit1 = cand1;
		}
		else {
		    hit0 = hit1 = cand0 = cand1 = 0;
		}
	    }
	    else {
		hit0 = hit1 = cand0 = cand1 = 0;
	    }
	    break;
	case ibis::qExpr::OP_GE:
	    if (expr.leftBound() >= expr.rightBound()) {
		if (bin1 >= nobs) {
		    if (expr.leftBound() <= max1 &&
			expr.leftBound() >= min1) {
			hit0 = nobs; hit1 = nobs;
			cand0 = nobs; cand1 = nobs + 1;
			if (max1 == min1) hit1 = cand1;
		    }
		    else {
			hit0 = hit1 = cand0 = cand1 = 0;
		    }
		}
		else if (expr.leftBound() <= maxval[bin0] &&
			 expr.leftBound() >= minval[bin0]) {
		    hit0 = bin0; hit1 = bin0;
		    cand0 = bin0; cand1 = bin0 + 1;
		    if (maxval[bin0] == minval[bin0]) hit1 = cand1;
		}
		else {
		    hit0 = hit1 = cand0 = cand1 = 0;
		}
	    }
	    else {
		hit0 = hit1 = cand0 = cand1 = 0;
	    }
	    break;
	case ibis::qExpr::OP_EQ:
	    if (expr.leftBound() == expr.rightBound()) {
		if (bin1 >= nobs) {
		    if (expr.leftBound() >= min1 &&
			expr.leftBound() <= max1) {
			hit0 = nobs; hit1 = nobs;
			cand0 = nobs; cand1 = nobs + 1;
			if (max1 == min1) hit1 = cand1;
		    }
		    else {
			hit0 = hit1 = cand0 = cand1 = 0;
		    }
		}
		else if (expr.rightBound() <= maxval[bin1] &&
			 expr.rightBound() >= minval[bin1]) {
		    hit0 = bin1; hit1 = bin1;
		    cand0 = bin1; cand1 = bin1 + 1;
		    if (maxval[bin0] == minval[bin0]) hit1 = cand1;
		}
		else {
		    hit0 = hit1 = cand0 = cand1 = 0;
		}
	    }
	    else {
		hit0 = hit1 = cand0 = cand1 = 0;
	    }
	    break;
	} // switch (expr.rightOperator())
	break; // case ibis::qExpr::OP_EQ
    } // switch (expr.leftOperator())
    LOGGER(6) << "ibis::pack::estimate(" << expr << ") bin number ["
	      << cand0 << ":" << hit0 << ", " << hit1 << ":" << cand1
	      << ") boundaries ["
	      << (cand0 < bits.size() ?
		  (minval[cand0]<bounds[cand0] ? minval[cand0] :
		   bounds[cand0]) : min1)
	      << ":"
	      << (hit0 < bits.size() ?
		  (minval[hit0]<bounds[hit0] ? minval[hit0] :
		   bounds[hit0]) : max1)
	      << ", "
	      << (hit1 < bits.size() ?
		  (hit1>hit0 ? (maxval[hit1-1] < bounds[hit1-1] ?
				maxval[hit1-1] : bounds[hit1-1]) :
		   (minval[hit0]<bounds[hit0] ? minval[hit0] :
		    bounds[hit0])) : min1)
	      << ":"
	      << (cand1 >= bits.size() ? max1 :
		  (cand1>cand0 ? (maxval[cand1-1] < bounds[cand1-1] ?
				  maxval[cand1-1] : bounds[cand1-1]) :
		   (minval[cand0] < bounds[0] ? minval[cand0] :
		    bounds[0])))
	      << ")";

    uint32_t i, j;
    bool same = false; // are upper and lower the same ?
    // attempt to generate lower and upper bounds together
    if (cand0 == hit0 && cand1 == hit1) { // top level only
	if (hit0 >= hit1) {
	    lower.set(0, nrows);
	    upper.set(0, nrows);
	}
	else if (hit1 <= nobs && hit0 > 0) { // closed range
	    if (hit1 > hit0) {
		if (bits[hit1-1] == 0)
		    activate(hit1-1);
		if (bits[hit1-1] != 0) {
		    lower.copy(*(bits[hit1-1]));
		    if (bits[hit0-1] == 0)
			activate(hit0-1);
		    if (bits[hit0-1] != 0)
			lower -= *(bits[hit0-1]);
		    upper.copy(lower);
		}
		else {
		    lower.set(0, nrows);
		    upper.set(0, nrows);
		}
	    }
	    else {
		lower.set(0, nrows);
		upper.set(0, nrows);
	    }
	}
	else if (hit0 > 0) { // open to the right (+infinity)
	    if (bits[hit0-1] == 0)
		activate(hit0-1);
	    if (bits[hit0-1] != 0) {
		lower.copy(*(bits[hit0-1]));
		lower.flip();
	    }
	    else {
		lower.set(1, nrows);
	    }
	    upper.copy(lower);
	}
	else if (hit1 <= nobs) {
	    if (bits[hit1-1] == 0)
		activate(hit1-1);
	    if (bits[hit1-1] != 0) {
		lower.copy(*(bits[hit1-1]));
		upper.copy(*(bits[hit1-1]));
	    }
	    else {
		lower.set(0, nrows);
		upper.set(0, nrows);
	    }
	}
	else {
	    lower.set(1, nrows);
	    upper.set(1, nrows);
	}
    }
    else if (cand0+1 == cand1) { // all in one coarse bin
	if (cand0 >= nobs) { // unrecorded (coarse) bin
	    if (bits[nobs-1] == 0)
		activate(nobs - 1);
	    if (bits[nobs-1] != 0) {
		upper.copy(*(bits.back()));
		upper.flip();
	    }
	    else {
		upper.set(1, nrows);
	    }
	    lower.set(0, upper.size());
	}
	else if (sub.size() == nobs) { // sub is defined
	    j = cand0;
	    if (sub[j]) { // subrange cand0 is defined
		// locate the boundary bins
		bin0 = sub[j]->locate(lbound);
		bin1 = sub[j]->locate(rbound);
		if (bin0 >= sub[j]->nobs) {
		    bin0 = sub[j]->nobs - 1;
		}
		if (bin1 >= sub[j]->nobs) {
		    bin1 = sub[j]->nobs - 1;
		}

		if (rbound <= sub[j]->minval[bin1]) {
		    cand1 = bin1;
		    hit1 = bin1;
		}
		else if (rbound <= sub[j]->maxval[bin1]) {
		    cand1 = bin1 + 1;
		    hit1 = bin1;
		}
		else {
		    cand1 = bin1 + 1;
		    hit1 = bin1 + 1;
		}
		if (lbound > sub[j]->maxval[bin0]) {
		    cand0 = bin0 + 1;
		    hit0 = bin0 + 1;
		}
		else if (lbound > sub[j]->minval[bin0]) {
		    cand0 = bin0;
		    hit0 = bin0 + 1;
		}
		else {
		    cand0 = bin0;
		    hit0 = bin0;
		}

		// add up the bins
		if (hit0 >= hit1) {
		    lower.set(0, nrows);
		}
		else {
		    sub[j]->addBits(hit0, hit1, lower);
		}
		upper.copy(lower);
		sub[j]->sumBits(cand0, cand1, upper, hit0, hit1);
	    }
	    else { // subrange cand0 is not defined
		lower.set(0, nrows);
		if (bits[cand0] == 0)
		    activate(cand0);
		if (bits[cand0] != 0) {
		    upper.copy(*(bits[cand0]));
		    if (cand0 > 0) {
			if (bits[cand0-1] == 0)
			    activate(cand0-1);
			if (bits[cand0-1] != 0)
			    upper -= *(bits[cand0-1]);
		    }
		}
		else {
		    upper.set(0, nrows);
		}
	    }
	}
	else { // sub is not defined
	    lower.set(0, nrows);
	    if (bits[cand0] == 0)
		activate(cand0);
	    if (bits[cand0] != 0) {
		upper.copy(*(bits[cand0]));
		if (cand0 > 0) {
		    if (bits[cand0-1] == 0)
			activate(cand0-1);
		    if (bits[cand0-1] != 0)
			upper -= *(bits[cand0-1]);
		}
	    }
	    else {
		upper.set(0, nrows);
	    }
	}
    }
    else if (cand0 == hit0) { // the right bound needs finer level
	// implicitly: hit1+1 == cand1, hit1 < nobs
	if (hit0 < hit1) {
	    if (bits[hit1-1] == 0)
		activate(hit1-1);
	    if (bits[hit1-1])
		lower.copy(*(bits[hit1-1]));
	    if (hit0 > 0) {
		if (bits[hit0-1] == 0)
		    activate(hit0-1);
		if (bits[hit0-1] != 0)
		    lower -= *(bits[hit0-1]);
	    }
	}
	else {
	    lower.set(0, nrows);
	}

	if (sub.size() == nobs) { // sub is defined
	    if (hit1 >= nobs) { // right edge bin not recorded
		col->getNullMask(upper);
	    }
	    else if (sub[hit1]) { // this particular subrange exists
		activate((hit1>0 ? hit1-1 : 0), hit1+1);
		if (bits[hit1] == 0) return;
		ibis::bitvector tot(*(bits[hit1]));
		if (hit1 > 0 && bits[hit1-1] != 0)
		    tot -= *(bits[hit1-1]);

		i = sub[hit1]->locate(rbound);
		if (i >= sub[hit1]->nobs) { // impossible ?
		    same = true;
		    upper.copy(lower);
		    col->logWarning("pack::estimate", "logical error -- "
				    "rbound = %.16g, bounds[%lu] = %.16g",
				    rbound,
				    static_cast<long unsigned>(hit1),
				    bounds[hit1]);
		}
		else if (rbound <= sub[hit1]->minval[i]) {
		    same = true;
		    if (i > 0) {
			if (bits[hit1])
			    sub[hit1]->addBits(0, i, lower, tot);
		    }
		    upper.copy(lower);
		}
		else if (rbound <= sub[hit1]->maxval[i]) {
		    if (i > 0) {
			if (bits[hit1])
			    sub[hit1]->addBits(0, i, lower, tot);
		    }
		    upper.copy(lower);
		    sub[hit1]->activate(i);
		    if (sub[hit1]->bits[i])
			upper |= *(sub[hit1]->bits[i]);
		}
		else {
		    same = true;
		    sub[hit1]->addBits(0, i+1, lower, tot);
		    upper.copy(lower);
		}
	    }
	    else {
		upper.copy(lower);
		if (bits[hit1] == 0)
		    activate(hit1);
		if (bits[hit1] != 0)
		    upper |= (*(bits[hit1]));
	    }
	}
	else {
	    if (hit1 < bits.size()) {
		if (bits[hit1] == 0)
		    activate(hit1);
		if (bits[hit1] != 0)
		    upper.copy(*(bits[hit1]));
		else
		    col->getNullMask(upper);
		if (hit0 > 0 && bits[hit0-1] != 0)
		    upper -= *(bits[hit0-1]);
	    }
	    else {
		col->getNullMask(upper);
		if (hit0 > 0 && bits[hit0-1] != 0)
		    upper -= *(bits[hit0-1]);
	    }
	}
    }
    else if (cand1 == hit1) { // the left end needs finer level
	// implcitly: cand0=hit0-1; hit0 > 0
	if (hit0 < hit1) {
	    if (hit1 <= nobs) {
		if (bits[hit1-1] == 0)
		    activate(hit1-1);
		if (bits[hit1-1]) {
		    lower.copy(*(bits[hit1-1]));
		    if (hit0 > 0) {
			if (bits[hit0-1] == 0)
			    activate(hit0-1);
			if (bits[hit0-1] != 0)
			    lower -= *(bits[hit0-1]);
		    }
		}
		else {
		    lower.set(0, nrows);
		}
	    }
	    else {
		if (bits[hit0-1] == 0)
		    activate(hit0-1);
		if (bits[hit0-1] != 0) {
		    lower.copy(*(bits[hit0-1]));
		    lower.flip();
		}
		else {
		    lower.set(1, nrows);
		}
	    }
	}
	else {
	    lower.set(0, nrows);
	}

	if (sub.size() == nobs && sub[cand0] != 0) {
	    // the particular subrange is defined
	    activate((cand0>0 ? cand0-1 : 0), cand0+1);
	    if (bits[cand0] == 0) return;
	    ibis::bitvector tot(*(bits[cand0]));
	    if (cand0 > 0 && bits[cand0-1] != 0)
		tot -= *(bits[cand0-1]);

	    i = sub[cand0]->locate(lbound);
	    if (i >= sub[cand0]->nobs) { // impossible case
		upper.copy(lower);
		col->logWarning("pack::estimate", "logical error -- "
				"lbound = %.16g, bounds[%lu] = %.16g",
				lbound,
				static_cast<long unsigned>(cand0),
				bounds[cand0]);
	    }
	    else if (lbound > sub[cand0]->maxval[i]) {
		sub[cand0]->addBits(i+1, sub[cand0]->nobs, lower, tot);
		upper.copy(lower);
	    }
	    else if (lbound > sub[cand0]->minval[i]) {
		sub[cand0]->addBits(i+1, sub[cand0]->nobs, lower, tot);
		upper.copy(lower);
		sub[cand0]->activate(i);
		if (sub[cand0]->bits[i])
		    upper |= *(sub[cand0]->bits[i]);
	    }
	    else {
		sub[cand0]->addBits(i, sub[cand0]->nobs, lower, tot);
		upper.copy(lower);
	    }
	}
	else {
	    upper.copy(lower);
	    if (bits[cand0] == 0)
		activate(cand0);
	    if (bits[cand0] != 0)
		upper |= *(bits[cand0]);
	}
    }
    else { // both ends need the finer level
	// first deal with the right end of the range
	j = hit1 - 1;
	if (hit1 > nobs) { // right end is open
	    same = true;
	    if (hit0 > 0) {
		if (bits[hit0-1] == 0)
		    activate(hit0-1);
		if (bits[hit0-1] != 0) {
		    lower.copy(*(bits[hit0-1]));
		    lower.flip();
		}
		else {
		    lower.set(1, nrows);
		}
	    }
	    else {
		lower.set(1, nrows);
	    }
	}
	else if (hit1 == nobs) { // right end falls in the last bin
	    if (rbound > max1) {
		same = true;
		if (bits[hit0-1] == 0)
		    activate(hit0-1);
		if (bits[hit0-1] != 0) {
		    lower.copy(*(bits[hit0-1]));
		    lower.flip();
		}
		else {
		    lower.set(1, nrows);
		}
	    }
	    else if (rbound > min1) {
		if (bits[hit0-1] == 0)
		    activate(hit0-1);
		if (bits[hit0-1] != 0) {
		    upper.copy(*(bits[hit0-1]));
		    upper.flip();
		}
		else {
		    upper.set(1, nrows);
		}

		if (bits[nobs-1] == 0)
		    activate(nobs-1);
		if (bits[nobs-1] != 0) {
		    lower.copy(*(bits.back()));
		    if (bits[hit0-1])
			lower -= *(bits[hit0-1]);
		}
		else {
		    lower.set(0, nrows);
		}
	    }
	    else {
		same = true;
		if (bits[nobs-1] == 0)
		    activate(nobs-1);
		if (bits[nobs-1] != 0) {
		    lower.copy(*(bits.back()));
		    if (bits[hit0-1] == 0)
			activate(hit0-1);
		    if (bits[hit0-1] != 0)
			lower -= *(bits[hit0-1]);
		}
		else {
		    lower.set(0, nrows);
		}
	    }
	}
	else {
	    if (hit0 < hit1) {
		if (bits[j] == 0)
		    activate(j);
		if (bits[j] != 0) {
		    lower.copy(*(bits[j]));
		    if (bits[hit0-1] == 0)
			activate(hit0-1);
		    if (bits[hit0-1] != 0)
			lower -= *(bits[hit0-1]);
		}
		else {
		    lower.set(0, nrows);
		}
	    }
	    else {
		lower.set(0, nrows);
	    }

	    if (sub.size() == nobs && sub[hit1] != 0) {
		// the specific subrange exists
		activate((hit1 > 0 ? hit1-1 : 0), hit1+1);
		if (bits[hit1] != 0) {
		    ibis::bitvector tot(*(bits[hit1]));
		    if (hit1>0 && bits[hit1-1] != 0)
			tot -= *(bits[hit1-1]);

		    i = sub[hit1]->locate(rbound);
		    if (i >= sub[hit1]->nobs) { // ??
			same = true;
			col->logWarning("pack::estimate", "logical error -- "
					"rbound = %.16g, bounds[%lu] = %.16g",
					rbound,
					static_cast<long unsigned>(hit1),
					bounds[hit1]);
		    }
		    else if (rbound <= sub[hit1]->minval[i]) {
			same = true;
			if (i > 0) {
			    sub[hit1]->addBits(0, i, lower, tot);
			}
		    }
		    else if (rbound <= sub[hit1]->maxval[i]) {
			if (i > 0) {
			    sub[hit1]->addBits(0, i, lower, tot);
			}
			upper.copy(lower);
			sub[hit1]->activate(i);
			if (sub[hit1]->bits[i])
			    upper |= *(sub[hit1]->bits[i]);
		    }
		    else {
			same = true;
			sub[hit1]->addBits(0, i+1, lower, tot);
		    }
		}
		else {
		    upper.copy(lower);
		}
	    }
	    else {
		upper.copy(lower);
		if (bits[hit1] == 0)
		    activate(hit1);
		if (bits[hit1] != 0)
		    upper |= *(bits[hit1]);
	    }
	}

	// deal with the lower (left) boundary
	j = cand0 - 1;
	if (cand0 == 0) { // sub[0] is never defined
	    if (same)
		upper.copy(lower);
	    if (bits[0])
		upper |= *(bits[0]);
	}
	else if (sub.size() == nobs && sub[cand0] != 0) { // sub defined
	    i = sub[cand0]->locate(lbound);
	    activate((cand0>0 ? cand0-1 : 0), cand0+1);
	    if (bits[cand0] != 0) {
		ibis::bitvector tot(*(bits[cand0]));
		if (cand0 > 0 && bits[cand0-1] != 0)
		    tot -= *(bits[cand0-1]);
		if (i >= sub[cand0]->nobs) { // unlikely case
		    if (same)
			upper.copy(lower);
		    col->logWarning("pack::estimate", "logical error -- "
				    "lbound = %.16g, bounds[%lu] = %.16g",
				    lbound,
				    static_cast<long unsigned>(cand0),
				    bounds[cand0]);
		}
		else if (lbound > sub[cand0]->maxval[i]) {
		    ibis::bitvector tmp;
		    sub[cand0]->addBits(i+1, sub[cand0]->nobs, tmp, tot);
		    lower |= tmp;
		    if (same) {
			upper.copy(lower);
		    }
		    else {
			upper |= tmp;
		    }
		}
		else if (lbound > sub[cand0]->minval[i]) {
		    ibis::bitvector tmp;
		    sub[cand0]->addBits(i+1, sub[cand0]->nobs, tmp, tot);
		    lower |= tmp;
		    if (same) {
			upper.copy(lower);
		    }
		    else {
			upper |= tmp;
		    }
		    sub[cand0]->activate(i);
		    if (sub[cand0]->bits[i])
			upper |= *(sub[cand0]->bits[i]);
		}
		else {
		    ibis::bitvector tmp;
		    sub[cand0]->addBits(i, sub[cand0]->nobs, tmp, tot);
		    lower |= tmp;
		    if (same) {
			upper.copy(lower);
		    }
		    else {
			upper |= tmp;
		    }
		}
	    }
	}
	else {
	    if (same)
		upper.copy(lower);

	    if (bits[cand0] == 0)
		activate(cand0);
	    if (bits[cand0] != 0)
		upper |= *(bits[cand0]);
	}
    }
} // ibis::pack::estimate

// ***should implement a more efficient version***
float ibis::pack::undecidable(const ibis::qContinuousRange& expr,
			      ibis::bitvector& iffy) const {
    float ret = 0;
    ibis::bitvector tmp;
    estimate(expr, tmp, iffy);
    if (iffy.size() == tmp.size())
	iffy -= tmp;
    else
	iffy.set(0, tmp.size());

    if (iffy.cnt() > 0) {
	uint32_t cand0=0, hit0=0, hit1=0, cand1=0;
	locate(expr, cand0, cand1, hit0, hit1);
	if (cand0+1 == hit0 && maxval[cand0] > minval[cand0]) {
	    ret = (maxval[cand0] - expr.leftBound()) /
		(maxval[cand0] - minval[cand0]);
	    if (ret < FLT_EPSILON)
		ret = FLT_EPSILON;
	}
	if (hit1+1 == cand1 && maxval[hit1] > minval[hit1]) {
	    if (ret > 0)
		ret = 0.5 * (ret + (expr.rightBound() - minval[hit1]) /
			     (maxval[hit1] - minval[hit1]));
	    else
		ret = (expr.rightBound() - minval[hit1]) /
		    (maxval[hit1] - minval[hit1]);
	    if (ret < FLT_EPSILON)
		ret = FLT_EPSILON;
	}
    }
    return ret;
} // ibis::pack::undecidable

double ibis::pack::getSum() const {
    double ret;
    bool here = true;
    { // a small test block to evaluate variable here
	const uint32_t nbv = col->elementSize()*col->partition()->nRows();
	if (str != 0)
	    here = (str->bytes()*2 < nbv);
	else if (offsets.size() > nobs)
	    here = (static_cast<uint32_t>(offsets[nobs]*2) < nbv);
    }
    if (here) {
	ret = computeSum();
    }
    else { // indicate sum is not computed
	ibis::util::setNaN(ret);
    }
    return ret;
} // ibis::pack::getSum

/// The the approximate sum of all values using the top level bins.
double ibis::pack::computeSum() const {
    double sum = 0;
    activate(); // need to activate all bitvectors
    if (minval[0] <= maxval[0] && bits[0] != 0)
	sum = 0.5*(minval[0] + maxval[0]) * bits[0]->cnt();
    for (uint32_t i = 1; i < nobs; ++ i)
	if (minval[i] <= maxval[i] && bits[i] != 0) {
	    ibis::bitvector diff(*(bits[i]));
	    if (bits[i-1])
		diff -= *(bits[i-1]);
	    sum += 0.5 * (minval[i] + maxval[i]) * diff.cnt();
	}
    // dealing with the last bins
    ibis::bitvector mask;
    col->getNullMask(mask);
    mask -= *(bits[nobs-1]);
    sum += 0.5*(max1 + min1) * mask.cnt();
    return sum;
} // ibis::pack::computeSum
