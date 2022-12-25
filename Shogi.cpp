#include "Shogi.h"

#include <iostream>

#include <Windows.h>

#include "Utility.h"

#include "Pawn.h"

#include "Cell.h"

#include "Player.h"

#include "Board.h"

#include <math.h>

#include "Slab.h"

#include <exception>


using namespace std;

//
//void getRowColvyLeftClick(int& rpos, int& cpos)
//{
//	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
//	DWORD Events;
//	INPUT_RECORD InputRecord;
//	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
//
//	do {
//		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
//
//		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
//		{
//			cpos = InputRecord.Event.MouseEvent.dwButtonState.X;
//			rpos = InputRecord.Event.MouseEvent.dwButtonState.Y;
//			break;
//		}
//	} while (true);
//}


//				PRIVATE


void Shogi::transformForCells(Pos& P)
{
	P.x = (P.x - X_TRANSLATE) / CELL_X;
	P.y = (P.y - Y_TRANSLATE) / CELL_Y;
}

void Shogi::transformForSlabs(Pos& P)
{
	if (P.x > X_TRANSLATE - 150 && P.x < X_TRANSLATE - 45)
		P.x = -2;
	else if (P.x > X_TRANSLATE + (CELL_X * NO_OF_COLS) + 45 && P.x < X_TRANSLATE + (CELL_X * NO_OF_COLS) + 150)
		P.x = -1;

	P.y = (P.y - 10) / SLAB_Y;
}

Pos Shogi::reverse(Pos P)
{
	P.x = P.x * CELL_X + X_TRANSLATE;
	P.y = P.y * CELL_Y + Y_TRANSLATE;
	return P;
}

bool Shogi::insideEllipse(Pos checkP, Pos center, int radx, int rady)
{
	if ((pow((center.x - checkP.x), 2) / pow(radx, 2))
		+ (pow((center.y - checkP.y), 2) / pow(rady, 2)) < 1)
		return true;
	return false;
}

void Shogi::promotion(Pos src, Pos des, int mainwin)
{
	if (src.x < 0
		|| this->B->cells[src.y][src.x]->getPeice()->getName() == "King"
		|| this->B->cells[src.y][src.x]->getPeice()->getName() == "GoldenGeneral")
		return;

	Peice* sourcePeice = this->B->cells[src.y][src.x]->getPeice();

	if (sourcePeice->ispromoted())
		return;

	if ((sourcePeice->getColor() == BLACK
		&& (src.y <= 2 || des.y <= 2))
		|| (sourcePeice->getColor() == WHITE
			&& (src.y >= 6 || des.y >= 6)))
	{
		promote(sourcePeice, mainwin);
	}
}

void Shogi::fetchNames()
{
	setbkcolor(COLOR(195,193,142));

	setcolor(BLACK);

	settextstyle(5, 0, 0);

	setusercharsize(3, 2, 3, 2);

	char name1[15]{}, name2[15]{};

	for (int i = 0; i < 15; i++)
	{
		while (!kbhit());

		char c = getch();

		if (int(c) == 13)
			break;

		name1[i] = c;

		bgiout << name1[i];
		outstreamxy(15 * i + 350, 340);
	}

	for (int i = 0; c != '\r' && i < 15; i++)
	{
		while (!kbhit());

		char c = getch();

		if (int(c) == 13)
			break;

		name2[i] = c;

		bgiout << name2[i];
		outstreamxy(15 * i + 1020, 347);
	}

	Ps[0]->name = name1;
	Ps[1]->name = name2;

	setcolor(TEXT_COLOR);

	settextstyle(TEXT_FONT, 0, 0);

	setusercharsize(1, 3, 1, 1);

	setbkcolor(BK_COLOR);
}
void Shogi::initscreenprocessing()
{
	setactivepage(0);

	int maxx = getmaxx(), maxy = getmaxy();

	settextjustify(CENTER_TEXT, CENTER_TEXT);

	settextstyle(SIMPLEX_FONT, 0, 4);

	outtextxy(maxx/2 - 25, maxy/2, "Loading...");

	setvisualpage(0);

	loadImages(this->B);

	settextstyle(TEXT_FONT, HORIZ_DIR, 0);

	setusercharsize(1, 3, 1, 1);

	setactivepage(1);

	readimagefile("sample.jpg", 0, 0, maxx, maxy);

	readimagefile("startscreen.jpg", 200, 0, maxx - 200, maxy);

	setvisualpage(1);

	setactivepage(2);

	readimagefile("Names page.jpg", 0, 0, getmaxx(), getmaxy());
	
	while (!ismouseclick(WM_LBUTTONDOWN));

	setvisualpage(2);

	fetchNames();

	setactivepage(3);

	readimagefile("sample.jpg", 0, 0, getmaxx(), getmaxy());

	setbkcolor(BLACK_DARK);
	
	bgiout << this->Ps[0]->getName();
	outstreamxy(X_TRANSLATE - 150 - 60, 25);

	bgiout << this->Ps[1]->getName();
	outstreamxy(X_TRANSLATE + CELL_X * NO_OF_COLS + 150 + 60, 25);

	outtextxy(1420, 300, "SAVE");
	outtextxy(1420, 360, "LOAD");
	outtextxy(1420, 420, "REPLAY");
	

	this->B->drawBoard();

	while (!ismouseclick(WM_LBUTTONDOWN));
	
	setvisualpage(3);
}

