all: configure compile run
S = \n[1;33m--
E = [0m

.PHONY: all configure run debug test report coverage clean reset

configure:
	@echo "$(S) Configuring builds $(E)"
	@mkdir -p build && cd build && cmake ..

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

report:
	@echo "$(S) Compiling static analysis report $(E)"
	@scan-build make app -C build

coverage:
	@echo "$(S) Running code coverage analysis $(E)"
	@make lib_coverage -C build -j8
	@./build/lib/lib_coverage
	@llvm-cov gcov -f `find build -name "*.gcda" | grep -v "dir/tests" | xargs`
	@rm -rf coverage && mkdir -p coverage
	@lcov --directory . --base-directory . --gcov-tool scripts/llvm-gcov.sh --no-external --capture -o coverage/cov.info
	@lcov --remove coverage/cov.info 'lib/tests/*' -o coverage/cov.info
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
