#pragma once
#include "Peice.h"

class Knight : public Peice
{
public:
	Knight(Pos, int, bool, Board*);
	 
	bool isLegalMove(Pos) final override;

	~Knight();
};

