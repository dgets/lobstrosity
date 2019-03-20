/*
 * by: Damon Getsman
 * started on: 19mar19 6:45am
 * finished:
 * The lobster typing tutor that I do so miss from my youth
 */

#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "my-nc_lobstutor.h"

/*
 * as of right now this simply checks to verify that there are enough rows and
 * columns to display things properly
 *
 * returns false if unable to hold a proper display
 */
bool test_capability(void) {
  if (MaxLines <= 10 || MaxCols < 40) {
	return false;
  }

  return true;
}

/*
 * reads the text file into a buffer and returns a pointer to it
 */
char* init_buffer(void) {
  FILE *tFile;
  char tBuf[MaxText + 1];

  tFile = fopen(TFileName, "r");
  if (tFile == NULL) {
    return NULL;
  }

  if (fread(tBuf, 1, MaxText, tFile) < 512) {
    //not enough text for an accurate assessment
    return NULL;
  }

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

  if (ouah > (MaxLen - 4)) {
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
 *
 * NOTE: this does not handle the status portions of the display, nor border
 */
void init_screen(char *tBuf) {
  int bufPos = 0;

  //five lines for status
  for (int lineNo = 5; lineNo <= (MaxLines - 3); lineNo += 3) {
	
