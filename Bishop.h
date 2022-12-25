#pragma once

#include "Peice.h"

class Bishop : public Peice
{
public:

	Bishop(Pos, int, bool, Board*);

	bool isLegalMove(Pos)final override;

	~Bishop();
};

