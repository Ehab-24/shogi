#include "Rook.h"

#include "Board.h"

#include "Shogi.h"


class Board;


Rook::Rook(Pos P, int clr, bool ispromoted, Board* B) 
	:Peice(P, clr, ispromoted, B)	{ this->name = "Rook"; }
//
//void Rook::towerRoof(int minx, int maxx, int y)
//{
//	int ps[18] = {
//		minx, y + 15,
//		minx + 3, y + 14,
//		minx + 10, y + 8,
//		maxx - 10, y + 8,
//		maxx - 3, y + 14,
//		maxx, y + 15,
//		maxx - 7, y + 19,
//		minx + 7, y + 19,
//		minx, y + 15
//	};
//
//	fillpoly(9, ps);
//}
//void Rook::drawTower(int x, int y)
//{
//	int maxx = x + 25, minx = x - 25;
//
//	y += 10;
//
//	int ps[8] = {
//		x - 5, y - 25,
//		x, y - 32,
//		x + 5, y - 25,
//		x - 5, y - 25
//	};
//
//	fillpoly(4, ps);
//
//	towerRoof(minx, maxx, y - 10);
//
//	towerRoof(minx + 5, maxx - 5, y - 20);
//
//	towerRoof(minx + 10, maxx - 10, y - 30);
//
//	bar3d(minx + 8, y + 13, maxx - 8, y + 18, 0, false);
//}
//
//void Rook::drawDragonKing(int x, int y)
//{
//
//	int _clr,
//		clrs,
//		clrd;
//
//	if (this->color == WHITE)
//	{
//		_clr = COLOR_OF_WHITE, clrs = WHITE_SHADE, clrd = WHITE_DARK;
//	}
//	else
//	{
//		_clr = COLOR_OF_BLACK, clrs = BLACK_SHADE, clrd = BLACK_DARK;
//	}
//	setfillstyle(SOLID_FILL, clrs);
//
//	ellipse(x + 15, y, -40, 70, 20, 30);
//
//	ellipse(x, y - 40, -75, -15, 20, 21);
//
//	ellipse(x + 3, y + 12, 10, 70, 15, 21);
//
//	ellipse(x + 18, y + 28, 20, 90, 12, 19);
//
//	line(x + 6, y - 16, x + 7, y - 12);
////
//	ellipse(x - 15, y, 110, 225, 20, 30);
//
//	ellipse(x, y - 40, 195, 255, 20, 21);
//
//	ellipse(x - 3, y + 12, 110, 170, 15, 21);
//
//	ellipse(x - 18, y + 28, 90, 160, 12, 19);
//
//	line(x - 6, y - 16, x - 7, y - 12);
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	setfillstyle(SOLID_FILL, _clr);
//
//	int maxx = x + 40, minx = x - 40;
//
//	int belly[16] = {
//		x + 15, y + 20,
//		x - 15, y + 20,
//		x - 8, y + 15,
//		x - 3, y + 6,
//		x, y - 15,
//		x + 3, y + 6,
//		x + 8, y + 15,
//		x + 15, y + 20,
//	};
//
//	fillpoly(8, belly);
//
//	int head[12] = {
//		x + 4, y - 19,
//		x - 4, y - 19,
//		x - 7, y - 25,
//		x, y - 35,
//		x + 7, y - 25,
//		x + 4, y - 19
//	};
//
//	fillpoly(6, head);
//
//	ellipse(x + 15, y, -40, 85, 24, 36);
//
//	ellipse(x, y - 40, -75, -15, 24, 26);
//
//	ellipse(x + 3, y + 12, 16, 80, 18, 25);
//
//	ellipse(x + 19, y + 30, 20, 90, 15, 25);
//
//	line(x + 5, y - 20, x + 8, y - 8);
////
//	ellipse(x - 15, y, 95, 220, 24, 36);
//
//	ellipse(x, y - 40, 195, 255, 24, 26);
//
//	ellipse(x - 3, y + 12, 100, 164, 18, 25);
//
//	ellipse(x - 19, y + 30, 90, 160, 15, 25);
//
//	line(x - 5, y - 20, x - 8, y - 8);
//
//	floodfill(x, y - 20, OUTLINE);
//
//	floodfill(x + 20, y, OUTLINE);
//
//	floodfill(x - 20, y, OUTLINE);
//
//	drawBase(x, y, false);
//
//	setfillstyle(SOLID_FILL, clrd);
//
//	floodfill(x + 36, y, OUTLINE);
//
//	floodfill(x - 36, y, OUTLINE);
//	
//	setfillstyle(SOLID_FILL, clrs);
//
//	floodfill(x + 18, y - 30, OUTLINE);
//
//	floodfill(x + 23, y + 10, OUTLINE);
//
//	floodfill(x - 18, y - 30, OUTLINE);
//
//	floodfill(x - 23, y + 10, OUTLINE);
//
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//	/*
//	setfillstyle(SOLID_FILL, clr);
//	setcolor(clr);
//
//	x -= 3;
//	
//	line(x - 23, y - 23, x - 25, y - 27);
//
//	ellipse(x - 8, y + 6, 128, 180, 24, 38);
//	ellipse(x - 9, y + 5, 133, 185, 24, 41);
//
//	floodfill(x - 25, y - 23, clr);
//
//	ellipse(x - 8, y + 6, 128, 180, 24, 38);
//	ellipse(x - 9, y + 5, 133, 185, 24, 41);
//
//	floodfill(x - 25, y - 23, clr);*/
//
//}
//
//void Rook::draw(int x, int y, bool)
//{
//	if (this->isPromoted)
//	{
//		drawDragonKing(x, y);
//	}
//	else
//	{
//		drawTower(x, y);
//	}
//}

bool Rook::isLegalMove(Pos P)
{
	if (this->isCaptured)
		return true;
	if (this->isPromoted && isLegalKing(P))
		return true;
	if (isHorzMove(P) && Board::isHorzClr(this->pos, P, this->B))
		return true;
	if (isVertMove(P) && Board::isVertClr(this->pos, P, this->B))
		return true;
	return false;
}


Rook::~Rook() { }