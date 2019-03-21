#include <ncurses.h>

#define MAXTEXT 8192
#define TXTFILE "lobstrosity.txt"
#define MAXLINELEN 75

bool init_ncurses(WINDOW *priscr) {
  /*
   * curses setup for initialization utilizing a screen that will have a half-
   * second pause when displaying any error message regarding inability to
   * init curses mode/capability when started up
   */

  priscr = initscr();   /* init curses library */
  keypad(priscr, TRUE); /* keyboard mapping */
  (void) nonl();        /* no NL->CR/NL on output */
  (void) noecho();      /* do not echo input */
  (void) halfdelay(25); /* wait 2.5 sec before carrying on w/out input to getch */

  /* ouahful variable */
  bool guhupdown;

  #ifdef DEBUGGING
	mvaddstr(0, 0, "In init_ncurses");
  #endif

  guhupdown = has_colors();
  if (guhupdown) {
        /* init color subsystem */
        start_color();

        init_pair(0, COLOR_RED, COLOR_BLACK);
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_YELLOW, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        init_pair(4, COLOR_CYAN, COLOR_BLACK);
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(6, COLOR_WHITE, COLOR_BLACK);

        return true;
  } else {
        mvaddstr(12, 15, "No color capability detected!");
        mvaddstr(13, 20, "Hit a key, por favor . . .");

        refresh();
        (void) getch();

        clear();
        refresh();

        return false;
  }
}
