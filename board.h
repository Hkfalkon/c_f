#ifndef BOARD_H
#define BOARD_H

#include <curses.h>
#include <stdlib.h>

typedef struct {
	int	rows, cols;	// 領域の行数・列数
	int	len;		// 目標とする連結数
	int	*cell;		// 領域の配列
	int	*count;		// 各列の積石数
	int	space;		// 空き領域数
} Board;

extern Board *BdNew(int r, int c, int n);
extern void BdFree(Board *b);
extern int BdSet(Board *b, int r, int c, int v);
extern int BdGet(Board *b, int r, int c);
extern int BdDraw(int y, int x, Board *b);
extern int BdJudge(Board *b, int y, int x);
extern int BdDrop(Board *b, int x, int v);

#endif

