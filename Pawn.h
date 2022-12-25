#pragma once

#include"Peice.h"


class Pawn : public Peice
{
public:
    Pawn(Pos, int, bool, Board*);
     
    bool isLegalMove(Pos) final override;


    ~Pawn();

private:
    void drawCrown(int,int);
};

