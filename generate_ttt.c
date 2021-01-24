#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_LENGTH 9
#define LINE_MAX_LENGTH 28

#define X_MARK 1
#define O_MARK 2
#define BLANK 0
#define DRAW -1
#define BOTH 0

#define bool char
#define true 1
#define false 0

/* List. */
struct _list_node {
  char line[LINE_MAX_LENGTH];
  struct _list_node *next;
};
typedef struct _list_node List;

/* Constructor for List. */
List* new_list(void) {
  List *l = (List*) malloc(sizeof(List));
  l->line[0] = '\0';
  l->next = NULL;
  return l;
}

/* Destructor for List. */
void free_list(List *l) {
  List *t, *n = l;
  while (n != NULL) {
    t = n;
    n = n->next;
    free(t);
  }
}

/* Push new element to list, appending to previously last node and returning current last node. */
List* push(List *l, char *line) {
  List *n = new_list();
  if (l == NULL) {
    n->next = new_list();
    strcpy(n->line, line);
    return n->next;
  }
  strcpy(n->line, line);
  l->next = n;
  return n;
}

/* Returns whether the given positions are a winning position. */
#define win_pos(b, i, j, k, w) ((((b)[(i)]) == w) && ((((b)[(j)]) == w) && (((b)[(k)]) == w)))
/* Returns whether the current board is a winning board. */
bool won(char board[BOARD_LENGTH], int w) {
  /* Rows */
  if (win_pos(board, 0, 1, 2, w) || win_pos(board, 3, 4, 5, w) || win_pos(board, 6, 7, 8, w))
    return true;
  /* Columns */
  if (win_pos(board, 0, 3, 6, w) || win_pos(board, 1, 4, 7, w) || win_pos(board, 2, 5, 8, w))
    return true;
  /* Diagonals */
  return win_pos(board, 0, 4, 8, w) || win_pos(board, 2, 4, 6, w);
}

/* End of game. Returns X_MARK if X wins, O_MARK if O wins, BLANK if game not yet finished, DRAW if
 * current game has come to a draw. */
int eog(char board[BOARD_LENGTH]) {
  int i;
  if (won(board, X_MARK)) return X_MARK;
  else if (won(board, O_MARK)) return O_MARK;
  for (i = 0; i < BOARD_LENGTH; ++i)
    if (board[i] == BLANK)
      return BLANK;
  return DRAW;
}

/* Square to character. */
#define stoc(x) (x) == 0 ? 'b' : (x) == 1 ? 'x' : 'o'
/* Human readable square to character. */
#define hstoc(x) (x) == 0 ? ' ' : (x) == 1 ? 'x' : 'o'

/* Board to line. */
List* btol(List *prev, char board[BOARD_LENGTH]) {
  int i;
  char c[BOARD_LENGTH];
  char line[LINE_MAX_LENGTH];
  for (i = 0; i < BOARD_LENGTH; ++i)
    c[i] = stoc(board[i]);
  sprintf(line, "%c,%c,%c,%c,%c,%c,%c,%c,%c,%s\n", c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7],
      c[8], won(board, X_MARK) ? "positive" : "negative");
  return push(prev, line);
}

/* Write all List contents to file. */
void write(const char *filename, List *l) {
  List *n;
  FILE *f;
  n = l;
  f = fopen(filename, "w");
  if (f == NULL) {
    puts("Error writing to file");
    exit(1);
  }
  while (n != NULL) {
    fputs(n->line, f);
    n = n->next;
  }
  fclose(f);
}

/* Copy board. */
void cpybrd(char dst[BOARD_LENGTH], char src[BOARD_LENGTH]) {
  int i;
  for (i = 0; i < BOARD_LENGTH; ++i)
    dst[i] = src[i];
}

/* Reset board. */
void rstbrd(char b[BOARD_LENGTH]) {
  int i;
  for (i = 0; i < BOARD_LENGTH; ++i) b[i] = BLANK;
}

/* Next player. If 1, switch to 2; if 2 switch to 1. */
#define nwho(x) 2+((1-(x)))%2

int length(List *head) {
  int i;
  List *l = head->next;
  for (i = 0; l != NULL; ++i)
    l = l->next;
  return i;
}

/* Simulate game trace. */
List* simulate(List *prev, char b[BOARD_LENGTH], int who) {
  int i, m, r;
  char c[BOARD_LENGTH];
  List *tail;

  r = eog(b);
  if (r != BLANK)
    return btol(prev, b);

  m = nwho(who);
  tail = prev;
  cpybrd(c, b);
  for (i = 0; i < BOARD_LENGTH; ++i)
    if (c[i] == BLANK) {
      c[i] = m;
      tail = simulate(tail, c, m);
      c[i] = BLANK;
    }

  return tail;
}

/* Print board. */
void printb(char b[BOARD_LENGTH]) {
  int i;
  for (i = 0; i < 3; ++i)
    printf(" %c | %c | %c\n", hstoc(b[3*i]), hstoc(b[3*i+1]), hstoc(b[3*i+2]));
}

/* Print help/usage message. */
void printh(char *bin) {
  printf("Usage: %s file [-x|-o|-2]\n"
      "  Positional arguments:\n"
      "    file - CSV file to save output to\n"
      "  Optional flags:\n"
      "    -x   - only save game traces where X starts\n"
      "    -o   - only save game traces where O starts\n"
      "    -2   - save both game traces\n", bin);
}

int main(int argc, char *args[]) {
  int i;
  char b[BOARD_LENGTH], which;
  char* filename;
  List *head;

  if (argc == 1) {
    printh(args[0]);
    exit(0);
  }

  /* Parse arguments. */
  which = X_MARK;
  for (i = 1; i < argc; ++i)
    if (!strcmp(args[i], "-h") || !strcmp(args[i], "--help")) {
      printh(args[0]);
      exit(0);
    } else if (!strcmp(args[i], "-o"))
      which = O_MARK;
    else if (!strcmp(args[i], "-2"))
      which = BOTH;
  filename = args[1];

  head = new_list();
  for (i = 0; i < BOARD_LENGTH; ++i) b[i] = BLANK;

  if (which == BOTH)
    simulate(simulate(head, b, X_MARK), b, O_MARK);
  else
    simulate(head, b, which);

  printf("Length of list: %d\n", length(head));
  write(filename, head->next);

  free_list(head);

  return 0;
}
