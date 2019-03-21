#include <stdio.h>
#include <ncurses.h>
#include "lobstrosity.h"

int main() {
  WINDOW *headsUp;

  init_ncurses(headsUp);

  mvaddstr(12, 25, "Success!  Hit a key . . .");
  refresh();
  (void) getch();

  clear();
  refresh();

  endwin();

  return 0;
}