void Shogi::capture(Pos src, Pos des)
{
	if (src.x < 0)
	{
		this->B->slabs[src.x + 2][src.y]->getPeice()->setCaptured(false);
	}
	if (this->B->cells[des.y][des.x]->isempty())
		return;

	Peice* srcp = this->B->cells[src.y][src.x]->getPeice();
	Peice* desp = this->B->cells[des.y][des.x]->getPeice();

	desp->setPromoted(false);
	desp->setCaptured(true);

	int clr;
	std::string name = this->B->cells[desp->gety()][desp->getx()]->getPeice()->getName();
	
	void* imptr, * imptr_, *imptrP, *imptrP_;

	if (desp->getColor() == BLACK)


	{
		clr = 0;
		desp->setColor(WHITE);

		if (name == "Pawn")
		{
			imptr = this->images[11][0];
			imptr_ = this->images[11][1];
			imptrP = this->images[11][2];
			imptrP_ = this->images[11][3];
		}
		else if (name == "Lance")
		{
			imptr = this->images[0][0];
			imptr_ = this->images[0][1];
			imptrP = this->images[0][2];
			imptrP_ = this->images[0][3];
		}
		else if (name == "Knight")
		{
			imptr = this->images[1][0];
			imptr_ = this->images[1][1];
			imptrP = this->images[1][2];
			imptrP_ = this->images[1][3];
		}
		else if (name == "SilverGeneral")
		{
			imptr = this->images[2][0];
			imptr_ = this->images[2][1];
			imptrP = this->images[2][2];
			imptrP_ = this->images[2][3];
		}
		else if (name == "GoldenGeneral")
		{
			imptr = this->images[3][0];
			imptr_ = this->images[3][1];
			imptrP = this->images[3][2];
			imptrP_ = this->images[3][3];
		}
		else if (name == "Bishop")
		{
			imptr = this->images[10][0];
			imptr_ = this->images[10][1];
			imptrP = this->images[10][2];
			imptrP_ = this->images[10][3];
		}
		else if (name == "Rook")
		{
			imptr = this->images[9][0];
			imptr_ = this->images[9][1];
			imptrP = this->images[9][2];
			imptrP_ = this->images[9][3];
		}
	}
	else {
		clr = 1;
		desp->setColor(BLACK);

		if (name == "Pawn")
		{
			imptr = this->images[20][0];
			imptr_ = this->images[20][1];
			imptrP = this->images[20][2];
			imptrP_ = this->images[20][3];
		}
		else if (name == "Lance")
		{
			imptr = this->images[31][0];
			imptr_ = this->images[31][1];
			imptrP = this->images[31][2];
			imptrP_ = this->images[31][3];
		}
		else if (name == "Knight")
		{
			imptr = this->images[32][0];
			imptr_ = this->images[32][1];
			imptrP = this->images[32][2];
			imptrP_ = this->images[32][3];
		}
		else if (name == "SilverGeneral")
		{
			imptr = this->images[33][0];
			imptr_ = this->images[33][1];
			imptrP = this->images[33][2];
			imptrP_ = this->images[33][3];
		}
		else if (name == "GoldenGeneral")
		{
			imptr = this->images[34][0];
			imptr_ = this->images[34][1];
			imptrP = this->images[34][2];
			imptrP_ = this->images[34][3];
		}
		else if (name == "Bishop")
		{
			imptr = this->images[29][0];
			imptr_ = this->images[29][1];
			imptrP = this->images[29][2];
			imptrP_ = this->images[29][3];
		}
		else if (name == "Rook")
		{
			imptr = this->images[30][0];
			imptr_ = this->images[30][1];
			imptrP = this->images[30][2];
			imptrP_ = this->images[30][3];
		}
	}

	desp->setImptr(imptr),
		desp->setImptr_(imptr_),
		desp->setImptrP(imptrP),
		desp->setImptrP_(imptrP_);
	
	const int BLACK_I = -2, WHITE_I = 10;

	int P_I;

	if (desp->getName() == "Pawn")
	{
		P_I = PAWN_I;

		this->B->slabs[clr][P_I]->addPeice(desp);

		desp->moveTo({ BLACK_I , PAWN_I});
	}
	else if (desp->getName() == "Lance")
	{
		P_I = LANCE_I;

		this->B->slabs[clr][P_I]->addPeice(desp);

		desp->moveTo({ BLACK_I , LANCE_I });
	}
	else if (desp->getName() == "Knight")
	{
		P_I = KNIGHT_I;

		this->B->slabs[clr][P_I]->addPeice(desp);

		desp->moveTo({ BLACK_I , KNIGHT_I });
	}
	else if (desp->getName() == "SilverGeneral")
	{
		P_I = SILVER_I;

		this->B->slabs[clr][P_I]->addPeice(desp);

		desp->moveTo({ BLACK_I , SILVER_I });
	}
	else if (desp->getName() == "GoldenGeneral")
	{
		P_I = GOLD_I;

		this->B->slabs[clr][P_I]->addPeice(desp);

		desp->moveTo({ BLACK_I , GOLD_I });
	}
	else if (desp->getName() == "Bishop")
	{
		P_I = BISHOP_I;

		this->B->slabs[clr][P_I]->addPeice(desp);

		desp->moveTo({ BLACK_I , BISHOP_I });
	}
	else if (desp->getName() == "Rook")
	{
		P_I = ROOK_I;

		this->B->slabs[clr][P_I]->addPeice(desp);

		desp->moveTo({ BLACK_I , ROOK_I });
	}

	displayCapturedPs(clr, P_I);
}

