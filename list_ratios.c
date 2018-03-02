#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  int x, y;
  double r;
} dimension;

double r;

dimension* new_dimension(int x, int y, double p) {
  dimension *d;
  d = (dimension*) malloc(sizeof(dimension));
  d->x = x;
  d->y = y;
  d->r = p;
  return d;
}

void free_dimensions(dimension **D, int n) {
  int i;
  for (i = 0; i < n; ++i) free(D[i]);
  free(D);
}

int cmp_dimension(const void *d, const void *e) {
  /* The dimension that has ratio closer to the global ratio r goes first. */
  double p, q;
  p = fabs(r - (*((dimension**) d))->r);
  q = fabs(r - (*((dimension**) e))->r);
  if (p < q) return -1;
  else if (p == q) return 0;
  else return 1;
}

int main(int argc, char *args[]) {
  int w, h, d, n;
  int i, j, k;
  dimension **D;

  if (argc != 4) {
    printf("Usage: %s w h d\n"
        "  w - original width\n"
        "  h - original height\n"
        "  d - divisability factor\n", args[0]);
    exit(1);
  }

  w = atoi(args[1]);
  h = atoi(args[2]);
  d = atoi(args[3]);

  r = ((double) w) / ((double) h);
  n = (w/d - 1)*(h/d - 1);
  D = (dimension**) malloc(n*sizeof(dimension*));

  k = 0;
  for (i = d; i < w; i += d)
    for (j = d; j < h; j += d)
      D[k++] = new_dimension(i, j, ((double) i)/((double) j));

  qsort(D, n, sizeof(dimension*), cmp_dimension);
  printf("Listing closest possible dimensions with arguments: w=%d, h=%d, d=%d, r=%f\n", w, h, d, r);
  for (i = 0; i < n; i++) {
    dimension *e;
    e = D[i];
    printf("  %d: (%d, %d) -> %f <> %f\n", i, e->x, e->y, e->r, fabs(r-(e->r)));
  }

  free_dimensions(D, n);

  return 0;
}
