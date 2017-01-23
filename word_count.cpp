#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_STR_LEN 100
#define STR(s) #s

typedef struct {
  char *s;
  int c;
} pair;

int cmp(const void *l, const void *r) {
  return ((pair*) r)->c - ((pair*) l)->c;
}

int main(int argc, char *args[]) {
  if (argc < 2) {
    printf("Usage %s: filename [maxlen]\n"
        "  filename - vocabulary file name\n"
        "  maxlen   - max word length (default " STR(MAX_STR_LEN) ")\n", args[0]);
    return 1;
  }

  FILE *f = fopen(args[1], "r");

  if (f == NULL) {
    printf("Failed to load file [%s].\n", args[1]);
  }

  int n;
  fscanf(f, "%d", &n);

  pair *voc = (pair*) malloc(n * sizeof(pair));
  int max_len = argc > 2 ? atoi(args[2]) : MAX_STR_LEN;
  int msample_len = 0;

  for (int i=0;i<n;++i) {
    char *str = (char*) malloc(max_len * sizeof(char));
    int j;
    fscanf(f, "%d %s", &j, str);
    int l = strlen(str);
    if (l > msample_len) msample_len = l;
    voc[j].s = str;
    voc[i].c = 0;
  }

  int m;
  fscanf(f, "%d", &m);

  for (int i=0;i<m;++i) {
    int w;
    fscanf(f, "%d", &w);
    ++voc[w].c;
  }

  qsort(voc, n, sizeof(pair), cmp);

  printf("Frequencies: word -> count  (percentage).\nVocabulary size: %d\nTotal word count: %d\n"
      "==================================\n", n, m);
  char fmt[30];
  sprintf(fmt, "%%-%ds -> %%4d  (%%06.3f %%%%)\n", msample_len);
  for (int i=0;i<n;++i)
    printf(fmt, voc[i].s, voc[i].c, 100.0*((double) voc[i].c) / n);

  for (int i=0;i<n;++i)
    free(voc[i].s);
  free(voc);

  return 0;
}
