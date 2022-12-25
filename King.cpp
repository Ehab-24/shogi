#include "King.h"


class Board;


void King::drawBase(int x, int y)
{
    int maxx = x + 25, minx = x - 25;

    bar3d(minx, y + 24, maxx, y + 28, 0, false);

    arc(x, y + 57, 52, 128, 42);

    floodfill(x, y + 19, OUTLINE);
}


//              PUBLIC

King::King(Pos P, int clr, bool ispromoted, Board* B) :Peice(P, clr, ispromoted, B) 
{
    this->name = "King";
}

//
//void King::draw(int x, int y, bool incheck)
//{
//     int maxx = x + 25, minx = x - 25;
// 
//     sector(x, y, 60, 120, 30, 20);
// 
//     bar3d(x - 7, y, x + 7, y + 12, 0, false);
// 
//     int Ps[18] = {
//         x, y,
//         x + 7, y - 13,
//         x + 15, y - 20,
//         maxx - 5, y - 20,
//         maxx, y - 13,
//         maxx , y,
//         maxx - 3, y + 3,
//         maxx - 6, y + 6,
//         x + 8, y + 8
//     };
// 
//     fillpoly(9, Ps);
// 
//     int Ps1[18] = {
//         x, y,
//         x - 7, y - 13,
//         x - 15, y - 20,
//         minx + 5, y - 20,
//         minx, y - 13,
//         minx , y,
//         minx + 3, y + 3,
//         minx + 6, y + 6,
//         x - 8, y + 8
//     };
// 
//     fillpoly(9, Ps1);
// 
//     int Ps2[6] = {
//         x - 6, y - 22,
//         x, y - 30,
//         x + 6, y - 22
//     };
// 
//     fillpoly(3, Ps2);
// 
//     drawBase(x, y);
//}

bool King::isLegalMove(Pos P)
{
    return this->isLegalKing(P);
}


King::~King() { }