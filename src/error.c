#include "token.h"
#include <stdio.h>
#include <string.h>

#include "zasm.h"

#define COLOR_RESET  "\x1b[0m"
#define COLOR_BOLD   "\x1b[1m"
#define COLOR_GRAY   "\x1b[90m"
#define COLOR_RED    "\x1b[91m"
#define COLOR_YELLOW "\x1b[93m"
#define COLOR_BLUE   "\x1b[94m"

int int_len(int x) {
  int len = 0;
  if (x <= 0)
    len++;
  while (x) {
    len++;
    x /= 10;
  }
  return len;
}

void repeat(char *c, int count) {
  for (int i = 0; i < count; i++)
    fprintf(stderr, "%s", c);
}

static void find_line(zasm_file f,
                      const char *pos,
                      const char **line_start,
                      const char **line_end,
                      int *column) {
  const char *p = pos;
  while (p > (const char *)f.data && p[-1] != '\n')
    p--;
  *line_start = p;
  *line_end = strchr(pos, '\n');
  *column = (int)(pos - *line_start) + 1;
}

void zasm_error(zasm_file f, zasm_token tok, const char *message) {
  const char *line_start;
  const char *line_end;
  int        column;

  find_line(f, tok.start, &line_start, &line_end, &column);
  fprintf(stderr, "%*s", int_len(tok.line) + 1, "");
  fprintf(stderr, COLOR_BOLD "--> " COLOR_RESET COLOR_BLUE "%s" COLOR_RESET ":"
          COLOR_YELLOW "%d" COLOR_RESET ":" COLOR_YELLOW "%d" COLOR_RESET,
          f.name, tok.line, column);
  fprintf(stderr, COLOR_BOLD COLOR_RED " Syntax Error\n" COLOR_RESET);
  fprintf(stderr, " " COLOR_BOLD "%d | " COLOR_RESET, tok.line);
  fprintf(stderr, "%.*s", column - 1, line_start);
  fprintf(stderr, COLOR_RED "%.*s" COLOR_RESET, (int)tok.len, tok.start);
  fprintf(stderr, "%.*s\n", (int)(line_end - (tok.start + tok.len)), tok.start + tok.len);
  repeat((char *)" ", int_len(tok.line) + 2);
  fprintf(stderr, COLOR_BOLD "|" COLOR_RESET);
  repeat((char *)" ", column);
  fprintf(stderr, COLOR_RED "^");
  repeat((char *)"~", tok.len - 1);
  fprintf(stderr, COLOR_RED " %s\n\n" COLOR_RESET, message);
}

