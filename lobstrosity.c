/*
 * by: Damon Getsman
 * started on: 19mar19 6:45am
 * finished:
 * The lobster typing tutor that I do so miss from my youth
 */

#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "lobstrosity.h"

/*
 * as of right now this simply checks to verify that there are enough rows and
 * columns to display things properly
 *
 * returns false if unable to hold a proper display
 */
/*bool test_capability(void) {
  if (MaxLines <= 10 || MaxCols < 40) {
	return false;
  }

  return true;
}*/

/*
 * reads the text file into a buffer and returns a pointer to it
 */
char* init_buffer(void) {
  FILE *tFile;
  char tBuf[MAXTEXT + 1];

  tFile = fopen(TXTFILE, "r");
  if (tFile == NULL) {
    fclose(tFile);
    return NULL;
  }

  if (fread(tBuf, 1, MAXTEXT, tFile) < 512) {
    /* not enough text for an accurate assessment */
    fclose(tFile);
    return NULL;
  }

  fclose(tFile);

  return tBuf;
}

/*
 * determines the position of the last non-whitespace character in a string
 * and returns it
 *
 * if the string is too long to display -1 is returned
 */
int determine_last_whitespace_pos(char *segment) {
  int ouah = strlen(segment);
  int pos;

  if (ouah > (MAXLINELEN - 4)) {
	return -1;
  }

  /* note that the following does not take \n or other non-space & non-tabbed
   * whitespace into account */
  for (pos = (ouah - 1); segment[pos] != ' ' && segment[pos] != '\t'; pos--) {
	/* this will leave us at the final whitespace in the string */
	if (pos < 0) {
		return -2;
	}
  }
  for (; segment[pos] == ' ' || segment[pos] == '\t'; pos--) {
	if (pos < 0) {
		return -2;
	}
  }

  return pos;
}

/*
 * initializes the display with the properly formatted text file contents
 * returns NULL instead of the buffer if not successful
 *
 * NOTE: this does not handle the status portions of the display, nor border
 */
char* init_screen(/*char *tBuf,*/ WINDOW *headsUp) {
  int bufPos = 0;
  char fullTextBuf[MAXTEXT + 1];

  if (!init_ncurses(headsUp)) {
	printf("\nUnable to initialize ncurses on this terminal.\n");
	return NULL;
  }

  int MaxCols = (int)getmaxx(headsUp);
  int MaxLines = (int)getmaxy(headsUp);
  char lineBuf[MaxCols - 4];

  fullTextBuf = init_buffer();
  if (fullTextBuf == NULL) {
	endwin();
	printf("\nUnable to read text for tutor utilization.\n");
	return NULL;
  }

  /* five lines for status */
  for (int lineNo = 5; lineNo <= (MaxLines - 3); lineNo += 3) {
	/* not sure that this will do what I need here, but it's a start to
	 * fleshing things out a bit, at least */
	strncpy(lineBuf, fullTextBuf[bufPos], (MaxCols - 4));
	bufPos += (MaxCols - 4);

	mvprintw(lineNo, 2, lineBuf);
  }

  return fullTextBuf;
}

/* program entry point */
int main(void) {
  WINDOW *headsUp; 

  if (!init_screen(headsUp)) {
	endwin();
	printf("Error is preventing proper program execution.");
	return 1;
  }

  /* constants */
  const int MaxCols = (int)getmaxx(headsUp);
  const int MaxLines = (int)getmaxy(headsUp);

  endwin();
  return 0;
}

