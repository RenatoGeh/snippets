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

3. `trim.sh`:
  - Trims an image with 10% fuzzy rate.

4. `jpg2pgm.sh`:
  - Resizes all files to a given (x, y) size.
  - Searches for files in directories one level down.
  - Ignores aspect ratio.

5. `count.sh`:
  - Counts number of files in directories one level down.
  - Prints each count, mean, max and min.

6. `coin.sh`:
  - For each directory inside pwd, toss a coin for each PGM file in it.
  - If heads, put it in a folder named `train` inside the directory
    being scanned.
  - If tails, put it in `test`.
  - Number of files is limited by `ntest` and `ntrain`.

7. `word_count.cpp`:
  - Takes a `.voc` file and counts word occurences (frequencies and
    percentage).

8. `prune_words.cpp`:
  - Takes a `.voc` file and rewrites it as a new vocabulary containing
    only the k most frequent words.
  - Optionally deletes words that do not meet the criterion.

9. `longest_word.sh`:
  - Searches for the longest word in a file.

10. `rand_sq_gen.cpp`:
  - Generates a `.pgm` file containing an `NxN` (where `N` is a
    defined macro) square with `n` black squares in random positions.

11. `sq_gen.cpp`:
  - Let `N` be the size of a square. `sq_gen.cpp` generates `N-1`
    distinct instances of an `NxN` square with `n` random black squares in
    random distinct positions.
