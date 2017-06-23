#include <cstdio>
#include <cstdlib>
#include <ctime>

#define N 4
#define FILENAME_SIZE 100

#define str(a) #a
#define xstr(a) str(a)

void draw(int i, int n, int m, int *b) {
  char fname[FILENAME_SIZE];
  sprintf(fname, "b%02dx%02d_n%03d_i%03d.pgm", N, N, n, i);
  FILE *out = fopen(fname, "w");
  fprintf(out, "P2\n" xstr(N) " " xstr(N) "\n1\n");
  for (int j=0;j<m;++j) {
    fprintf(out, "%d", b[j]);
    fputc((j+1) % N == 0 ? '\n' : ' ', out);
  }
  fclose(out);
}

int main(int argc, char *args[]) {
  if (argc != 2) {
    printf("Generates " xstr(N*N-1) " distinct instances of an " xstr(N) "x" xstr(N) " square with"
        "n random black squares in random distinct positions.\n"
        "Usage: %s n\n"
        "  n - number of random black squares\n", args[0]);
    return 1;
  }

  int m = N*N;
  int n = atoi(args[1]);
  int k = n % (m - 1);
  int *b = new int[m];

  // Edge cases. If k = 0, all squares are 1 except for one 0 square. If k = 1, all squares are 0
  // except for one 1 square. In both cases, there are N-1 possible permutations.
  if (k < 2) {
    for (int i=0;i<m;++i) b[i] = !k;
    b[0] = k;
    for (int i=1;i<m;++i) {
      draw(i, n, m, b);
      b[i-1] = !k;
      b[i] = k;
    }
    draw(m, n, m, b);
  } else /* general case */ {
    // b is the NxN board. We can see it as an integer in binary form. To select N-1 random
    // configurations of b with n black squares, it is sufficient to select N-1 numbers whose
    // binary form has only n 1-bits. Therefore, a configuration is unique and has a bijection with
    // its binary form. To check if a configuration has already been selected, it is sufficient to
    // check if its binary form has already been selected.
    int *c = new int[m-1]();
    int s;
    for (int j=0;j<m;++j) {
      bool ok = false;
      while (!ok) {
        for (int i=0;i<m;++i) b[i] = 0;
        for (int i=0;i<k;++i) {
          int v;
          do v = rand() % m; while(b[v]);
          b[v] = 1;
        }
        int t = 1;
        s = 0;
        for (int i=0;i<k;++i) {
          s += t*b[i];
          t <<= 1;
        }
        ok = true;
        for (int i=0;i<N-1;++i)
          if (c[i] == s) {
            ok = false;
            break;
          }
      }
      c[j] = s;
      draw(j, n, m, b);
    }
  }

  return 0;
}
