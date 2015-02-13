## Requirements

###### SFML 2.1

You need to install SMFL 2.1. There are great tutorials on how to install it on the [official website](http://www.sfml-dev.org/tutorials/2.1/).

###### CMake

CMake is used to compile the project. You can find information on how to get CMake on the [official website](http://www.cmake.org/). On MacOSX you can use [homebrew](http://mxcl.github.io/homebrew/) and  run `brew install cmake`.

###### LLVM

CLang's analyzer scan-build is used to generate reports. You can find information on how to install scan-build on the [official website](http://clang-analyzer.llvm.org/index.html).

On MacOSX you can use [homebrew](http://mxcl.github.io/homebrew/) and  run `brew install llvm35`.

## Basic usage

Running the `make` command will configure and compile the application. You can the start the generated executable file located in the build folder: `./build/wip`.
