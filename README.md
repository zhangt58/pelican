# pelican
One-dimensional time-dependent FEL code

## Description
Solve 1D free-electron laser equations, get FEL output power, both C++ and
MATLAB versions are provided.

* MATLAB functions: ``pelican.m`` and ``pelicanT.m`` could be used to compute
  FEL process cases of single-frequency and multi-frequency;
* Parallel computing is enabled for both C++ and M code;
* C++ version can only solve single-frequency case, but offers efficiency.

## Basic Usage

### Install package

* On Linux OS: Ubuntu 16.04, i.e. xenial, or Linux Mint 18, debian package could
  be used to install by double clicking, packed package could be found in
  [this directory](dist/).
* After installation, update new path of MATLAB with ``/usr/share/pelican_m``,
  then in MATLAB, new functions: ``pelican`` and ``pelicanT`` are ready to use.
* In Linux terminal, command ``pelican`` is ready to use.
* Examples see [HERE for MATLAB](legacy/example) and [HRER for C++ binary](contrib).
* For C++ version, the documentation is hosted [HERE](https://archman.github.io/pelican/).
