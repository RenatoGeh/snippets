#!/bin/bash

if [ "$#" -lt 5 ] || [ "$#" -gt 6 ]; then
  echo "Usage: $0 w h m f k d"
  echo "  w - width of the PGM image"
  echo "  h - height of the PGM image"
  echo "  m - max pixel value"
  echo "  f - filename output"
  echo "  k - number of generated instances"
  echo "  d - debug mode, true or false"
fi

w=$1
h=$2
m=$3
n=$(($w*$h - 1))
path=$4
k=$5

if [ "$#" -eq 6 ]; then
  DEBUG=$6
else
  DEBUG=false
fi

:> "$path"
for i in $(seq 0 $n); do
  echo "var $i $m" >> "$path"
done
for j in $(seq 1 $k); do
  data=""
  if $DEBUG; then
    dbg_f="pgm_out_$j.pgm"
    :> "$dbg_f"
    printf "P2\n$w $h\n$m\n" > "$dbg_f"
  fi

  for i in $(seq 0 $n); do
    data="$data$((RANDOM % $m))"
    if (( $i == $n )); then
      data=$data$'\n'
    else
      data="$data "
    fi
  done
  echo -n "$data" >> "$path"
  if $DEBUG; then
    echo -n "$data" >> "$dbg_f"
  fi
done
