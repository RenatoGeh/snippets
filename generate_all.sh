#!/bin/bash

function gen_ctags {
  echo "Generating $1 ctags at $2..."
  ctags -R --sort=yes --c++-kinds=+p --fields=+iaS --extras=+q --language-force=C++ -f $1 $2
}

gen_ctags gl /usr/include/GL/   # for OpenGL
gen_ctags sdl /usr/include/SDL/ # for SDL
gen_ctags qt4 /usr/include/qt4/ # for QT4
gen_ctags boost /usr/include/boost/ # for Boost

echo "Done."
