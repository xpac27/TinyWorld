#!/bin/bash

function show_help() {
	echo "usage: ./cubemap2irrmap.sh [-i input_folder]"
	echo ""
	echo "  input_folder: a folder containing a 'cubemap' subfolder containing right.png,"
	echo "                left.png, top.png, bottom.png, back.png and front.png files."
}

# A POSIX variable
OPTIND=1         # Reset in case getopts has been used previously in the shell.

# Initialize our own variables:
input=""

while getopts "hi:" opt; do
    case "$opt" in
    h)
        show_help
        exit 0
        ;;
    i)  input=$OPTARG
        ;;
    esac
done

shift $((OPTIND-1))

[ "$1" = "--" ] && shift

SRC="$input/cubemap"
DST="$input/irradiance-map"

convert $SRC/right.png $SRC/left.png $SRC/top.png $SRC/bottom.png $SRC/back.png $SRC/front.png -adjoin /tmp/cube.tif
envremap -i cube -o rect -n 512 /tmp/cube.tif /tmp/rect.tif
shtrans -g32 -o /tmp/g32.tif /tmp/rect.tif
shtrans -i -o /tmp/irr.tif /tmp/g32.tif
envremap -i rect -o cube -n 512 /tmp/irr.tif /tmp/cube-irr.tif
convert /tmp/cube-irr.tif -scene 0 /tmp/cube-irr-%d.tif
convert /tmp/cube-irr-0.tif $DST/right.png
convert /tmp/cube-irr-1.tif $DST/left.png
convert /tmp/cube-irr-2.tif $DST/top.png
convert /tmp/cube-irr-3.tif $DST/bottom.png
convert /tmp/cube-irr-4.tif $DST/back.png
convert /tmp/cube-irr-5.tif $DST/front.png
