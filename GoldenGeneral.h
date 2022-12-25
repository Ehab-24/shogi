#pragma once

#include "Peice.h"

class GoldenGeneral : public Peice
{
public:

	GoldenGeneral(Pos, int, bool, Board*);
	 
	bool isLegalMove(Pos)final override;

	~GoldenGeneral();
};

