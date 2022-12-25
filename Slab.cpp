#include "Slab.h"

#include "Peice.h"

#include "Pawn.h"

Slab::Slab(int x, int y, int clr) :x(x), y(y), color(clr) {}

Peice* Slab::removePeice()
{
	Peice* R = this->peices[peices.size() - 1];

	this->peices.pop_back();

	return R;
}

void Slab::addPeice(Peice* P)
{
	if (this->peices.size() == 1 && this->peices[0] == nullptr)
		this->peices[0] = P;
	this->peices.push_back(P);
}

void Slab::draw()
{
	int Ps[12] = {
		x + SLAB_X / 2, y,
		x + SLAB_X - 15, y + 10,
		x + SLAB_X, y + SLAB_Y,
		x , y + SLAB_Y,
		x + 15, y + 10,
		x + SLAB_X / 2, y
	};
	int Ps1[12] = {
		x + SLAB_X / 2, y + 1,
		x + SLAB_X - 16, y + 11,
		x + SLAB_X - 1, y + SLAB_Y - 1,
		x + 1, y + SLAB_Y - 1,
		x + 16, y + 11,
		x + SLAB_X / 2, y + 1
	};
	int Ps2[12] = {
		x + SLAB_X / 2, y + 2,
		x + SLAB_X - 17, y + 12,
		x + SLAB_X - 2, y + SLAB_Y - 2,
		x + 2, y + SLAB_Y - 2,
		x + 17, y + 12,
		x + SLAB_X / 2, y + 2
	};
	int Ps3[12] = {
		x + SLAB_X / 2, y + 3,
		x + SLAB_X - 18, y + 13,
		x + SLAB_X - 3, y + SLAB_Y - 3,
		x + 3, y + SLAB_Y - 3,
		x + 18, y + 13,
		x + SLAB_X / 2, y + 3
	};
	int Ps4[12] = {
		x + SLAB_X / 2, y + 4,
		x + SLAB_X - 19, y + 14,
		x + SLAB_X - 4, y + SLAB_Y - 4,
		x + 4, y + SLAB_Y - 4,
		x + 19, y + 14,
		x + SLAB_X / 2, y + 4
	};

	drawpoly(6, Ps);
	
	drawpoly(6, Ps1);
	
	drawpoly(6, Ps2);

	drawpoly(6, Ps3);

	fillpoly(6, Ps4);

	int size = this->peices.size();
	
	setcolor(TEXT_COLOR);

	std::string s = "1";

	s[0] = size - 1 + '0';

	char* out = new char[2];

	strcpy(out, s.c_str());

	outtextxy(x + SLAB_X + 10, y + SLAB_Y, out);

	delete[]out;

///////////////////////////////////////////////////////////////////////////////////////////////////
	
	if (size == 1)
		return;

	if (this->peices[1]->getColor() == WHITE)
		setfillstyle(SOLID_FILL, COLOR_OF_WHITE);
	else
		setfillstyle(SOLID_FILL, COLOR_OF_BLACK);

	setcolor(OUTLINE);

	this->peices[1]->draw(SLAB_X / 2 + x, SLAB_Y / 2 + y + 5);
}

bool Slab::isempty()
{
	if (this->peices.size() == 1)
		return true;
	return false;
}

Peice* Slab::getPeice()
{
	return this->peices[this->peices.size() - 1];
}

int Slab::getColor()
{
	return this->peices[0]->getColor();
}

int Slab::getSize()
{
	return this->peices.size();
}

int Slab::getX() { return this->x; }
int Slab::getY() { return this->y; }

void Slab::setX(int _x) { this->x = _x; }
void Slab::setY(int _y) { this->y = _y; }

void Slab::setColor(int c) {
	this->color = c;
}

Slab::~Slab() {}