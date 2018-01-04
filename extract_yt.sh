#!/bin/bash

if [[ $# -eq 2 ]]; then
  # Just an easy alias to youtube-dl.
  youtube-dl --audio-quality 0 --extract-audio --audio-format mp3 --output "$2.%(ext)s" "$1"
  exit 0
fi

if [[ $# -lt 3 ]]; then
  echo "Usage: $0 url filename [timestamps]"
  echo "  url        - YouTube URL to extract"
  echo "  filename   - audio output filename"
  echo "  timestamps - list of timestamps of filename to be cut"
  exit 1
fi

echo "Extracting '$1' from YouTube..."
youtube-dl --audio-quality 0 --extract-audio --audio-format mp3 --output "$2.%(ext)s" "$1"
all=( "$@" )
stamps=( ${all[@]/$1} )
stamps=( ${stamps[@]/$2} )
echo "Splitting $2.mp3 (ts: ${stamps[@]})..."
./split_audio.sh "$2.mp3" ${stamps[@]}
echo "Removing temp files..."
rm "$2.mp3"
echo "Done!"
