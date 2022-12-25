#pragma once

#include"Utility.h"

class Board;

class Peice
{
public:
	bool isVertMove(Pos);
	bool isHorzMove(Pos);
	bool isDiagMove(Pos);
	
	virtual bool isLegalMove(Pos) = 0;

	void draw(int, int, bool = false);

	void moveTo(Pos);

	int getColor();

	Pos getPos();

	void setPromoted(bool);

	bool ispromoted();

	void setCaptured(bool);

	bool getCaptured();

	std::string getName();

	void setColor(int);

	void setBoard(Board*);

	Peice(Pos, int, bool, Board*);

	int getx();
	int gety();

	void setImptr(void*);
	void* getImptr();

	void setImptr_(void*);
	void* getImptr_();

	void setImptrP(void*);
	void* getImptrP();

	void setImptrP_(void*);
	void* getImptrP_();

	virtual ~Peice();

protected:
	
	Pos pos;

	Board* B{ nullptr };
	
	bool isCaptured;

	std::string name{};

	int color{};
	
	bool isPromoted{ false };

	void* imptr{ nullptr };
	void* imptr_{ nullptr };

	void* imptrP{ nullptr };
	void* imptrP_{ nullptr };

	bool isLegalKing(Pos);

	bool isLegalGoldenGeneral(Pos);
};

