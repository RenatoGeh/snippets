#include <cstdio>
#include <cstdlib>
#include <cstring>

/* Creates a histogram of pixel colors of a set of PGM images. */
int main(int argc, char *args[]) {
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
    ++max;
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

  if (argc > 1) {
    int plot = atoi(args[1]);
    if (!plot) goto end;
    puts("Creating hist.dat file for gnuplot...");

    FILE *dat = fopen("hist.dat", "w");
    fputs("# Gnuplot dat file for PGM grayscale usage histogram.\n", dat);
    fputs("# Intensity  Counts\n", dat);
    for (int i = 0; i < max; ++i)
      fprintf(dat, "%9d  %d\n", i, hist[i]);
    fclose(dat);

    puts("Creating gnuplot script...");
    FILE *script = fopen("plot_script.gpi", "w");
    fprintf(script, "set title \"PGM grayscale usage for pgm-%d images.\"\n", max);
    fprintf(script, "set xrange [0:%d]\nset auto y\n", max-1);
    fprintf(script, "set style data histogram\nset term png\nset output \"histogram.png\"\n");
    fprintf(script, "set xlabel \"Counts of each intensity\"\nset ylabel \"Counts axis\"\n");
    fprintf(script, "set boxwidth 0.5 relative\nset style fill solid 0.5\nunset key\n");
    fprintf(script, "set xtics rotate\nset x2tics\nset x2label \"Intensities\"\n");
    fprintf(script, "set x2range [0:%d]\n", max-1);
    //fprintf(script, "set terminal png size 5000,5000\n");
    fprintf(script, "plot \"hist.dat\" [0:255] using 0:2:1:xticlabels(2) with boxes lc variable\n");
    fclose(script);
  }

end:
  free(hist);

  return 0;
}
