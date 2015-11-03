all: configure compile run

.PHONY: all configure run debug test analysis coverage clean reset

configure:
	@mkdir -p out
	@bf debug=true
	@ninja -t compdb cxx > out/compile_commands.json

compile:
	@ninja out/tinyworld

run:
	@./out/tinyworld

debug:
	@lldb -f out/tinyworld

test:
	@ninja out/tests
	@./out/tests

clean:
	@ninja -t clean
	@echo "done!"

reset:
	@rm -rf out
	@echo "done!"

coverage:
	@bf debug=true coverage=true
	@ninja out/tests
	@./out/tests
	@llvm-cov gcov -f `find out -name "*.gcda" | grep -v "dir/tests" | xargs` &> /dev/null
	@rm -rf coverage && mkdir -p coverage
	@lcov --directory . --base-directory . --gcov-tool scripts/llvm-gcov.sh --no-external --capture -o coverage/cov.info &> /dev/null
	@lcov --remove coverage/cov.info 'lib/tests/*' -o coverage/cov.info &> /dev/null
	@lcov --list coverage/cov.info
	@genhtml coverage/cov.info -o coverage &> /dev/null
	@open coverage/index.html

analysis:
	@bf debug=true analysis=true
	@scan-build -V ninja out/tinyworld
