#!/bin/bash

# Finds all PGM image files recursively in given directory and:
#  1. Creates a compressed, n-bit variant of each image file extracted previously.
#  2. Saves each PGM file to the current working directory with a suffix "_n-bit".
#  3. Constructs a histogram of the cumulative color usage of all PGM files.
#  4. Prints said histogram to the stdin.

if [ "$#" -lt 2 ] && [ "$#" -gt 5 ]; then
  echo "Usage: $0 dir bit [parent=1] [plot=1] [real=0]"
  echo "  dir    - directory containing PGM image files."
  echo "  bit    - new bit for compressed PGM files."
  echo "  parent - 1 if should create parent dirs, 0 otherwise."
  echo "  plot   - 1 if should plot with gnuplot, 0 otherwise."
  echo "  real   - 1 if bit should be the absolute value, else max value is 2^bit."
  echo "Example:"
  echo "  $0 pgm_files/ 4 1 0 0"
  exit
fi

create_parent="1"
plot="1"
real="0"
if [ ! -z "$3" ]; then
  create_parent="$3"
fi
if [ ! -z "$4" ]; then
  plot="$4"
fi
if [ ! -z "$5" ]; then
  real="$5"
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
  ./pgm_compress.out $2 $base $real < $i

  new_name="${base}_${2}-bit.pgm"

  if [ "$create_parent" == "1" ]; then
    parent="$(basename "$(dirname "$i")")"
    if [ ! -d "$parent" ]; then
      mkdir "$parent"
    fi
    mv "$new_name" "${parent}/$new_name"
    echo "${parent}/$new_name" >> /tmp/files.txt
  else
    echo "$new_name" >> /tmp/files.txt
  fi

done

./pgm_histogram.out $plot < /tmp/files.txt

gnuplot plot_script.gpi