void Shogi::displayCapturedPs(int clr, int P_I)
{

	setfillstyle(SOLID_FILL, SLAB_COLOR);

	setcolor(SLAB_OUTLINE);

	this->B->slabs[clr][P_I]->draw();
}

bool Shogi::isValidCell(Pos P)
{
	if (P.x < 0 || P.x > 8 || P.y < 0 || P.y > 8)
		return false;
	if (this->B->cells[P.y][P.x]->isempty())
		return false;
	return this->B->cells[P.y][P.x]->getPeice()->getColor() == this->Ps[turn]->getColor();
}

bool Shogi::isValidSlab(Pos P)
{
	if (P.x < -2 || P.x > -1 || P.y < 0 || P.y >= 8)
		return false;
	if (this->B->slabs[P.x + 2][P.y]->isempty())
		return false;
	return this->B->slabs[P.x + 2][P.y]->getColor() == this->Ps[turn]->getColor();
}

bool Shogi::selfCheck(Pos src, Pos des, int color) { return this->B->selfCheck(src, des, color); }

bool Shogi::canMove(int player) { return this->B->canMove(player); }

void Shogi::checkCaution(int player)
{
	Pos kingpos = this->B->findKing(player);

	if (!this->B->inCheck(player))
	{
		if (this->Ps[player/15]->inCheck)
		{
			setfillstyle(SOLID_FILL, CELL_COLOR);

			setcolor(OUTLINE);

			this->B->cells[kingpos.y][kingpos.x]->draw();
		}
		this->Ps[player / 15]->inCheck = false;

		return;
	}
	this->Ps[player / 15]->inCheck = true;

	this->B->drawCaution(CELL_X / 2 + (kingpos.x * CELL_X + X_TRANSLATE), CELL_Y / 2 + (kingpos.y * CELL_Y + Y_TRANSLATE) + 5);
}


bool Shogi::isMyPeice(Pos src)
{
	return this->B->cells[src.y][src.x]->getPeice()->getColor() == this->Ps[turn]->getColor();
}

