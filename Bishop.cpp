#include "Bishop.h"

#include "Board.h"

#include "Shogi.h"


Bishop::Bishop(Pos P, int clr, bool ispromoted, Board* B) : Peice(P, clr, ispromoted, B) 
{
	this->name = "Bishop";
}

//void Bishop::draw(int x, int y, bool killFlag)
//{
    
    //int maxx = x + 12, minx = x - 12;

    //if (this->isPromoted)
    //{
    //    int ps[10] = {
    //   x - 7, y - 22,
    //   x + 7, y - 22,
    //   maxx - 6, y - 30,
    //   x , y - 34,
    //   minx + 6, y - 30
    //    };

    //    fillpoly(5, ps);


    //    //fillellipse(x, y - 18, 4, 7);

    //    y -= 3;

    //    x += 5;

    //    int Ps[14] = {
    //        x + 10, y - 8,
    //        x + 15, y - 18,
    //        x + 14, y - 38,
    //        x + 21, y - 19,
    //        x + 17, y - 8,
    //        x + 10, y - 8
    //    };

    //    fillpoly(6, Ps);

    //    y += 8;

    //    int Ps1[12] = {
    //        x + 6, y,
    //        x + 20, y - 11,
    //        maxx + 23, y - 25,
    //        maxx + 21, y - 12,
    //        x + 19, y - 2,
    //        x + 15, y - 3
    //    };

    //    fillpoly(5, Ps1);


    //    ///////////////////////////////////////////////////////////////////


    //    y -= 8;

    //    x -= 10;

    //    int Ps2[14] = {
    //        x - 10, y - 8,
    //        x - 15, y - 18,
    //        x - 14, y - 38,
    //        x - 21, y - 19,
    //        x - 17, y - 8,
    //        x - 10, y - 8
    //    };

    //    fillpoly(6, Ps2);

    //    y += 8;

    //    int Ps3[14] = {
    //        x - 6, y,
    //        x - 20, y - 11,
    //        minx - 23, y - 25,
    //        minx - 21, y - 12,
    //        x - 19, y - 2,
    //        x - 15, y - 3
    //    };

    //    fillpoly(6, Ps3);

    //    x += 5;
    //}
    //else
    //{
    //    int Ps1[8] = {
    //   x - 7, y - 22,
    //   x + 7, y - 22,
    //   maxx, y - 32,
    //   minx, y - 32
    //    };

    //    fillpoly(4, Ps1);
    //}



    //y -= 5;

    //bar3d(minx + 2, y - 19, maxx - 2, y - 15, 0, false);

    //int Ps[14] = {
    //    x - 4, y - 12,
    //    x - 8, y + 2,
    //    minx, y + 10,
    //    maxx, y + 10,
    //    x + 8, y + 2,
    //    x + 4, y - 12,
    //    x - 4, y - 12
    //};

    //int clr, clrs, clrd;

    //if (this->color == WHITE)
    //    clr = COLOR_OF_WHITE, clrs = WHITE_SHADE, clrd = WHITE_DARK;
    //else
    //    clr = COLOR_OF_BLACK, clrs = BLACK_SHADE, clrd = BLACK_DARK;

    //setcolor(clr);

    //drawpoly(7, Ps);

    //line(x - 2, y - 12, x - 7, y + 10);
    //line(x + 2, y - 12, x + 5, y + 10);

    //setfillstyle(SOLID_FILL, clrs);

    //floodfill(x - 6, y, clr);

    //setfillstyle(SOLID_FILL, clrd);

    //floodfill(x + 6, y, clr);

    //setfillstyle(SOLID_FILL, clr);

    //floodfill(x, y, clr);

    //setcolor(OUTLINE);

    //setfillstyle(SOLID_FILL, clr);

    //drawpoly(7, Ps);

    //drawBase(x, y, WHITE);
//}

bool Bishop::isLegalMove(Pos P)	
{
	if (this->isCaptured)
		return true;
	if (this->isPromoted && isLegalKing(P))
		return true;
	return (isDiagMove(P) && Board::isDiagClr(this->pos, P, this->B));
}

Bishop::~Bishop() { }