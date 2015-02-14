all: configure compile run
print = $(MAKE) MESSAGE=$(1) print
print:
	@echo ""; echo "[1;33m-- $(MESSAGE)[0m"

.PHONY: all, print

configure:
	$(call print,"Configuring builds")
	mkdir -p build && cd build && cmake ..

compile:
	$(call print,"Compiling sources")
	make app -C build

run:
	$(call print,"Running the app")
	./build/app/app

tests:
	$(call print,"Compiling tests")
	make test -C build
	$(call print,"Running tests")
	./build/test/test

report:
	$(call print,"Compiling static analysis report")
	scan-build -o reports make report -C build

report-open:
	$(call print,"Open the latest report")
	open reports/`ls reports | tail -1`/index.html

clean:
	$(call print,"Compiling sources")
	make clean -C build

reset:
	$(call print,"Removing all build data")
	rm -rf build/app
	rm -rf build/reports
	rm -rf build/test
	rm build/Makefile
