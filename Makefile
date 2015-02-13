all: configure compile
.PHONY: all

configure:
	@echo ""; echo "[1;33m-- Configuring build[0m"
	mkdir -p build-debug
	cd build-debug && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ../cmake

compile:
	@echo ""; echo "[1;33m-- Compiling sources[0m"
	make -C build-debug

toto:
	mkdir -p build-analyze reports
	cd build-analyze && cmake -DCMAKE_CXX_COMPILER=c++-analyzer -DCMAKE_C_COMPILER=ccc-analyzer ../cmake

clean:
	@echo ""; echo "[1;33m-- Removing all build data[0m"
	rm -rf build-*/*

run:
	@echo ""; echo "[1;33m-- Running the app[0m"
	./build-debug/wip
