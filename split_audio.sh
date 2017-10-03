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
dmin=`echo $ufdx | cut -d':' -f2`
dsec=`echo $ufdx | cut -d':' -f3 | perl -nl -MPOSIX -e 'print ceil($_);'`
dx=$(( dmin*60+dsec ))
echo "Duration: $dx"
echo "Clipping audio bits:"

pp="00:00"
for s in "${stamps[@]}"; do
  echo "From $min minutes and $sec seconds ($t secs)"
  min=`echo $s | cut -d'.' -f1`
  sec=`echo $s | cut -d'.' -f2`
  l=$(( min*60+sec ))
  echo "  to $min minutes and $sec seconds ($l secs)"
  fout="${fnamenex}_${i}.mp3"
  echo $fname
  ffmpeg -i $fname -ss "$pp" -to "$min:$sec" -c copy $fout
  echo "Outputting audio to $fout."
  let t=l
  pp="$min:$sec"
  let i=i+1
done

echo "From $t seconds till end of file:"
fout="${fnamenex}_${i}.mp3"
ffmpeg -i $fname -ss "$pp" -to "$ufdx" -c copy $fout
echo "Outputting audio to $fout."
echo "Created $i output files."
