#pragma once

#include "Peice.h"

class SilverGeneral :
    public Peice
{
public:

	SilverGeneral(Pos, int, bool, Board*);
	 
	bool isLegalMove(Pos)final override;

	~SilverGeneral();
};

