#include <stdio.h>
#include <stdlib.h>

#define MAX 255
#define WHITE 255
#define BLACK 0
#define GRAY  125

int parse_args(int argc, char *args[], int *w, int *h, FILE **fout, int **p) {
  int k, i;

  *w = atoi(args[1]);
  *h = atoi(args[2]);
  *fout = fopen(args[3], "w");

  k = argc-4;
  *p = (int*) malloc(k*sizeof(int));
  for (i = 0; i < k; i++)
    (*p)[i] = atoi(args[i+4]);

  return k;
}

int main(int argc, char *args[]) {
  int i;
  int w, h, n, k;
  FILE *fout;
  int *p, *q;

  if (argc < 5) {
    printf("Usage: %s w h fout [p1 p2 ... pn]\n"
        "  w    - image width\n"
        "  h    - image height\n"
        "  fout - output filename\n"
        "  p    - pixel indeces\n", args[0]);
    exit(1);
  }

  k = parse_args(argc, args, &w, &h, &fout, &p);
  n = w * h;

  q = (int*) malloc(n*sizeof(int));
  for (i = 0; i < n; i++)
    q[i] = WHITE;
  for (i = 0; i < k; i++)
    q[p[i]] = GRAY;

  fprintf(fout, "P2\n%d %d\n%d\n", w, h, MAX);

  for (i = 0; i < n; i++) {
    fprintf(fout, "%3d", q[i]);
    if (!((i+1) % w)) fputc('\n', fout);
    else fputc(' ', fout);
  }

  return 0;
}
