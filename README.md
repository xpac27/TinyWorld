## Requirements

###### SFML

You need to install SMFL 2.2. There are great tutorials on how to install it on the [official website](http://www.sfml-dev.org/tutorials/2.2/).

###### CMake

CMake is used to compile the project. You can find information on how to get CMake on the [official website](http://www.cmake.org/). On MacOSX you can use [homebrew](http://mxcl.github.io/homebrew/) and  run `brew install cmake`.

###### LLVM

CLang's analyzer scan-build is used to generate reports. You can find information on how to install scan-build on the [official website](http://clang-analyzer.llvm.org/index.html).

On MacOSX you can use [homebrew](http://mxcl.github.io/homebrew/) and  run `brew install llvm`. In order to use this version of llvm you need to set the following:

    export CC="/usr/local/Cellar/llvm/3.5.1/bin/clang"
    export CXX="/usr/local/Cellar/llvm/3.5.1/bin/clang++ -stdlib=libc++"
    export CXXFLAGS="$CXXFLAGS -nostdinc++ -I/usr/local/Cellar/llvm/3.5.1/include"
    export LDFLAGS="$LDFLAGS -L/usr/local/Cellar/llvm/3.5.1/lib"
    export PATH="$PATH:/usr/local/Cellar/llvm/3.5.1/share/clang/tools/scan-build"

## Basic usage

Running the `make` command will configure and compile the application. You can the start the generated executable file located in the build folder: `./build/wip`.

Running `make report` will generate a static analysis report.
