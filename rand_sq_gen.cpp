#include <cstdio>
#include <cstdlib>
#include <ctime>

#ifndef N
#define N 4
#endif
#define xstr(a) str(a)
#define str(a) #a

// First argument is number of black squares.
int main(int argc, char *args[]) {
  if (argc != 3) {
    printf("Generates " xstr(N) "x" xstr(N) "PGM images with n random black squares.\n"
        "Usage: %s n filename\n"
        "  n        - number of black squares\n"
        "  filename - output file name\n", args[0]);
    return 1;
  }

  int n = atoi(args[1]);
  srand(time(NULL));

  FILE *out = fopen(args[2], "w");
  fprintf(out, "P2\n" xstr(N) " " xstr(N) "\n1\n");

  int sq = N*N;
  int *m = new int[sq];
  for (int i=0;i<sq;++i) m[i] = 0;
  for (int i=0;i<n;++i) {
    int v;
    do v = rand()%sq; while (m[v]);
    m[v] = 1;
  }

  for (int i=0;i<sq;++i) {
    fprintf(out, "%d", m[i]);
    fputc((i+1) % N == 0 ? '\n' : ' ', out);
  }

  fclose(out);

  return 0;
}
