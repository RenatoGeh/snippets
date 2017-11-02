#!/bin/bash

pimg="pimg.pgm"
cimg="cimg.pgm"
w=$1
h=$2
n=$(( w*h ))
max=255
pcolor=64
ccolor=128
psc=( $3 )
csc=( $4 )

:> "$pimg"
:> "$cimg"

printf "P2\n%d %d\n%d\n" $w $h $max | tee "$pimg" "$cimg" > /dev/null

declare -a pvals
for ((i=0;i<n;i++)) do
  pvals[i]=0
done
for i in ${psc[@]}; do
  pvals[i]=$pcolor
done
for ((i=0;i<n;i++)) do
  printf "%d " ${pvals[i]} >> $pimg
done

declare -a cvals
for ((i=0;i<n;i++)) do
  cvals[i]=0
done
for i in ${csc[@]}; do
  cvals[i]=$ccolor
done
for ((i=0;i<n;i++)) do
  printf "%d " ${cvals[i]} >> $cimg
done
