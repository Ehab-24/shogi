#include "Cell.h"
#include "Utility.h"
#include "Peice.h"


Cell::Cell(Peice*pptr, int _x, int _y) : pptr(pptr), x(_x), y(_y), l(CELL_X), h(CELL_Y), color(COLOR(220, 190, 130)) {}

void Cell::draw(bool killFlag)
{
	if (this->pptr != nullptr)
	{
		this->pptr->draw(l / 2 + x, h / 2 + y + 5, killFlag);
	}
	else
	{
		putimage(x, y, this->imptr, COPY_PUT);
	}
}

void* Cell::getImptr() { return this->imptr; }
void* Cell::getImptr_() { return this->imptr; }
void* Cell::getImptrP() { return this->imptr; }
void* Cell::getImptrP_() { return this->imptr; }

bool Cell::isempty() { return this->pptr == nullptr; }

Peice* Cell::getPeice() { return this->pptr; }

bool Cell::getHighlighted() { return this->highlighted; }

void Cell::setPeice(Peice* const P)	{ this->pptr = P; }

void Cell::highlight()
{
	putimage(x, y, this->imptr_, COPY_PUT);
	this->highlighted = true;
}

void Cell::unhighlight()
{
	putimage(x, y, this->imptr, COPY_PUT);
	this->highlighted = false;
}

void Cell::setHighlighted(bool b) { this->highlighted = b; }

int Cell::getx() { return this->x; }

int Cell::gety() { return this->y; }

void Cell::setimptr(void* im) { this->imptr = im; }
void Cell::setimptr_(void* im_) { this->imptr_ = im_; }

Cell::~Cell() { if(this->pptr != nullptr) this->pptr->~Peice(); }