#pragma once

#include "Utility.h"

class Cell;

class Peice;

class Player;

class Board;

class Shogi
{
public:
	Shogi();

	void play(int);

	virtual ~Shogi();

	static void transformForCells(Pos&);

	static void transformForSlabs(Pos&);

	static Pos reverse(Pos);

private:

	int r{}, c{};

	Board* B;

	Player* Ps[2];

	int turn;

	void*** images{ nullptr };

	void displayTurn();

	Pos selectSource();

	Pos selectDest();

	bool isValidSource(Pos);

	bool isValidDest(Pos);

	bool insideBox(int, int, int, int, int , int);

	void save();

	bool optionsMenuHandle(Pos);

	void Move(Pos, Pos);

	void updateTurn();

	void displayMove(Pos, Pos);

	bool isMyPeice(Pos);

	void highlight(Pos, int);

	void unhighlight();

	void promotion(Pos, Pos, int);

	void fetchNames();

	bool selfCheck(Pos, Pos, int);

	bool canMove(int);

	void checkCaution(int);

	void saveGame();

	void loadGame();

	void replay();

	bool insideEllipse(Pos, Pos, int, int);

	void promote(Peice*, int);

	void capture(Pos, Pos);

	void initscreenprocessing();

	void endScreenProcessing(std::string);

	void displayCapturedPs(int, int);

	bool isValidCell(Pos);

	bool isValidSlab(Pos);

	void loadImages(Board*);

	void updateTimer();
	void setTimer();

	void showTimer();
};