## Requirements

* **SMFL** ([website](http://www.sfml-dev.org/tutorials/2.2/))
* **CMake** ([website](http://www.cmake.org/))
* **Clang Static Analyzer** ([website](http://clang-analyzer.llvm.org/index.html)) optional

##### On Mac OSX

You can use [homebrew](http://mxcl.github.io/homebrew/) with the following command:

    brew install sfml cmake llvm --with-clang

In order to use Clang Static Analyzer you need to extend your PATH:

    export PATH="$PATH:/usr/local/Cellar/llvm/3.5.1/share/clang/tools/scan-build"

Optionaly, to use clang as default compiler you can export those variables:

    export CC="/usr/local/Cellar/llvm/3.5.1/bin/clang"
    export CXX="/usr/local/Cellar/llvm/3.5.1/bin/clang++ -stdlib=libc++"
    export CXXFLAGS="$CXXFLAGS -nostdinc++ -I/usr/local/Cellar/llvm/3.5.1/include"
    export LDFLAGS="$LDFLAGS -L/usr/local/Cellar/llvm/3.5.1/lib"

## How to installing

Simply clone the repository:

    git clone https://github.com/xpac27/wip.git

And download submodules:

    git submodule init
    git submodule update

## Basic usage

You could type `make` and the application should configure, compile and run \o/. Optionaly, you could run `make configure` once and use the commands above.

This will compile the application:

    make compile

This will compile and run the tests:

    make tests

This will compile the application and run the static analyzer on it (which could take some time):

    make report

This will open the latest report:

    make report-open
