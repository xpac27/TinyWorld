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

reset:
	@echo "Removing all outputs..."
	@rm -rf out
	@echo "done!"

irradiance-map:
	$(MAKE) SRC=lib/res/textures/environment DST=lib/res/textures/irradiance-map irradiance-map-compute
irradiance-map-compute:
	convert $(SRC)/right.png $(SRC)/left.png $(SRC)/top.png $(SRC)/bottom.png $(SRC)/back.png $(SRC)/front.png -adjoin /tmp/cube.tif
	envremap -i cube -o rect -n 512 /tmp/cube.tif /tmp/rect.tif
	shtrans -g32 -o /tmp/g32.tif /tmp/rect.tif
	shtrans -i -o /tmp/irr.tif /tmp/g32.tif
	envremap -i rect -o cube -n 512 /tmp/irr.tif /tmp/cube-irr.tif
	convert /tmp/cube-irr.tif -scene 0 /tmp/cube-irr-%d.tif
	convert /tmp/cube-irr-0.tif $(DST)/right.png
	convert /tmp/cube-irr-1.tif $(DST)/left.png
	convert /tmp/cube-irr-2.tif $(DST)/top.png
	convert /tmp/cube-irr-3.tif $(DST)/bottom.png
	convert /tmp/cube-irr-4.tif $(DST)/back.png
	convert /tmp/cube-irr-5.tif $(DST)/front.png

lint:
	clang-tidy -p out/compile_commands.json `find lib/src app/src -name "*.cpp" | xargs`

check:
	@mkdir -p out/cppcheck
	@cppcheck --xml --xml-version=2 --enable=all --std=c++11 --quiet -Ilib/inc -Iapp/src -Ilib/src lib/src app/src 2> out/cppcheck/result.xml
	@./scripts/cppcheck-htmlreport --title="TinnyWorld" --source-dir=. --report-dir=out/cppcheck --file=out/cppcheck/result.xml
	@open out/cppcheck/index.html

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

ctags:
	rm -f ./.git/tags
	find `pwd`/app `pwd`/lib/src `pwd`/lib/inc `pwd`/lib/tests/src \( -name "*.c" -or -name "*.h" -or -name "*.cpp" -or -name "*.hpp" \) -exec ctags --append=yes -f ./.git/tags {} \;
