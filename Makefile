all: configure compile run
S = \n[1;33m--
E = [0m

.PHONY: all configure run debug test report coverage coverage_html configure_report clean reset

configure:
	@echo "$(S) Configuring builds $(E)"
	@mkdir -p build && cd build && cmake ..

configure_report:
	@echo "$(S) Configuring builds $(E)"
	@mkdir -p build/report && cd build/report && cmake -DCMAKE_C_COMPILER=ccc-analyzer -DCMAKE_CXX_COMPILER=c++-analyzer -DGLM_COMPILER=0 ../..

compile:
	@echo "$(S) Compiling sources $(E)"
	@make app -C build -j8

run:
	@echo "$(S) Running the app $(E)"
	@./build/app/app

debug:
	@echo "$(S) Debugging the app $(E)"
	@lldb -f build/app/app

test:
	@echo "$(S) Compiling tests $(E)"
	@make tests -C build -j8
	@echo "$(S) Running tests $(E)"
	@./build/lib/tests/tests

report: configure_report
	@echo "$(S) Compiling static analysis report $(E)"
	@scan-build -V make app -C build/report

coverage:
	echo "$(S) Generate code coverage report $(E)"
	make lib_coverage -C build -j8
	./build/lib/lib_coverage
	xcrun llvm-cov gcov -f `find build -name "*.gcda" | grep -v "dir/tests" | xargs`
	rm -rf coverage && mkdir -p coverage
	lcov --directory . --base-directory . --gcov-tool scripts/llvm-gcov.sh --no-external --capture -o coverage/cov.info
	lcov --remove coverage/cov.info 'lib/tests/*' -o coverage/cov.info
	lcov --list coverage/cov.info

coverage_html: coverage
	@genhtml coverage/cov.info -o coverage
	@open coverage/index.html

clean:
	@echo "$(S) Compiling sources $(E)"
	@make clean -C build
	@echo "done!"

reset:
	@echo "$(S) Removing all build data $(E)"
	@rm -rf build
	@echo "done!"
