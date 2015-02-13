all: configure compile
.PHONY: all

configure:
	@echo ""; echo "[1;33m-- Configuring build[0m"
	mkdir -p build-debug
	cd build-debug && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ../cmake

report:
	@echo ""; echo "[1;33m-- Compile and create report[0m"
	mkdir -p build-analyze reports
	cd build-analyze && scan-build cmake ../cmake
	scan-build -o reports make -C build-analyze
	open reports/`ls reports | tail -1`/index.html

compile:
	@echo ""; echo "[1;33m-- Compiling sources[0m"
	make -C build-debug

clean:
	@echo ""; echo "[1;33m-- Removing all build data[0m"
	rm -rf build-*/*

run:
	@echo ""; echo "[1;33m-- Running the app[0m"
	./build-debug/wip
