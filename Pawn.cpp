#include "Pawn.h"

#include "Board.h"


using namespace std;


Pawn::Pawn(Pos P, int clr, bool ispromoted, Board*B) : Peice(P, clr, ispromoted, B) 
{
	this->name = "Pawn";
}

bool Pawn::isLegalMove(Pos P)
{
	if (this->isCaptured)
	{
		return false;
	}
	if (this->isPromoted)
		return this->isLegalGoldenGeneral(P);
	if (this->color == WHITE && isVertMove(P) && P.y == pos.y + 1)
		return true;
	if (this->color == BLACK && isVertMove(P) && P.y == pos.y - 1)
		return true;
	return false;
}
//
//void Pawn::drawCrown(int x, int y)
//{
//	int maxx = x + 25, minx = x - 25;
//
//	fillellipse(x, y - 18, 4, 7);
//
//	y -= 3;
//
//	int Ps[14] = {
//		x + 10, y - 4,
//		x + 15, y - 7,
//		x + 19, y - 14,
//		x + 21, y - 8,
//		x + 17, y - 4,
//		x + 10, y - 4
//	};
//
//	fillpoly(6, Ps);
//
//	y += 3;
//
//	int Ps1[14] = {
//		x + 10, y + 2,
//		x + 17, y,
//		maxx, y - 2,
//		maxx - 3, y + 3,
//		x + 18, y + 3,
//		x + 10, y + 2
//	};
//
//	fillpoly(6, Ps1);
//
/////////////////////////////////////////////////////////////////////
//
//
//	y -= 3;
//
//	int Ps2[14] = {
//		x - 10, y - 4,
//		x - 15, y - 7,
//		x - 19, y - 14,
//		x - 21, y - 8,
//		x - 17, y - 4,
//		x - 10, y - 4
//	};
//
//	fillpoly(6, Ps2);
//
//	y += 3;
//
//	int Ps3[14] = {
//		x - 10, y + 2,
//		x - 17, y,
//		minx, y - 2,
//		minx + 3, y + 3,
//		x - 18, y + 3,
//		x - 10, y + 2
//	};
//
//	fillpoly(6, Ps3);
//}
//
//void Pawn::draw(int x, int y, bool)
//{
//	int maxx = x + 15, minx = x - 15;
//
//	if (this->isPromoted)
//		drawCrown(x, y - 14);
//	
//	fillellipse(x, y - 14, 7, 9);
//
//	sector(x, y + 12, 60, 120, 30, 15);
//
//	drawBase(x, y);
//	
//	if (this->color == WHITE) {
//		setfillstyle(SOLID_FILL, WHITE_SHADE);
//		setcolor(WHITE);
//	} else	{
//		setfillstyle(SOLID_FILL, BLACK_SHADE);
//		setcolor(COLOR(200, 165, 130));
//	}
//
//	fillellipse(x - 2, y - 17, 2, 3);
//}

Pawn::~Pawn()	{ }