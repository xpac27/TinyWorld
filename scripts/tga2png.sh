#!/bin/bash
find lib/res/textures/surfaces -iname "*.tga" | sed 's/\.tga$//g' | while read i
do
	echo "converting $i to PNG"
	convert "$i.tga" -resize 1024x1024 "$i.png"
	rm "$i.tga"
done
find lib/res/textures/environments -iname "*.tga" | sed 's/\.tga$//g' | while read i
do
	echo "converting $i to PNG"
	convert "$i.tga" -resize 512x512 "$i.png"
	rm "$i.tga"
done
