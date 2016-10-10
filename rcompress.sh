#!/bin/bash

# Finds all PGM image files recursively in given directory and:
#  1. Creates a compressed, n-bit variant of each image file extracted previously.
#  2. Saves each PGM file to the current working directory with a suffix "_n-bit".
#  3. Constructs a histogram of the cumulative color usage of all PGM files.
#  4. Prints said histogram to the stdin.

if [ "$#" -ne 2 ]; then
  echo "Usage: $0 dir bit"
  echo "  dir - directory containing PGM image files."
  echo "  bit - new bit for compressed PGM files."
  echo "Example:"
  echo "  ./rcompress.sh pgm_files/ 4"
  exit
fi

g++ pgm_compress.cpp -o pgm_compress.out
g++ pgm_histogram.cpp -o pgm_histogram.out

readarray files < <(find $1 -name '*.pgm')
n=${#files[@]}

echo "$n" > /tmp/files.txt

for i in "${files[@]}"
do
  filename=$(basename "$i")
  base="${filename%.*}"
  ./pgm_compress.out $2 $base < $i
  echo "${base}_${2}-bit.pgm" >> /tmp/files.txt
done

./pgm_histogram.out < /tmp/files.txt
