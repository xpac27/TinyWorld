.PHONY: all configure run debug test analysis coverage clean reset tags

all: configure compile run

configure:
	@tup init

compile:
	@tup

run:
	@LD_LIBRARY_PATH=out out/app-desktop

debug:
	@lldb -f out/app-desktop

test:
	@LD_LIBRARY_PATH=out out/tests

reset:
	@echo "Removing all outputs..."
	@rm -rf out
	@echo "done!"

tidy:
	./scripts/clang-tidy

check:
	@./scripts/cppcheck
	@./scripts/cppcheck-htmlreport --title="TinnyWorld" --source-dir=. --report-dir=out/cppcheck --file=out/cppcheck/result.xml
	@open out/cppcheck/index.html

tags:
	./scripts/tags
