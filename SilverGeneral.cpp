#include "SilverGeneral.h"


class Board;


SilverGeneral::SilverGeneral(Pos P, int clr, bool ispromoted, Board* B) :Peice(P, clr, ispromoted, B) { this->name = "SilverGeneral"; }
//
//void SilverGeneral::draw(int x, int y, bool)
//{
//	int maxx = x + 20, minx = x - 20;
//
//	y += 3;
//
//	int Ps[28] = {
//		x,y - 30,
//		x - 4,y - 10,
//		x - 8, y - 10,
//		minx, y - 20,
//		x - 7, y - 1,
//		minx + 4, y + 12,
//		x - 6, y + 5,
//
//		x + 6, y + 5,
//		maxx - 4, y + 12,
//		x + 7, y - 1,
//		maxx, y - 20,
//		x + 8, y - 10,
//		x + 4, y - 10,
//		x,y - 30 
//	};
//
//	fillpoly(14, Ps);
//
//	if (this->isPromoted) {
//
//		int clrs, clr;
//
//		if (this->color == WHITE)
//			clr = COLOR_OF_WHITE, clrs = WHITE_SHADE;
//		else
//			clr = COLOR_OF_BLACK, clrs = BLACK_SHADE;
//
//		setfillstyle(SOLID_FILL, clrs);
//
//		fillellipse(x, y - 30, 5, 5);
//
//		fillellipse(minx, y - 20, 5, 5);
//
//		fillellipse(maxx, y - 20, 5, 5);
//
//		setfillstyle(SOLID_FILL, clr);
//	}
//	drawBase(x, y - 3);
//}

bool SilverGeneral::isLegalMove(Pos P)
{
	if (this->isCaptured)
		return true;

	int dy = abs(P.y - pos.y),
		dx = abs(P.x - pos.x);

	if (this->isPromoted)
		return this->isLegalGoldenGeneral(P);

	if (!isLegalKing(P))
		return false;
	if (dx == 1 && dy == 0)
		return false;
	if (this->color == WHITE && dx == 0 && P.y == pos.y - 1)
		return false;
	if (this->color == BLACK && dx == 0 && P.y == pos.y + 1)
		return false;
	return true;
}


SilverGeneral::~SilverGeneral() {  }