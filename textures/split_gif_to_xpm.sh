#!/usr/bin/env bash

# check if we can use magick

if [ $# -ne 1 ] 
then
	printf "Error. usage: ./script <file.gif>\n"
	exit 1
fi

if ! command -v magick >/dev/null 2>&1
then
	printf "magick command not found. imagemagick is required to manipulate images\n"
	exit 1
fi

gif=$1 # the name of the gif file

# this checks if the file format is a GIF as identified by magick
file_format=$(magick identify "$gif" | awk '{print $2}' | head -n1)
if [ "$file_format" != "GIF" ]
then
	printf "Error. Not a GIF file\n"
	exit 1
fi

printf "Splitting %s into individual frames...\n" "$gif"
sleep 1

# get the name part before the .gif extension
filename=$(echo "$gif" | cut -d'.' -f 1)

# count the number of frames in the gif
frame_count=$(magick identify "$gif" | wc -l)

# split the gif into individual pngs
# not sure the technical differences between adjoin and coalesce
# but coalesce worked for certain gifs that adjoin didn't#
magick -verbose "$gif" -coalesce "$filename"%d.png
#magick -verbose "$gif" +adjoin "$filename"%d.png

printf "Done splitting %s into individual frames\n" "$gif"

# loop through the frames converting each png into an xpm
# remove the png in the process
max_index=$(("$frame_count" - 1))
for i in $(seq 0 "$max_index")
do
	png_file="$filename""$i".png
	xpm_file="$filename""$i".xpm
	magick -verbose "$png_file" "$xpm_file"
	rm -rf "$png_file"
done
