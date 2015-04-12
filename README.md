# TinyWorld [![Build Status](https://travis-ci.org/xpac27/TinyWorld.svg?branch=master)](https://travis-ci.org/xpac27/TinyWorld)

This is a work in progress which purpose is for me to learn C++.

Todo:
- [ ] make entities learn to look for food
- [ ] make entities move randomly and die after some time
- [ ] vertex buffer object
- [x] basic entity component system

## Requirements

* **SMFL** ([website](http://www.sfml-dev.org/tutorials/2.2/))
* **CMake** ([website](http://www.cmake.org/))
* **Clang Static Analyzer** ([website](http://clang-analyzer.llvm.org/index.html)) optional

##### On Mac OSX

Using [homebrew](http://mxcl.github.io/homebrew/):

    brew install sfml cmake llvm

In order to use Clang Static Analyzer you need to extend your PATH this way:

    export PATH="$PATH:/usr/local/Cellar/llvm/3.5.1/share/clang/tools/scan-build"

## Basic usage

Type `make` and the application should configure, compile and run \o/. Optionaly, you can run `make configure` once and use the commands above.

This will compile the application:

    make compile

This will compile and run the tests:

    make test

This will compile the application and run the static analyzer on it (which could take some time):

    make report

This will open the latest report:

    make report-open
