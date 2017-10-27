#!/bin/bash

if [[ $# -lt 2 ]]; then
  echo "Usage: $0 filename [timestamps]"
  echo "  filename   - audio filename"
  echo "  timestamps - list of timestamps of filename to be cut"
  exit 1
fi

stamps=( "$@" )
fname=$1
fnamenex=${fname%.*}
stamps=( ${stamps[@]/$fname} )
t=0
min=0
sec=0
i=0

# Get audio duration
echo "Audio: $fname"
ufdx=`ffmpeg -i $fname 2>&1 | grep Duration | awk '{print $2}' | tr -d ,`
echo "Duration: $ufdx"
echo "Clipping audio bits:"

pp="00:00"
for s in "${stamps[@]}"; do
  echo "From $pp"
  echo "  to $s"
  fout="${fnamenex}_${i}.mp3"
  echo $fname
  ffmpeg -i $fname -ss "$pp" -to "$s" -c copy $fout
  echo "Outputting audio to $fout."
  pp="$s"
  let i=i+1
done

echo "From $t seconds till end of file:"
fout="${fnamenex}_${i}.mp3"
ffmpeg -i $fname -ss "$pp" -to "$ufdx" -c copy $fout
echo "Outputting audio to $fout."
echo "Created $i output files."
