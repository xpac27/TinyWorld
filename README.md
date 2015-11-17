# TinyWorld [![Build Status](https://travis-ci.org/xpac27/TinyWorld.svg?branch=master)](https://travis-ci.org/xpac27/TinyWorld)

![alt text](https://github.com/xpac27/TinyWorld/raw/master/screenshots/Screen-Shot-2015-11-17-at-22.39.20)

This is a work in progress which purpose is for me to learn C++.

Todo:
- [ ] make entities learn to look for food
- [ ] make entities move randomly and die after some time
- [ ] continus formated statistics
- [ ] terrain height
- [ ] controled camera
- [ ] physically based shading
- [ ] gamma correction
- [ ] deferred shading
- [x] shadow volume
- [x] batched rendering
- [x] ambiant, diffuse, specular lighting
- [x] png textures
- [x] obj, mtl parser
- [x] vertex array object
- [x] basic entity component system

## Requirements

* **OpenGL** 4.1 + ([website](https://www.opengl.org/))
* **GLEW** 1.12.0 + ([website](http://glew.sourceforge.net/))
* **GLFW** 3.1.1 + ([website](glfw.org/index.html))
* **GLM** 0.9.6 + ([website](glm.g-truc.net))
* **LibPNG** ([website](http://www.libpng.org/pub/png/libpng.html))
* **Ninja** 1.6.0 + ([website](https://martine.github.io/ninja/))
* **Buildfox** 0.1.2 + ([website](https://github.com/beardsvibe/buildfox))

## Basic usage

Type `make` and the application should configure, compile and run \o/.

Optionaly, you can run `make configure` once and use the commands above.

- `make compile` - compile the application
- `make test` - compile and run the tests
- `make report` - compile the application and run the static code analyzer on it
- `make coverage` - compile the application and run the code coverage analyzer on it

## Setup

### Mac OSX

	brew update
	brew tap homebrew/versions
	brew install glfw3 glew glm libpng ninja
	pip install buildfox

Optionaly, in order to use Clang Static Analyzer:

	brew install lcov
	brew install llvm --with-clang
	export PATH="$PATH:/usr/local/opt/llvm/share/clang/tools/scan-build"
	export PATH="$PATH:/usr/local/opt/llvm/bin/"

### Ubuntu

Prerequisits:

    apt-get update
    apt-get install curl unzip python-pip cmake

Libs:

    apt-get install libc++-dev libglew-dev libpng12-dev

Build system:

    apt-get install ninja-build
    pip install buildfox

GLM:

    curl -LO http://downloads.sourceforge.net/project/ogl-math/glm-0.9.6.3/glm-0.9.6.3.zip
    unzip -q glm-0.9.6.3.zip
    sudo cp -r glm/glm /usr/include/
    rm -rf glm glm-0.9.6.3.zip

GLFW3:

    curl -LO https://github.com/glfw/glfw/releases/download/3.1.1/glfw-3.1.1.zip
    unzip -q glfw-3.1.1.zip
    cd glfw-3.1.1
    cmake .
    make
    sudo make install
    cd ..
    rm glfw-3.1.1.zip

Optionaly, in order to use Clang Static Analyzer and Code Coverage:

    apt-get install llvm lcov
