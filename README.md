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

12. `has_duplicate.sh`:
  - Given a set of files F, let i and j in F be distinct files.
    `has_duplicate.sh` returns whether there exists i and j such that
    the contents of i are equal to those of j.

13. `cat_sq_gen.sh`:
  - For every possible n black squares configurations in a square of
    `NxN` dimension, create a category for each n and output `N^2`
    configurations into their respective categories.

14. `pgm2data.sh`:
  - Generates k random PGM images given a width, height and maximum pixel
    value.
  - Debug mode generates individual PGM files for visualization.
  - Compiles the k images into a `.data` file as specified in
    <https://github.com/RenatoGeh/gospn>.

15. `unique_id.go`:
  - Tests a one-to-one and onto function for subrectangles in a
    rectangle.

16. `split_audio.sh`:
  - Takes an audio or video `f` and splits it into pieces.
  - Every timestamp given as argument splits `f` from the previous
    timestamp to the next timestamp.
  - Great for splitting a single file album audio into multiple singles!

17. `extract_ty.sh`:
  - Takes a YouTube URL, downloads the video, extracts the audio (`.mp3`)
    and splits it into different sections based on timestamps.
  - Uses `split_audio.sh` to split it by timestamps.

18. `diff_cmp.sh`:
  - Takes a directory and an expression. Finds all same name files from
    current directory and given directory. For each of these files, use
    NeoVim's diff tool.
  - Useful for manually applying patches from different branches of the
    same repository.

19. `draw_scope.sh`:
  - Draws the assigned pixels in a `w x h` image.