void Shogi::displayTurn()
{
	setcolor(TEXT_COLOR);

	bgiout << this->Ps[turn]->getName();
	
	if (this->Ps[turn]->getColor() == WHITE)
		outstreamxy(X_TRANSLATE - 210, 25);
	else
		outstreamxy(X_TRANSLATE + CELL_X * NO_OF_COLS + 210, 25);

	setcolor(COLOR(127, 127, 0));

	bgiout << this->Ps[(turn + 1) % 2]->getName();

	if (this->Ps[turn]->getColor() == BLACK)
		outstreamxy(X_TRANSLATE - 210, 25);
	else
		outstreamxy(X_TRANSLATE + CELL_X * NO_OF_COLS + 210, 25);

	setcolor(TEXT_COLOR);
}

Pos Shogi::selectSource()
{
	Pos src;

	while (!ismouseclick(WM_LBUTTONDOWN));

	getmouseclick(WM_LBUTTONDOWN, src.x, src.y);

	if ((src.x > X_TRANSLATE - 150 && src.x < X_TRANSLATE - 45)
		|| (src.x > X_TRANSLATE + (CELL_X * NO_OF_COLS) + 45 && src.x < X_TRANSLATE + (CELL_X * NO_OF_COLS) + 150))
		transformForSlabs(src);
	else if (src.x > X_TRANSLATE && src.x < X_TRANSLATE + (CELL_X * NO_OF_COLS))
		transformForCells(src);

	return src;
}

bool Shogi::insideBox(int x1, int y1, int x2, int y2, int x, int y)
{
	if (x > x1 && x < x2 && y > y1 && y < y2)
		return true;
	return false;
}

bool Shogi::optionsMenuHandle(Pos P)
{
	if (insideBox(1420, 260, 1520, 300, P.x, P.y))
	{
		save();
		return true;
	}
	if (insideBox(1420, 320, 1520, 360, P.x, P.y))
	{
		loadGame();
		return true;
	}
	if (insideBox(1420, 380, 1520, 420, P.x, P.y))
	{
		replay();
		return true;
	}
	return false;
}

Pos Shogi::selectDest()
{
	Pos des;

	/*if(ismouseclick(WM_LBUTTONDOWN))
		outtextxy(1100, 300, "Dest selected");*/

	while (!ismouseclick(WM_LBUTTONDOWN));

	getmouseclick(WM_LBUTTONDOWN, des.x, des.y);

	if ((des.x > X_TRANSLATE - 150 && des.x < X_TRANSLATE - 45)
		|| (des.x > X_TRANSLATE + (CELL_X * NO_OF_COLS) + 45 && des.x < X_TRANSLATE + (CELL_X * NO_OF_COLS) + 150))
		transformForSlabs(des);
	else
		transformForCells(des);

	return des;
}

bool Shogi::isValidSource(Pos P)
{
	return (isValidCell(P) || isValidSlab(P));
}

bool Shogi::isValidDest(Pos P)
{
	if (P.x < 0 || P.x > 8 || P.y < 0 || P.y > 8)
		return false;
	if (this->B->cells[P.y][P.x]->isempty())
		return true;
	return this->B->cells[P.y][P.x]->getPeice()->getColor() != this->Ps[turn]->getColor();
}

void Shogi::updateTurn() { this->turn = (this->turn + 1) % 2; }

void Shogi::Move(Pos src, Pos des)
{
	this->B->move(src, des);
}

void Shogi::displayMove(Pos src, Pos des)
{
	
	if (src.x < 0)
	{
		setfillstyle(SOLID_FILL, SLAB_COLOR);

		setcolor(SLAB_OUTLINE);

		this->B->slabs[src.x + 2][src.y]->draw();

		setfillstyle(SOLID_FILL, CELL_COLOR);

		setcolor(CELL_OUTLINE);
	}
	else
	{
		setfillstyle(SOLID_FILL, CELL_COLOR);

		setcolor(CELL_OUTLINE);

		this->B->cells[src.y][src.x]->draw();
	}
	this->B->cells[des.y][des.x]->draw();
}

void Shogi::highlight(Pos src, int color)	{ this->B->highlight(src, color); }

void Shogi::unhighlight()	{ this->B->unhighlight(); }

