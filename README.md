# TinyWorld [![Build Status](https://travis-ci.org/xpac27/TinyWorld.svg?branch=master)](https://travis-ci.org/xpac27/TinyWorld)

![alt text](https://github.com/xpac27/TinyWorld/raw/master/screenshots/Screen-Shot-2016-02-02-at-23.29.12.gif)

This is a work in progress which purpose is for me to learn C++.

Todo:
- [ ] make entities learn to look for food
- [ ] make entities move randomly and die after some time
- [ ] continus formated statistics
- [ ] terrain height
- [ ] controled camera
- [x] normal mapping
- [x] physically based shading
- [x] gamma correction
- [x] deferred shading
- [x] robust shadow volume
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

Optionaly, you can run:

- `make configure` - generate the project
- `make compile` - compile the application
- `make test` - compile and run the tests
- `make clean` - remove all compiled objects
- `make tidy` - run cland tidy static analyzer
- `make check` - run cppcheck static analyzer
- `make coverage` - run llvm-cov code coverage analyzer
- `make analysis` - run scan-build static analyzer

## Setup

### Mac OSX

	brew update
	brew tap homebrew/versions
	brew install glfw3 glew glm libpng ninja
	pip install buildfox

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

## Static Analyzers

To install CPPCheck:

    git clone git clone git://github.com/danmar/cppcheck.git
    cd cppcheck
    cmake .
    make && make install

To install Clang Static Analyzer, llvm-cov, scan-build and clang-tidy:

	brew install lcov
	brew install llvm --with-clang
	export PATH="$PATH:/usr/local/opt/llvm/share/clang/tools/scan-build"
	export PATH="$PATH:/usr/local/opt/llvm/bin/"

or:

    apt-get install llvm lcov

## Generate irradiance map

You need to install rlk's [envtools](https://github.com/rlk/envtools), [util3d](https://github.com/rlk/util3d), and [sht](https://github.com/rlk/sht).

	git clone git@github.com:rlk/util3d.git
    git clone git@github.com:rlk/sht.git
    git clone git@github.com:rlk/envtools.git
    cd sht && make && cd ..
    cd envtools && make && cd ..
    sudo cp sht/shtrans /usr/lib/
    sudo cp envtools/envremap /usr/lib/

You also need to install [ImageMagick](http://www.imagemagick.org/script/index.php). If you'are on mac you can type `brew install imagemagick`.

Then simply place your cubemap's png images in the resource's environement folder (named front.png, back.png, left.png, right.png, top.png, bottom.png) and run `./scripts/cubemap2irrmap.sh -i lib/res/textures/environments/stormyday`.

