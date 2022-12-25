#pragma once
#include "Peice.h"
class King : public Peice
{
private:
	
	void drawBase(int,int);

public:

	King(Pos, int, bool, Board*);
	 

	bool isLegalMove(Pos)final override;

	~King();
};

