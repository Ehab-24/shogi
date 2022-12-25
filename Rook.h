#pragma once
#include "Peice.h"
class Rook : public Peice
{
private:

	void towerRoof(int,int,int);

	void drawTower(int, int);

	void drawDragonKing(int, int);

public:

	Rook(Pos, int, bool, Board*);
	 
	bool isLegalMove(Pos)final override;

	~Rook();
};

