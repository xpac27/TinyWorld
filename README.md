# TinyWorld [![Build Status](https://travis-ci.org/xpac27/TinyWorld.svg?branch=master)](https://travis-ci.org/xpac27/TinyWorld)

![alt text](https://github.com/xpac27/TinyWorld/raw/master/screenshots/Screen-Shot-2015-04-24-at-22.51.23.png)

This is a work in progress which purpose is for me to learn C++.

Todo:
- [ ] make entities learn to look for food
- [ ] make entities move randomly and die after some time
- [x] obj parser
- [x] vertex buffer object
- [x] basic entity component system

## Requirements

* **SMFL** 2.0 + ([website](http://www.sfml-dev.org/tutorials/2.2/))
* **CMake** 2.8.12 + ([website](http://www.cmake.org/))
* **Clang Static Analyzer** ([website](http://clang-analyzer.llvm.org/index.html)) optional

## Basic usage

Type `make` and the application should configure, compile and run \o/.

Optionaly, you can run `make configure` once and use the commands above.

- `make compile` - compile the application
- `make test` - compile and run the tests
- `make report` - compile the application and run the static analyzer on it
- `make report-open` - open the latest report

## Setup

### Mac OSX 

    brew install sfml cmake

Optionaly, in order to use Clang Static Analyzer:

    brew install llvm
    export PATH="$PATH:/usr/local/Cellar/llvm/3.5.1/share/clang/tools/scan-build"

### Ubuntu

    apt-get update
    apt-get install cmake llvm libstdc++6 libglew-dev libsfml-dev

Optionaly, in order to use Clang Static Analyzer:

    apt-get install llvm