void Shogi::promote(Peice* src, int mainwin)
{
	int newwin = initwindow(350, 220, "", 505, 240);

	readimagefile("Promote.jpg", 0, 0, getmaxx(), getmaxy());

	while (!ismouseclick(WM_LBUTTONDOWN));

	int x{}, y{};

	getmouseclick(WM_LBUTTONDOWN, x, y);

	src->setPromoted(true);

	//if()

	closegraph(newwin);

	setcurrentwindow(mainwin);
}

void Shogi::endScreenProcessing(std::string winner)
{
	while (!ismouseclick(WM_LBUTTONDOWN));

	initwindow(1530, 780, "winner winner no dinner");
	
	readimagefile("Win page.jpg", 0, 0, getmaxx(), getmaxy());

	setcolor(YELLOW);
	
	bgiout << winner;

	settextstyle(DEFAULT_FONT, 0, 15);

	outstreamxy(2 * getmaxx() / 3,  getmaxy() / 3);

	bgiout << "Wins!";

	outstreamxy(2 * getmaxx() / 3 + 20, getmaxy() / 3 + 60);

	while (!ismouseclick(WM_LBUTTONDOWN));
}

void Shogi::save()
{
	std::ofstream fout("Saved.txt");

	this->B->saveBoard(fout);

	fout << endl << turn << endl << this->Ps[0]->getName() << " " << this->Ps[1]->getName();

	fout.close();
}

void Shogi::saveGame() 
{
	static int i = 0;

	std::fstream out;
	out.open("Replay.txt", std::ios::app);

	if (i == 0) {
		out << this->Ps[0]->getName() << " " << this->Ps[1]->getName() << endl;
		i = 1;
	}
	this->B->saveBoard(out);

	out << endl << turn << endl;

	out.close();
}

void Shogi::loadGame()
{
	std::ifstream fin("Saved.txt");

	if (!fin.is_open()) {
		//file not found
		return;
	}

	this->B = new Board(fin);

	fin >> this->turn;

	fin.close();
}

