FastBit library
===============

This is a clone of the official FastBit library, which is available 
[here](http://sdm.lbl.gov/fastbit/doc/ "FastBit"). 

This repository contains changes to packaging system which allows to build RPMs
compatible with IPFIXcol packages.

__Warning__: Always clone the repository for updates. Our changes are rebased
on top of original sources, which makes the history subject to change.

### Requirements
The FastBit library requires C++11 standard support


### Build
Following command will create necessary RPMs in RPMBUILD subdirectory

	autoreconf -i
	./configure
	make rpm


### Original documentation
For original documentation please refer to README and INSTALL files in
the root of the repository.
