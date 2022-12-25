#include "GoldenGeneral.h"


class Board;


GoldenGeneral::GoldenGeneral(Pos P, int clr, bool ispromoted, Board* B) :Peice(P, clr, ispromoted, B) { this->name = "GoldenGeneral"; }

//
//void GoldenGeneral::draw(int x, int y, bool)
//{
//    int maxx = x + 20, minx = x - 20;
//
//    y += 5;
//
//    int Ps[28] = { 
//        x,y - 30,
//        x - 4,y - 10,
//        x - 8, y - 10,
//        minx, y - 20,
//        x - 7, y - 1,
//        minx, y,
//        x - 6, y + 5,
//
//        x + 6, y + 5,
//        maxx, y,
//        x + 7, y - 1,
//        maxx, y - 20,
//        x + 8, y - 10,
//        x + 4, y - 10,
//        x,y - 30 
//    };
//
//    fillpoly(14, Ps);
//
//    drawBase(x, y - 5);
//}

bool GoldenGeneral::isLegalMove(Pos P)  
{
    if (this->isCaptured)
        return true; 
    return this->isLegalGoldenGeneral(P); 
}


GoldenGeneral::~GoldenGeneral() { }