void Shogi::loadImages(Board*_B)
{
	const char* imNames[84] = { 
		"LanceW.gif" ,
		"LanceW_.gif" ,
		"LanceWP.gif" ,
		"LanceWP_.gif" ,

		"KnightW.gif", 
		"KnightW_.gif", 
		"KnightWP.gif", 
		"KnightWP_.gif", 

		"SilverW.gif", 
		"SilverW_.gif", 
		"SilverWP.gif", 
		"SilverWP_.gif", 

		"GoldW.gif", 
		"GoldW_.gif", 
		
		"KingW.gif", 
		"KingW_.gif", 
		
		"GoldW.gif" ,
		"GoldW_.gif" ,
		
		"SilverW.gif" , 
		"SilverW_.gif" , 
		"SilverWP.gif" , 
		"SilverWP_.gif" , 

		"KnightW.gif",
		"KnightW_.gif",
		"KnightWP.gif",
		"KnightWP_.gif",

		"LanceW.gif" , 
		"LanceW_.gif" , 
		"LanceWP.gif" , 
		"LanceWP_.gif" , 
		
		"RookW.gif"/*10*/, 
		"RookW_.gif"/*10*/, 
		"RookWP.gif"/*10*/, 
		"RookWP_.gif"/*10*/, 
		
		"BishopW.gif", 
		"BishopW_.gif", 
		"BishopWP.gif", 
		"BishopWP_.gif", 
		
		"PawnW.gif", 
		"PawnW_.gif", 
		"PawnWP.gif", 
		"PawnWP_.gif", 

		"PawnB.gif",
		"PawnB_.gif",
		"PawnBP.gif",
		"PawnBP_.gif",

		"BishopB.gif",
		"BishopB_.gif",
		"BishopBP.gif",
		"BishopBP_.gif",

		"RookB.gif"/*10*/,
		"RookB_.gif"/*10*/,
		"RookBP.gif"/*10*/,
		"RookBP_.gif"/*10*/,

		"LanceB.gif" , 
		"LanceB_.gif" , 
		"LanceBP.gif" , 
		"LanceBP_.gif" , 
		
		"KnightB.gif", 
		"KnightB_.gif", 
		"KnightBP.gif", 
		"KnightBP_.gif", 
		
		"SilverB.gif", 
		"SilverB_.gif", 
		"SilverBP.gif", 
		"SilverBP_.gif", 
		
		"GoldB.gif", 
		"GoldB_.gif", 
		
		"KingB.gif", 
		"KingB_.gif", 
		
		"GoldB.gif" ,
		"GoldB_.gif" ,
		
		"SilverB.gif" , 
		"SilverB_.gif" , 
		"SilverBP.gif" , 
		"SilverBP_.gif" , 
		
		"KnightB.gif" , 
		"KnightB_.gif" , 
		"KnightBP.gif" , 
		"KnightBP_.gif" , 
		
		"LanceB.gif" , 
		"LanceB_.gif" , 
		"LanceBP.gif" , 
		"LanceBP_.gif" 
	};

	this->images = new void** [NO_OF_PEICES];
	
	for (int i = 0; i < NO_OF_PEICES; i++)
		this->images[i] = new void* [4];

	for (int i = 0, im = 0; i < NO_OF_PEICES;)
	{
		int reps = 1;
		if (_B->Ps[i]->getName() == "Pawn")
			reps = 9;

		void*imgptr,
			*imgptr_,
			*imgptrP,
			*imgptrP_;

		int size = imagesize(0, 0, CELL_X - 1, CELL_Y  - 1);

		for (int j = 0; j < reps; j++, i++) {

			if (j == 0)
			{
				readimagefile(imNames[im], 0, 0, CELL_X - 1, CELL_Y  - 1);

				imgptr = malloc(size);

				getimage(0, 0, CELL_X - 1, CELL_Y  - 1, imgptr);
			}
			_B->Ps[i]->setImptr(imgptr);
			this->images[i][0] = imgptr;

			//
			if (j == 0)
			{
				readimagefile(imNames[im + 1], 0, 0, CELL_X - 1, CELL_Y  - 1);

				imgptr_ = malloc(size);

				getimage(0, 0, CELL_X - 1, CELL_Y  - 1, imgptr_);
			}
			_B->Ps[i]->setImptr_(imgptr_);
			this->images[i][1] = imgptr_;

			if (_B->Ps[i]->getName() == "GoldenGeneral" || _B->Ps[i]->getName() == "King")
			{
				im += 2;
				this->B->Ps[i]->setImptr(imgptr);

				this->B->Ps[i]->setImptr_(imgptr_);

				continue;
			}
			if (j == 0)
			{
				readimagefile(imNames[im + 2], 0, 0, CELL_X - 1, CELL_Y  - 1);

				imgptrP = malloc(size);

				getimage(0, 0, CELL_X - 1, CELL_Y  - 1, imgptrP);
			}
			_B->Ps[i]->setImptrP(imgptrP);
			this->images[i][2] = imgptrP;

			//
			if (j == 0)
			{
				readimagefile(imNames[im + 3], 0, 0, CELL_X - 1, CELL_Y  - 1);

				imgptrP_ = malloc(size);

				getimage(0, 0, CELL_X - 1, CELL_Y  - 1, imgptrP_);
			}
			_B->Ps[i]->setImptrP_(imgptrP_);
			this->images[i][3] = imgptrP_;

			this->B->Ps[i]->setImptr(imgptr);
			this->B->Ps[i]->setImptr_(imgptr_);
			this->B->Ps[i]->setImptrP(imgptrP);
			this->B->Ps[i]->setImptrP_(imgptrP_);
		}
		if (i != 0 && !(_B->Ps[i - 1]->getName() == "GoldenGeneral" || _B->Ps[i - 1]->getName() == "King"))
			im += 4;
	}

	readimagefile("Cell.gif", 0, 0, CELL_X - 1, CELL_Y  - 1);

	int size = imagesize(0, 0, CELL_X - 1, CELL_Y  - 1);

	void* im = malloc(size);
	void* im_ = malloc(size);

	getimage(0, 0, CELL_X - 1, CELL_Y  - 1, im);

	readimagefile("Cell_.gif", 0, 0, CELL_X - 1, CELL_Y  - 1);

	getimage(0, 0, CELL_X - 1,CELL_Y - 1,im_);

	for (int ri = 0; ri < NO_OF_ROWS; ri++)
	{
		for (int ci = 0; ci < NO_OF_COLS; ci++)
		{
			_B->cells[ri][ci]->setimptr(im);
			_B->cells[ri][ci]->setimptr_(im_);
		}
	}
}

void Shogi::updateTimer()	{ this->Ps[turn]->updateTimer(); }

