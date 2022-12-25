#pragma once

#include "Utility.h"

#include <vector>

#include <fstream>


class Peice;
class Cell;
class Slab;
class Player;


class Board
{
private:

	Board(const Board&);

	void createAllPeices();

	void createCells();

	void createAllSlabs();

	void copySlabs(const Board&);

	void copyCells(const Board&);

	void drawFrame();

	void drawCells();

	void drawSlabs();
	
	void colsWithoutPawns(bool*, int);

	Pos findKing(int);

	void drawCaution(int, int);


	Peice** Ps{ nullptr };

	//std::vector<std::vector<std::vector<Peice*>>>capPs;

	Slab*** slabs;

	//void* imptrs[84];

public:

	friend class Shogi;

	Cell*** cells{ nullptr };

	Board();

	Board(std::ifstream&);
	
	void move(Pos, Pos);

	void drawNodes();

	void drawBoard();

	void highlight(Pos, int);

	void unhighlight();

	bool inCheck(int);

	bool selfCheck(Pos, Pos, int);

	bool canMove(int);

	void saveBoard(std::ofstream&);
	void saveBoard(std::fstream&);

	~Board();

	static bool isVertClr(Pos, Pos, Board*);
	static bool isHorzClr(Pos, Pos, Board*);
	static bool isDiagClr(Pos, Pos, Board*);
};

