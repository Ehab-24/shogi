#pragma once

#include "Utility.h"
#include "Peice.h"

class Lance:public Peice
{
public:
	Lance(Pos, int, bool, Board*);
	 
	bool isLegalMove(Pos) final override;

	~Lance();

private:
	void drawMace(int, int);
};

