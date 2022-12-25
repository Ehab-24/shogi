#include "Lance.h"

#include "Board.h"

#include "Shogi.h"


Lance::Lance(Pos P, int clr, bool ispromoted, Board* B) :Peice(P, clr, ispromoted, B)
{
    this->name = "Lance";
}
//
//void Lance::drawMace(int x, int y)
//{
//    y -= 3;
//
//    fillellipse(x, y - 12, 9, 9);
//
//    int spike1R[6] = {
//        x + 8, y - 14,
//        x + 14, y - 12,
//        x + 8, y - 10
//    };
//
//    fillpoly(3, spike1R);
//
//    int spike1L[6] = {
//       x - 8, y - 14,
//       x - 14, y - 12,
//       x - 8, y - 10
//    };
//
//    fillpoly(3, spike1L);
//
//    int spike2R[6] = {
//        x + 6, y - 20,
//        x + 11, y - 21,
//        x + 8, y - 17
//    };
//
//    fillpoly(3, spike2R);
//
//    int spike2L[6] = {
//       x - 6, y - 20,
//       x - 11, y - 21,
//       x - 8, y - 17
//    };
//
//    fillpoly(3, spike2L);
//
//    int spike3R[6] = {
//        x + 5, y - 4,
//        x + 10, y - 3,
//        x + 7, y - 7
//    };
//
//    fillpoly(3, spike3R);
//
//    int spike3L[6] = {
//        x - 5, y - 4,
//        x - 10, y - 3,
//        x - 7, y - 7
//    };
//
//    fillpoly(3, spike3L);
//}
//
//void Lance::draw(int x, int y, bool)
//{
//    int maxx = x + 12, minx = x - 12;
//
//    int Ps[12] = { 
//        x - 5, y,
//        minx, y + 9,
//        x, y + 11 ,
//        maxx, y + 9,
//        x + 5, y ,
//        x, y - 38
//    };
//
//    fillpoly(6, Ps);
//
//    if (this->isPromoted)
//        drawMace(x, y);
//
//    drawBase(x, y);
//}

bool Lance::isLegalMove(Pos P)
{
    if (this->isCaptured)
        return true;
    if (this->isPromoted)
        return this->isLegalGoldenGeneral(P);

    if (this->color == WHITE && Board::isVertClr(this->pos, P, this->B) && isVertMove(P) && P.y > pos.y)
        return true;
    if (this->color == BLACK && Board::isVertClr(this->pos, P, this->B) && isVertMove(P) && P.y < pos.y)
        return true;
    return false;
}


Lance::~Lance()	{ }