void Shogi::setTimer() { this->Ps[turn]->setStartTime(); }

void Shogi::showTimer()	{ this->Ps[turn]->showTimer(); }

void Shogi::replay()
{
	cleardevice();

	std::ifstream fin("Replay.txt");

	readimagefile("sample.jpg", 0, 0, getmaxx(), getmaxy());

	if (!fin.is_open()) {
		//file not found
		return;
	}
	std::string n;
	
	fin >> n;
	this->Ps[0]->setName(n);

	fin >> n;
	this->Ps[1]->setName(n);

	while (!fin.eof()) {

		Board*_B = new Board(fin);
		_B->Ps = new Peice * [NO_OF_PEICES];
		for (int ri = 0; ri < 9; ri++)
			for (int ci = 0; ci < 9; ci++) {
				_B->cells[ri][ci]->setimptr(this->B->cells[ri][ci]->getImptr());
				_B->cells[ri][ci]->setimptr_(this->B->cells[ri][ci]->getImptr_());
			}
		for (int i = 0; i < 40; i++) {
			_B->Ps[i] = new Pawn(this->B->Ps[i]->getPos(), B->Ps[i]->getColor(), B->Ps[i]->ispromoted(), _B);
			_B->Ps[i]->setImptr(this->B->Ps[i]->getImptr());
			_B->Ps[i]->setImptr_(this->B->Ps[i]->getImptr_());
			if (this->Ps[i]->getName() == "King" || this->Ps[i]->getName() == "GoldenGeneral")

			{
				_B->Ps[i]->setImptrP(this->B->Ps[i]->getImptrP());
				_B->Ps[i]->setImptrP_(this->B->Ps[i]->getImptrP_());
			}
		}
		fin >> this->turn;

		setbkcolor(BLACK_DARK);

		bgiout << this->Ps[0]->getName();
		outstreamxy(X_TRANSLATE - 150 - 60, 25);

		bgiout << this->Ps[1]->getName();
		outstreamxy(X_TRANSLATE + CELL_X * NO_OF_COLS + 150 + 60, 25);

		Sleep(200);

		_B->drawBoard();

		this->displayTurn();

		//delete[]_B;
	}
	fin.close();
}

//					PUBLIC


Shogi::Shogi()
{
	setcolor(COLOR(255, 255, 0));

	this->Ps[0] = new Player("", WHITE);
	
	this->Ps[1] = new Player("", BLACK);

	this->B = new Board();

	srand(time(0));
	this->turn = rand() % 2;	
}

void Shogi::play(int mainwin)
{
	int maxx = getmaxx(),

	maxy = getmaxy();

	int midx = maxx / 2, midy = maxy / 2;
	
	initscreenprocessing();


	do
	{
		setcolor(COLOR(255, 255, 0));

		displayTurn();
		
		Pos srcP{ (-3,-3) },
			destP = (-3,-3);

		bool inCheck = false;

		do{
			setTimer();

			bool validOption = false;
			do{
				updateTimer();
				showTimer();

				if (isValidSource(destP))
					srcP = destP;
				else
				{
					srcP = selectSource();

					validOption = optionsMenuHandle(srcP);
				}
			} while(!isValidSource(srcP) && !validOption);

			if (srcP.x < 0)
			{
				int a = 0;
			}

			highlight(srcP, Ps[turn]->getColor());

			this->B->drawNodes();

			updateTimer();
			showTimer();

			destP = selectDest();

			unhighlight();

			this->B->drawNodes();


		} while ((!isValidDest(destP)
			|| (srcP.x >= 0 && !this->B->cells[srcP.y][srcP.x]->getPeice()->isLegalMove(destP))
			|| (srcP.x < 0 && !this->B->cells[destP.y][destP.x]->isempty()))
			|| selfCheck(srcP ,destP, Ps[turn]->getColor()));

		updateTimer();
		showTimer();

		promotion(srcP, destP, mainwin);

		capture(srcP, destP);

		Move(srcP, destP);

		displayMove(srcP, destP);

		checkCaution(Ps[(turn + 1) % 2]->getColor());
		checkCaution(Ps[turn]->getColor());

		this->B->drawNodes();
		
		saveGame();

		updateTurn();

	} while (canMove(Ps[turn]->getColor()));

	updateTurn();

	endScreenProcessing(Ps[turn]->name);
}

Shogi::~Shogi(){}