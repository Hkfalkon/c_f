#include <curses.h>
#include <stdlib.h>
#include "board.h"
#include "draw.h"

Board *BdNew(int r, int c, int n)
{
	Board	*b;

	b = (Board *)malloc(sizeof(Board));
	if (b == NULL) return (NULL);

	b->rows = r;
	b->cols = c;
	b->len = n;
	b->cell = NULL;
	b->count = NULL;
	b->space = r*c;

	b->cell = (int *)calloc(r*c, sizeof(int));
	if (b->cell == NULL) goto EXIT;

	b->count = (int *)calloc(c, sizeof(int));
	if (b->count == NULL) goto EXIT;

	return (b);

EXIT:
	BdFree(b);
	return (NULL);
}

void BdFree(Board *b)
{
	if (!b) return;
	free(b->count);
	free(b->cell);
	free(b);
}

int ChkPos(Board *b, int r, int c)
{
	if (r < 0) return (1);
	if (c < 0) return (1);
	if (r >= b->rows) return (1);
	if (c >= b->cols) return (1);
	return (0);
}

int BdSet(Board *b, int r, int c, int v)
{
	if (ChkPos(b, r, c)) return (-1);
	(*(b->cell + (b->cols)*r + c)) = v;

	if (v) {
		(*(b->count + c))++;
		(b->space)--;
	}
	return (v);
}

int BdGet(Board *b, int r, int c)
{
	if (ChkPos(b, r, c)) return (-1);
	return (*(b->cell + (b->cols)*r + c));
}

int BdDraw(int y, int x, Board *b)
{
	int	r, c;
	int	v;
	int	x0 = x;

	for (r = 0; r < b->rows; r++, y++) {
		x = x0;
		for (c = 0; c < b->cols; c++, x += 2) {
			v = BdGet(b, r, c);
			if (v < 0) continue;
			move(y, x);
			if (v == 0) {
				Bold(0);
				DrawStr(y, x, 7, "□ ");
			} else {
				Bold(1);
				DrawStr(y, x, v, "● ");
			}
		}
	}
	return (0);
}

// 連結数の検索
// x, y：基準位置
// dx, dy：検索方向
// return：連結数
int Len(Board *b, int y, int x, int dy, int dx)
{
	int	v;
	int	n = 0;

	v = BdGet(b, y, x);
	while (1) {
		x += dx;
		y += dy;
		if (BdGet(b, y, x) != v) break;
		n++;
	}
	return (n);
}

// +x方向の連結数
int Len1(Board *b, int y, int x)
{
	int	n = 1;
	n += Len(b, y, x, 0, +1);
	n += Len(b, y, x, 0, -1);
	return (n);
}

// (+x, +y)方向の連結数
int Len2(Board *b, int y, int x)
{
	int	n = 1;
	n += Len(b, y, x, +1, +1);
	n += Len(b, y, x, -1, -1);
	return (n);
}

// +y方向の連結数
int Len3(Board *b, int y, int x)
{
	int	n = 1;
	n += Len(b, y, x, +1, 0);
	n += Len(b, y, x, -1, 0);
	return (n);
}

// (-x, +y)方向の連結数
int Len4(Board *b, int y, int x)
{
	int	n = 1;
	n += Len(b, y, x, +1, -1);
	n += Len(b, y, x, -1, +1);
	return (n);
}

// 連結完了の判定
// x, y：基準位置
int BdJudge(Board *b, int y, int x)
{
	int	f = 0;

	if (!b) return (0);
	if (Len1(b, y, x) >= b->len) f += 0x01;
	if (Len2(b, y, x) >= b->len) f += 0x02;
	if (Len3(b, y, x) >= b->len) f += 0x04;
	if (Len4(b, y, x) >= b->len) f += 0x08;
	return (f);
}

// 石の設置
// x：列番号
// v：プレーヤ番号
int BdDrop(Board *b, int x, int v)
{
	int	y;

	if (!b) return (-1);
	for (y = 0; y < b->rows; y++) if (BdGet(b, y, x)) break;
	y--;
	BdSet(b, y, x, v);
	return (y);
}

