#include <cstdio>
#include <cstdlib>

/* Takes a .voc file and prunes vocabulary down to k most frequent words. Any other words are
 * classified as <unk>. */

typedef struct {
  int index;
  int freq;
  char *str;
} word;

int word_cmp(const void *l, const void *r) {
  return ((word*) r)->freq - ((word*) l)->freq;
}

int main(int argc, char *args[]) {
  if (argc == 1 || argc < 5) {
    printf("Usage: %s filename outname k maxlen [delete]\n"
           "  filename - .voc input filename path.\n"
           "  outname - .voc output filename path.\n"
           "  k - the number of most frequent words to be kept.\n"
           "  maxlen - the maximum length for a word in filename.\n"
           "  delete - (int) whether to actually delete or simply flag it as <unk>.\n", args[0]);
    return 1;
  }

  FILE *voc = fopen(args[1], "r");
  int n;
  fscanf(voc, "%d", &n);

  word *vocab = (word*) malloc(n * sizeof(word));
  const int MAX_LEN = atoi(args[4]);
  for (int i=0;i<n;++i) {
    vocab[i].str = (char*) malloc(MAX_LEN * sizeof(char));
    vocab[i].freq = 0;
  }

  for (int i=0;i<n;++i) {
    int j;
    fscanf(voc, "%d ", &j);
    vocab[j].index = j;
    fscanf(voc, "%s", vocab[j].str);
  }

  int m;
  fscanf(voc, "%d", &m);

  int *text = (int*) malloc(m * sizeof(int));
  for (int i=0;i<m;++i) {
    int j;
    fscanf(voc, "%d", &j);
    ++vocab[j].freq;
    text[i] = j;
  }

  qsort(vocab, n, sizeof(word), word_cmp);

  FILE *out = fopen(args[2], "w");
  const int k = atoi(args[3]);
  int *has = (int*) malloc(n * sizeof(int));
  for (int i=0;i<n;++i) has[i] = -1;
  const int del = argc == 5 ? 0 : atoi(args[5]);

  fprintf(out, "%d\n", del? k : k+1);
  for (int i=0;i<k;++i) {
    fprintf(out, "%d %s\n", i, vocab[i].str);
    has[vocab[i].index] = i;
  }
  if (!del)
    fprintf(out, "%d <unk>\n", k);

  for (int i=0;i<n;++i)
    free(vocab[i].str);

  fprintf(out, "%d\n", m);

#define LINE_LEN 100
  int l = 0;
  for (int i=0;i<m;++i) {
    int w = has[text[i]];
    if (w >= 0) {
      fprintf(out, "%d", w);
      ++l;
    } else if (!del)
      fprintf(out, "%d", k);
    else continue;

    if ((l+1) % LINE_LEN == 0)
      fputc('\n', out);
    else
      fputc(' ', out);
  }
#undef LINE_LEN

  free(has);
  free(text);
  free(vocab);

  fclose(out);

  return 0;
}
