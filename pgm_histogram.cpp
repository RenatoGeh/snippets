#include <cstdio>
#include <cstdlib>
#include <cstring>

/* Creates a histogram of pixel colors of a set of PGM images. */
int main() {
  int *hist, n;

  scanf("%d ", &n);
  hist = NULL;

  FILE *pgm;
  int max;
  for (int i = 0; i < n; ++i) {
    char filename[100];
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = '\0';
    pgm = fopen(filename, "r");

    int w, h;
    fscanf(pgm, "P2 %d %d %d", &w, &h, &max);

    if (hist == NULL) {
      hist = (int*) malloc(max*sizeof(int));
      for (int j = 0; j < max; ++j)
        hist[j] = 0;
    }

    int m = w*h;
    for (int j = 0; j < m; ++j) {
      int p;
      fscanf(pgm, "%d", &p);
      ++hist[p];
    }

    fclose(pgm);
  }

  printf("PGM histogram for pgm-%d images.\n", max);
  for (int i = 0; i < max; ++i)
    printf("  [%d] = %d\n", i, hist[i]);
  puts("End of PGM histogram.");
  free(hist);

  return 0;
}
