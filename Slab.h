#pragma once

#include "Utility.h"

class Peice;

class Slab
{
	std::vector<Peice*>peices{ nullptr };

	int color;

	int x{}, y{};

public:

	Slab(int,int,int);

	void draw();

	Peice* removePeice();

	Peice* getPeice();

	bool isempty();

	int getColor();

	void setColor(int);

	int getSize();

	void setX(int);
	void setY(int);

	int getX();
	int getY();

	void addPeice(Peice*);

	~Slab();
};

