#!/bin/bash

shopt -s nullglob
folds=(*)

#max_x=0
#max_y=0
#for f in */*; do
  #if [[ -f $f && $f == *.jpg ]]; then
    #info=`file $f`
    ##echo "$f"
    #[[ "$info" =~ ([0-9]{2,}+x[0-9]+) ]]
    #dim="${BASH_REMATCH[1]}"
    #[[ "$dim" =~ ([0-9]+) ]]
    #x="${BASH_REMATCH[1]}"
    #[[ "$dim" =~ (x[0-9]+) ]]
    #y="${BASH_REMATCH[1]}"
    #y=${y:1}
    ##echo "$x x $y"
    #if [ "$x" -gt "$max_x" ]; then
      #let max_x=$x
      ##echo "New max_x: $max_x"
    #fi
    #if [ "$y" -gt "$max_y" ]; then
      #let max_y=$y
      ##echo "New max_y: $max_y"
    #fi
  #fi
#done

#ratio=$(( max_y / max_x ))
x=100
y=100
#y=$(( x * ratio ))
#y=$( printf "%.0f" y )
#echo "Set max dimensions as (${max_x},${max_y})."
#echo "Ratio of height/width: ${ratio}."
#echo "Real dimensions: (${x},${y})."

for dir in "${folds[@]}"; do
  if [[ -d "$dir" ]]; then
    for f in ${dir}/*; do
      if [[ -f $f && $f == *.jpg ]]; then
        filename=$(basename "$f")
        base="${filename%.*}"
        convert "$dir/${base}.jpg" -resize ${x}x${y}\! "$dir/${base}.pgm"
        echo "Converted $dir/${base}.jpg to $dir/${base}.pgm"
      fi
    done
  fi
done
