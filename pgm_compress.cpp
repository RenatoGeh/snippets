#include <cstdio>
#include <cstdlib>

/* Compresses PGM files.
 *
 * Example:
 *
 * Given an m-bit PGM file F:
 *
 * Let q = 2^m.
 *   | P2
 *   | 46 56
 *   | q
 *   | ...
 *
 * Compresses F into an n-bit PGM file H, with n < m:
 *
 * Let p = 2^n.
 *   | P2
 *   | 46 56
 *   | p
 *   | ...
 */
int main(int argc, char *args[]) {
  int bit = 4, max = 1;

  if (argc > 1)
    bit = atoi(args[1]);

  max <<= bit;

  int w, h, omax;
  scanf("P2 %d %d %d", &w, &h, &omax);

#define MAX_FILENAME_SIZE 50
  char filename[MAX_FILENAME_SIZE];
#undef MAX_FILENAME_SIZE

  if (argc > 2)
    sprintf(filename, "%s_%d-bit.pgm", args[2], bit);
  else
    sprintf(filename, "img_%d-bit.pgm", bit);

  FILE *out;
  out = fopen(filename, "w");
  fprintf(out, "P2\n%d %d\n%d\n", w, h, max);

  int n = w*h;
  double df = (double) max / (double) omax;
  for (int i = 0; i < n; ++i) {
    int opx;
    scanf("%d", &opx);
    double npx = (double) opx * df;
    fprintf(out, "%d", (int) npx);
    if (i % w == w-1)
      putc('\n', out);
    else
      putc(' ', out);
  }

  fclose(out);

  return 0;
}
