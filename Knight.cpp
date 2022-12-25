#include "Knight.h"


class Board;


Knight::Knight(Pos P, int clr, bool ispromoted, Board* B) :Peice(P, clr, ispromoted, B)
{
	this->name = "Knight";
}
//
//void Knight::draw(int x, int y, bool)
//{
//	fillellipse(x, y, 20, 12);
//}

bool Knight::isLegalMove(Pos P)
{
	if (this->isCaptured)
		return true;
	if (this->isPromoted)
		return this->isLegalGoldenGeneral(P);

	int dx = abs(P.x - pos.x);

	if (this->color == WHITE && P.y == pos.y + 2 && dx == 1)
		return true;
	else if (this->color == BLACK && P.y == pos.y - 2 && dx == 1)
		return true;
	return false;
}

Knight::~Knight() { }