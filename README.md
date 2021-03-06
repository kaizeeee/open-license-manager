# Open License Manager

A copy protection, licensing software written in C++ for Windows and Linux (with a simple C api for use in C projects).

[![Standard](https://img.shields.io/badge/c%2B%2B-11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)
[![unstable](http://badges.github.io/stability-badges/dist/unstable.svg)](http://github.com/badges/stability-badges)
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![Build Status](https://travis-ci.org/open-license-manager/open-license-manager.svg?branch=develop)](https://travis-ci.org/open-license-manager/open-license-manager)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/62d6e1bb22d648bd85b6f3bc344a545a)](https://www.codacy.com/manual/gcontini/open-license-manager?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=open-license-manager/open-license-manager&amp;utm_campaign=Badge_Grade)
[![codecov](https://codecov.io/gh/open-license-manager/open-license-manager/branch/develop/graph/badge.svg)](https://codecov.io/gh/open-license-manager/open-license-manager)
[![Github Issues](https://img.shields.io/github/issues/open-license-manager/open-license-manager)](http://github.com/open-license-manager/open-license-manager/issues)

Protect the software you develop from unauthorized copies, limit the usage in time, to a specific set of 
machines, or prevent the usage in  virtualized environments. It is an Open License Manager that helps to keep your 
software closed :smirk: . Among other features if it runs on a "real hardware" it can generate a signature of that hardware and report if the signature doesn't match.

A comprehensive [list of features](https://github.com/open-license-manager/open-license-manager/wiki/features), and their status is available in the project wiki. 

If you plan to use this library or part of it remember to show us your appreciation giving it a 
<a class="github-button" href="https://github.com/open-license-manager/open-license-manager" data-icon="octicon-star" aria-label="Star open-license-manager/open-license-manager on GitHub">star</a> here on GitHub.

## License
The project is donated to the community. It comes with a very large freedom of use for everyone, and it will always be. 
It uses a [BSD 3 clauses](https://opensource.org/licenses/BSD-3-Clause) licensing schema, that allows free modification and inclusion in commercial software. 

## Project Structure
The software is made by 3 main sub-components:
-   a C++ library with a nice C api, `licensecc` with minimal (or no) external dependencies (the part you have to integrate in your software) that is the project you're currently in.
-   a license debugger `lcc-inspector` to be sent to the final customer when there are licensing problems or for calculating the pc hash before issuing the license.
-   a license generator (github project [lcc-license-generator](https://github.com/open-license-manager/lcc-license-generator)) `lcc` for customizing the library and generate the licenses.
 
## How to build
Below an overview of the basic build procedure, you can find detailed instructions for [linux](http://open-license-manager.github.io/open-license-manager/development/Build-the-library.html) 
or [windows](http://open-license-manager.github.io/open-license-manager/development/Build-the-library-windows.html) in the project web site. 

### Prerequisites
-   Operating system: Linux(Ubuntu, CentOS), Windows
-   compilers       : GCC (Linux) MINGW (Linux cross compile for Windows), MINGW or MSVC (Windows) 
-   tools           : cmake(>3.6), git, make/ninja(linux)
-   libs            : If target is Linux Openssl is required. Windows depends only on system libraries. Boost is necessary to build license generator and to run the tests but it's NOT a dependency of the final `licensecc` library. 

For a complete list of dependencies and supported environments see [the wiki](https://github.com/open-license-manager/open-license-manager/wiki/Dependencies)

Clone the project. It has submodules, don't forget the `--recursive` option.

```console
git clone --recursive https://github.com/open-license-manager/open-license-manager.git
cd open-license-manager/
cd build
```

### build on Linux

```console
cmake .. -DCMAKE_INSTALL_PREFIX=../install
make
make install
```

### build on Windows (with MSVC 2015)

```console
cmake .. -G "Visual Studio 14 2015 Win64" -DBOOST_ROOT="{Folder where boost is}" -DCMAKE_INSTALL_PREFIX=../install
cmake --build . --target install --config Release
```

### cross compile with MINGW on Linux

```console
x86_64-w64-mingw32.static-cmake .. -DCMAKE_INSTALL_PREFIX=../install
make
make install
```

## How to test

### on Linux

```console
make test
```

### on Windows (MSVC)

```console
ctest -C Release
```

## How to use

The [examples](https://github.com/open-license-manager/examples) repository that shows various ways to integrate `open-licence-manager` into your project.

## How to contribute

The easiest way you can solve your problems or ask help is through the [forum](https://groups.google.com/forum/#!forum/licensecc) (hosted on Google), 
otherwise if you think there is a problem you can open an issue in the [issue system](https://github.com/open-license-manager/open-license-manager/issues). 
Have a look to the [contribution guidelines](CONTRIBUTING.md) before reporting.
We use [GitFlow](https://datasift.github.io/gitflow/IntroducingGitFlow.html) (or at least a subset of it). 
Remember to install the gitflow git plugin and use `develop` as default branch for your pull requests. 
