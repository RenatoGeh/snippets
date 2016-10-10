# Snippets

1. `pgm_compress.cpp`:
  - Compresses PGM image files to an n-bit new PGM.

2. `pgm_histogram.cpp`:
  - Prints histogram of color usage of a set of grayscale PGM images files.

3. `rcompress.sh`:
  - Recursively find each PGM file in a given directory.
  - Creates an n-bit compressed PGM of each found PGM file.
  - Constructs a histogram out of all such PGM n-bit files.
  - Prints histogram to the `stdin`.
