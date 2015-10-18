all: configure compile run
S = \n[1;33m--
E = [0m

.PHONY: all configure run debug test report coverage generate_coverage configure_report clean reset

configure:
	@echo "$(S) Configuring builds $(E)"
	@mkdir -p out
	@bf
	@ninja -t compdb cxx > out/compilation_commands.json

compile:
	@echo "$(S) Compiling sources $(E)"
	@ninja out/tinyworld

run:
	@echo "$(S) Running the app $(E)"
	@./out/tinyworld

debug:
	@echo "$(S) Debugging the app $(E)"
	@lldb -f out/tinyworld

test:
	@echo "$(S) Compiling tests $(E)"
	@ninja out/tests
	@echo "$(S) Running tests $(E)"
	@./out/tests

clean:
	@echo "$(S) Compiling sources $(E)"
	@ninja -t clean
	@echo "done!"

reset:
	@echo "$(S) Removing all build data $(E)"
	@rm -rf out
	@echo "done!"

coverage:
	@echo "$(S) Generate code coverage report $(E)"
	@bf coverage=true
	@ninja out/tests
	@./out/tests
	@llvm-cov gcov -f `find out -name "*.gcda" | grep -v "dir/tests" | xargs` &> /dev/null
	@rm -rf coverage && mkdir -p coverage
	@lcov --directory . --base-directory . --gcov-tool scripts/llvm-gcov.sh --no-external --capture -o coverage/cov.info &> /dev/null
	@lcov --remove coverage/cov.info 'lib/tests/*' -o coverage/cov.info &> /dev/null
	@lcov --list coverage/cov.info
	@genhtml coverage/cov.info -o coverage &> /dev/null
	@open coverage/index.html

report: configure_report
	@echo "$(S) Compiling static analysis report $(E)"
	@scan-build -V make app -C build/report

configure_report:
	@echo "$(S) Configuring builds $(E)"
	@mkdir -p build/report && cd build/report && cmake -DCMAKE_C_COMPILER=ccc-analyzer -DCMAKE_CXX_COMPILER=c++-analyzer -DGLM_COMPILER=0 ../..
