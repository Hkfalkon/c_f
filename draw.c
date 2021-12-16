#define _XOPEN_SOURCE
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include "draw.h"

void Color(int id)
{
	attron(COLOR_PAIR(id));
}

void Bold(int sw)
{
	if (sw) {
		attron(A_BOLD);
	} else {
		attroff(A_BOLD);
	}
}

void DrawStr(int y, int x, int c, char *s)
{
	attron(COLOR_PAIR(c));
	mvaddstr(y, x, s);
}

#define WCSLEN	1024
int MbsWidth(char *s)
{
	wchar_t	wcs[WCSLEN];

	if (mbstowcs(wcs, s, WCSLEN) < 0) return (-1);
	return (wcswidth(wcs, WCSLEN));
}

void CenterStr(int y, int w, int c, char *s)
{
	int	n;

	n = MbsWidth(s);
	DrawStr(y, (w - n)/2, c, s);
}

