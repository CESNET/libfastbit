FastBit library
===============

This is a clone of the official FastBit library, which is available 
[here](http://sdm.lbl.gov/fastbit/doc/ "FastBit"). 

This repository contains changes to packaging system which allows to build RPMs
compatible with IPFIXcol packages.

__Warning__: Always clone the repository for updates. Our changes are rebased
on top of original sources, which makes the history subject to change.

### Installation
FastBit can be installed from [Fedora copr repository](https://copr.fedorainfracloud.org/coprs/g/CESNET/IPFIXcol/) on CentOS (>=7) and Fedora (>=22)

Just add the repository to your system:
```
dnf copr enable @CESNET/IPFIXcol 
```

And install the packages:
```
dnf install libfastbit libfastbit-devel
```

### Build Requirements
The FastBit library requires C++11 standard support

### Build Dependencies
CentOS, Fedora, RHEL (supports rpm packages)
```
autoconf make libtool flex gcc-c++ doxygen graphviz sharutils rpm-build

```

Debian. Ubuntu (no packages)
```
autoconf build-essential libtool
```

### Build RPM packages
Following command will create necessary RPMs in RPMBUILD subdirectory

	autoreconf -i
	./configure
	make rpm


### Build and install from sources
	autoreconf -i
	./configure
	make
	make install

<span style="background-color: #FFFF00">Please do run the `autoreconf -i` command. The configure script needs to be regenerated.</span>

### Original documentation
For original documentation please refer to README and INSTALL files in
the root of the repository.
