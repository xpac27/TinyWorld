.PHONY: all
all: configure compile

configure:
	@echo ""; echo "[1;33m-- Configuring build[0m"
	cd build && cmake -DCMAKE_BUILD_TYPE=Debug .

compile:
	@echo ""; echo "[1;33m-- Compiling sources[0m"
	make -C build

run:
	@echo ""; echo "[1;33m-- Running the app[0m"
	./build/wip
