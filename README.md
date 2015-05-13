# TinyWorld [![Build Status](https://travis-ci.org/xpac27/TinyWorld.svg?branch=master)](https://travis-ci.org/xpac27/TinyWorld)

![alt text](https://github.com/xpac27/TinyWorld/raw/master/screenshots/Screen-Shot-2015-04-24-at-22.51.23.png)

This is a work in progress which purpose is for me to learn C++.

Todo:
- [ ] make entities learn to look for food
- [ ] make entities move randomly and die after some time
- [x] ambiant, diffuse, specular lighting
- [x] png textures
- [x] obj, mtl parser
- [x] vertex array object
- [x] basic entity component system

## Requirements

* **OpenGL** ([website](https://www.opengl.org/))
* **GLEW** 1.12.0 + ([website](http://glew.sourceforge.net/))
* **GLFW** 3.1.1 + ([website](glfw.org/index.html))
* **GLM** 0.9.6 + ([website](glm.g-truc.net))
* **LibPNG** ([website](http://www.libpng.org/pub/png/libpng.html))
* **CMake** 2.8.12 + ([website](http://www.cmake.org/))
* **Clang Static Analyzer** ([website](http://clang-analyzer.llvm.org/index.html)) optional

## Basic usage

Type `make` and the application should configure, compile and run \o/.

Optionaly, you can run `make configure` once and use the commands above.

- `make compile` - compile the application
- `make test` - compile and run the tests
- `make report` - compile the application and run the static analyzer on it

## Setup

### Mac OSX

    brew install glew glfw3 glm libpng cmake

Optionaly, in order to use Clang Static Analyzer:

    brew install llvm
    export PATH="$PATH:/usr/local/Cellar/llvm/3.5.1/share/clang/tools/scan-build"

### Ubuntu

    apt-get update
    apt-get install cmake libstdc++6 libxrandr-dev libxcursor-dev libglew-dev libpng12-dev

Download GLM from the website, unzip it and copy the `glm` folder (containing the headers) to `/usr/include`.

Follow ([this guide](http://www.glfw.org/docs/latest/compile.html)) to install GLFW3 from sources.

Optionaly, in order to use Clang Static Analyzer:

    apt-get install llvm
