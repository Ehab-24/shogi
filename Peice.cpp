#include "Peice.h"

#include <math.h>


class Board;


Peice::Peice(Pos p, int clr, bool ispromoted, Board *B) :pos(p), color(clr), isPromoted(ispromoted), B(B), isCaptured(false) {}

Peice::~Peice() {}

void Peice::moveTo(Pos P)	{ this->pos = P; }

void Peice::draw(int x, int y, bool killFlag)
{
    if (!this->isPromoted)
    {
        if (killFlag) {
            putimage(x - CELL_X / 2, y - CELL_Y / 2, this->imptr_, COPY_PUT);
        }
        else {
            putimage(x - CELL_X/2, y - CELL_Y/2, this->imptr, COPY_PUT);
        }
    }
    else {
        if (killFlag) {
            putimage(x - CELL_X / 2, y - CELL_Y / 2, this->imptrP_, COPY_PUT);
        }
        else {
            putimage(x - CELL_X / 2, y - CELL_Y / 2, this->imptrP, COPY_PUT);
        }
    }
}

Pos Peice::getPos() { return this->pos; }

void Peice::setBoard(Board* B) { this->B = B; }

int Peice::getColor() { return this->color; }

void Peice::setColor(int clr) { this->color = clr; }

std::string Peice::getName() { return this->name; }

void Peice::setPromoted(bool b) { this->isPromoted = b; }

bool Peice::ispromoted() { return this->isPromoted; }

void Peice::setCaptured(bool b) { this->isCaptured = b; }

bool Peice::isLegalKing(Pos P)
{
    int dy = abs(pos.y - P.y),
        dx = abs(pos.x - P.x);

    if ((dy == 1 || dy == 0) && (dx == 0 || dx == 1))
        return true;
    return false;
}

bool Peice::isLegalGoldenGeneral(Pos P)
{
    int dy = abs(P.y - pos.y),
        dx = abs(P.x - pos.x);

    if (!isLegalKing(P))
        return false;
    if (this->color == WHITE && dx == 1 && P.y == pos.y - 1)
        return false;
    if (this->color == BLACK && dx == 1 && P.y == pos.y + 1)
        return false;
    return true;
}

bool Peice::getCaptured() { return this->isCaptured; }

int Peice::getx() { return this->pos.x; }
int Peice::gety() { return this->pos.y; }

void Peice::setImptr(void* im) { this->imptr = im; }
void* Peice::getImptr() { return this->imptr ; }

void Peice::setImptr_(void* im_) { this->imptr_ = im_; }
void* Peice::getImptr_() { return this->imptr ; }

void Peice::setImptrP(void* im) { this->imptrP = im; }
void* Peice::getImptrP() { return this->imptrP; }

void Peice::setImptrP_(void* im_) { this->imptrP_ = im_; }
void* Peice::getImptrP_() { return this->imptrP_; }


//						STATIC

bool Peice::isHorzMove(Pos P)	{ return P.y == pos.y; }

bool Peice::isVertMove(Pos P)	{ return P.x == this->pos.x; }

bool Peice::isDiagMove(Pos P) { return abs(P.x - this->pos.x) == abs(P.y - this->pos.y); }