#include "Board.h"

#include "Cell.h"

#include "Utility.h"

#include "Pawn.h"

#include "Lance.h"

#include "Knight.h"

#include "Bishop.h"

#include "Rook.h"

#include "SilverGeneral.h"

#include "GoldenGeneral.h"

#include "King.h"

#include "Slab.h"

#include "Player.h"


//				UTILITY

void Board::copyCells(const Board& B)
{
	this->cells = new Cell * *[NO_OF_ROWS];

	for (int ri = 0; ri < NO_OF_ROWS; ri++)
	{
		this->cells[ri] = new Cell * [NO_OF_COLS] {};
		for (int ci = 0; ci < NO_OF_ROWS; ci++)
		{
			int clr;

			if (!B.cells[ri][ci]->isempty())
				clr = B.cells[ri][ci]->getPeice()->getColor();

			if (B.cells[ri][ci]->isempty())
			{
				this->cells[ri][ci] = new Cell(nullptr, ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			}
			else if (B.cells[ri][ci]->getPeice()->getName() == "Pawn")
			{
				this->cells[ri][ci] = new Cell(new Pawn({ ci,ri }, clr, B.cells[ri][ci]->getPeice()->ispromoted(), this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			}
			else if (B.cells[ri][ci]->getPeice()->getName() == "Lance")
			{
				this->cells[ri][ci] = new Cell(new Lance({ ci,ri }, clr, B.cells[ri][ci]->getPeice()->ispromoted(), this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			}
			else if (B.cells[ri][ci]->getPeice()->getName() == "Knight")
			{
				this->cells[ri][ci] = new Cell(new Knight({ ci,ri }, clr, B.cells[ri][ci]->getPeice()->ispromoted(), this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			}
			else if (B.cells[ri][ci]->getPeice()->getName() == "SilverGeneral")
			{
				this->cells[ri][ci] = new Cell(new SilverGeneral({ ci,ri }, clr, B.cells[ri][ci]->getPeice()->ispromoted(), this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			}
			else if (B.cells[ri][ci]->getPeice()->getName() == "GoldenGeneral")
			{
				this->cells[ri][ci] = new Cell(new GoldenGeneral({ ci,ri }, clr, B.cells[ri][ci]->getPeice()->ispromoted(), this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			}
			else if (B.cells[ri][ci]->getPeice()->getName() == "Bishop")
			{
				this->cells[ri][ci] = new Cell(new Bishop({ ci,ri }, clr, B.cells[ri][ci]->getPeice()->ispromoted(), this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			}
			else if (B.cells[ri][ci]->getPeice()->getName() == "Rook")
			{
				this->cells[ri][ci] = new Cell(new Rook({ ci,ri }, clr, B.cells[ri][ci]->getPeice()->ispromoted(), this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			}
			else if (B.cells[ri][ci]->getPeice()->getName() == "King")
			{
				this->cells[ri][ci] = new Cell(new King({ ci,ri }, clr, B.cells[ri][ci]->getPeice()->ispromoted(), this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			}
		}
	}
}

void Board::copySlabs(const Board& B)
{
	this->slabs = new Slab * *[NO_OF_PLAYERS];

	for (int pi = 0; pi < NO_OF_PLAYERS; pi++)
	{
		this->slabs[pi] = new Slab * [NO_OF_SLABS];

		for (int si = 0; si < NO_OF_SLABS; si++)
		{
			if (B.slabs[pi][si]->getSize() <= 1)
				continue;

			int color = B.slabs[pi][si]->getColor();

			int x = B.slabs[pi][si]->getX(), y = B.slabs[pi][si]->getY();

			Slab* s = this->slabs[pi][si] = new Slab(x, y, color);
			
			if (si == 0)
			{
				this->slabs[pi][si]->addPeice(new Pawn(B.slabs[pi][si]->getPeice()->getPos(), color, false, this));
			}
			else if (si == 1)
			{
				this->slabs[pi][si]->addPeice(new Lance(B.slabs[pi][si]->getPeice()->getPos(), color, false, this));
			}
			else if (si == 2)
			{
				this->slabs[pi][si]->addPeice(new Knight(B.slabs[pi][si]->getPeice()->getPos(), color, false, this));
			}
			else if (si == 3)
			{
				this->slabs[pi][si]->addPeice(new SilverGeneral(B.slabs[pi][si]->getPeice()->getPos(), color, false, this));
			}
			else if (si == 4)
			{
				this->slabs[pi][si]->addPeice(new GoldenGeneral(B.slabs[pi][si]->getPeice()->getPos(), color, false, this));
			}
			else if (si == 5)
			{
				this->slabs[pi][si]->addPeice(new Bishop(B.slabs[pi][si]->getPeice()->getPos(), color, false, this));
			}
			else if (si == 6)
			{
				this->slabs[pi][si]->addPeice(new Rook(B.slabs[pi][si]->getPeice()->getPos(), color, false, this));
			}
		}
	}
}

Board::Board(const Board& B)
{
	this->copyCells(B);

	this->copySlabs(B);
}

Pos Board::findKing(int color)
{
	for(int ri = 0; ri < NO_OF_ROWS; ri++)
		for (int ci = 0; ci < NO_OF_COLS; ci++)
		{
			if (!this->cells[ri][ci]->isempty()
				&& this->cells[ri][ci]->getPeice()->getName() == "King" && this->cells[ri][ci]->getPeice()->getColor() == color)
				return { ci,ri };
		}
	return { -1,-1 };
}

void Board::createAllPeices()
{
	this->Ps = new Peice * [NO_OF_PEICES];

	for (int i = 0; i < NO_OF_PEICES; i++)
	{
		if (i >= 11 && i < NO_OF_PEICES / 2)
			this->Ps[i] = new Pawn({ i - 11, 2 }, WHITE, false, this);
		else if (i >= NO_OF_PEICES/2 && i < NO_OF_PEICES/2 + 9)
			this->Ps[i] = new Pawn({ i - NO_OF_PEICES/2 , 6 }, BLACK, false, this);
		
		else if (i == 0 || i == 8)
			this->Ps[i] = new Lance({ i , 0 }, WHITE, false, this);
		else if (i == NO_OF_PEICES - 9 || i == NO_OF_PEICES - 1)
			this->Ps[i] = new Lance({ i - (NO_OF_PEICES - 9) , 8 }, BLACK, false, this);
		
		else if (i == 1 || i == 7)
			this->Ps[i] = new Knight({ i, 0 }, WHITE, false, this);
		else if (i == NO_OF_PEICES - 8 || i == NO_OF_PEICES - 2)
			this->Ps[i] = new Knight({ i - (NO_OF_PEICES - 9) , 8 }, BLACK, false, this);
		
		else if (i == 2 || i == 6)
			this->Ps[i] = new SilverGeneral({ i, 0 }, WHITE, false, this);
		else if (i == NO_OF_PEICES - 7 || i == NO_OF_PEICES - 3)
			this->Ps[i] = new SilverGeneral({ i - (NO_OF_PEICES - 9)  , 8 }, BLACK, false, this);
		
		else if (i == 3 || i == 5)
			this->Ps[i] = new GoldenGeneral({ i, 0 }, WHITE, false, this);
		else if (i == NO_OF_PEICES - 6 || i == NO_OF_PEICES - 4)
			this->Ps[i] = new GoldenGeneral({ i - (NO_OF_PEICES - 9) , 8 }, BLACK, false, this);
		
		else if (i == 4)
			this->Ps[i] = new King({ i , 0 }, WHITE, false, this);
		else if (i == NO_OF_PEICES - 5)
			this->Ps[i] = new King({ i - (NO_OF_PEICES - 9) , 8 }, BLACK, false, this);
		
		else if (i == 10)
			this->Ps[i] = new Bishop({ 7 , 1 }, WHITE, false, this);
		else if (i == 29)
			this->Ps[i] = new Bishop({ 1 , 7 }, BLACK, false, this);
		
		else if (i == 9)
			this->Ps[i] = new Rook({ 1, 1 }, WHITE, false, this);
		else if (i == 30)
			this->Ps[i] = new Rook({ 7 , 7 }, BLACK, false, this);
	}
}

void Board::createCells()
{
	this->cells = new Cell * *[NO_OF_ROWS];
	for (int ri = 0, pi = 0; ri < NO_OF_ROWS; ri++)
	{
		this->cells[ri] = new Cell * [NO_OF_COLS];
		for (int ci = 0; ci < NO_OF_COLS; ci++)
		{
			if (ri == 2
				||  ri == 6
				|| (ri == 1 || ri == 7) && (ci == 1 || ci == 7)
				|| (ri == 0 || ri == 8)) {

				this->cells[ri][ci] = new Cell(this->Ps[pi], ci * CELL_X + X_TRANSLATE + ci*2, ri * CELL_Y + Y_TRANSLATE + ri*2);
				pi++;
			}
			else
				this->cells[ri][ci] = new Cell(nullptr, ci * CELL_X + X_TRANSLATE + ci*2, ri * CELL_Y + Y_TRANSLATE + ri*2);
		}
	}
}

void Board::createAllSlabs()
{
	this->slabs = new Slab ** [NO_OF_PLAYERS];

	for (int pi = 0; pi < NO_OF_PLAYERS; pi++)
	{
		this->slabs[pi] = new Slab* [NO_OF_SLABS];

		int X,
			color;
		if (pi == 0)
		{
			X = X_TRANSLATE - 150;
			color = BLACK;
		}
		else
		{
			X = X_TRANSLATE + (CELL_X * NO_OF_COLS) + 45;
			color = WHITE;
		}

		for (int si = 0; si < NO_OF_SLABS; si++)
		{
			this->slabs[pi][si] = new Slab(X, (si * SLAB_Y) + 10, color);
		}
	}
}

void Board::drawFrame()
{
	setfillstyle(SOLID_FILL, CELL_OUTLINE);

	setcolor(CELL_OUTLINE);

	bar3d(X_TRANSLATE - 10, Y_TRANSLATE - 10, X_TRANSLATE, Y_TRANSLATE + (CELL_Y * NO_OF_ROWS) + 10, 0, false);

	bar3d(X_TRANSLATE + (CELL_X * NO_OF_COLS), Y_TRANSLATE - 10, X_TRANSLATE + (CELL_X * NO_OF_COLS) + 10, Y_TRANSLATE + (CELL_Y * NO_OF_ROWS) + 10, 0, false);

	bar3d(X_TRANSLATE, Y_TRANSLATE - 10, X_TRANSLATE + (CELL_X * NO_OF_COLS), Y_TRANSLATE, 0, false);

	bar3d(X_TRANSLATE, Y_TRANSLATE + (CELL_Y * NO_OF_ROWS), X_TRANSLATE + (CELL_X * NO_OF_COLS), Y_TRANSLATE + (CELL_Y * NO_OF_ROWS) + 10, 0, false);

	setcolor(COLOR(30, 15, 0));

	line(X_TRANSLATE - 10, Y_TRANSLATE - 10, X_TRANSLATE, Y_TRANSLATE);

	line(X_TRANSLATE + (CELL_X * NO_OF_COLS), Y_TRANSLATE, X_TRANSLATE + (CELL_X * NO_OF_COLS) + 10, Y_TRANSLATE - 10);

	line(X_TRANSLATE - 10, Y_TRANSLATE + (CELL_Y * NO_OF_ROWS) + 10, X_TRANSLATE, Y_TRANSLATE + (CELL_Y * NO_OF_ROWS));

	line(X_TRANSLATE + (CELL_X * NO_OF_COLS), Y_TRANSLATE + (CELL_Y * NO_OF_ROWS), X_TRANSLATE + (CELL_X * NO_OF_COLS) + 10, Y_TRANSLATE + (CELL_Y * NO_OF_ROWS) + 10);
}

void Board::drawCells()
{
	for (int ri = 0; ri < 9; ri++)
		for (int ci = 0; ci < 9; ci++)
		{
			this->cells[ri][ci]->draw();
		}
}

void Board::drawSlabs()
{
	for (int pi = 0; pi < NO_OF_PLAYERS; pi++)
		for (int ri = 0; ri < NO_OF_SLABS; ri++)
		{
			setfillstyle(SOLID_FILL, SLAB_COLOR);

			setcolor(SLAB_OUTLINE);

			this->slabs[pi][ri]->draw();
		}
}

void Board::drawCaution(int x, int y)
{
	setfillstyle(SOLID_FILL, COLOR(145, 0, 0));

	fillellipse(x + 20, y - 25, 10, 11);

	int ps[8] = {
		x + 19, y - 31,
		x + 22, y - 31,
		x + 20, y - 24,
		x + 17, y - 24
	};

	setfillstyle(SOLID_FILL, WHITE);
	setcolor(WHITE);

	fillpoly(4, ps);

	fillellipse(x + 18, y - 21, 2, 2);
}



//				PUBLIC

Board::Board()
{
	std::vector<std::vector<Peice*>>cPs;

	std::vector<Peice*>cps;
	/*
	for (int j = 0; j < 7; j++)
		cPs.push_back(cps);

	for (int i = 0; i < 2; i++)
		this->capPs.push_back(cPs);*/

	this->createAllSlabs();

	this->createAllPeices();

	this->createCells();
}

void Board::drawNodes()
{
	setfillstyle(SOLID_FILL, CELL_OUTLINE);

	setcolor(CELL_OUTLINE);

	fillellipse(this->cells[3][3]->getx(), this->cells[3][3]->gety(), 7, 7);

	fillellipse(this->cells[3][6]->getx(), this->cells[3][6]->gety(), 7, 7);

	fillellipse(this->cells[6][3]->getx(), this->cells[6][3]->gety(), 7, 7);

	fillellipse(this->cells[6][6]->getx(), this->cells[6][6]->gety(), 7, 7);
}

void Board::drawBoard()
{
	this->drawFrame();

	this->drawCells();	

	this->drawNodes();

	this->drawSlabs();
}

void Board::highlight(Pos src, int color)
{
	Peice* sourcePeice{ nullptr };

	if (src.x < 0)	//Slabs have -ve x indices.
	{
		src.x += 2;
		sourcePeice = this->slabs[src.x][src.y]->getPeice();
	}
	else
		sourcePeice = this->cells[src.y][src.x]->getPeice();

	setcolor(CELL_OUTLINE);

	if (!sourcePeice->getCaptured())
	{/*
		this->cells[src.y][src.x]->draw();

		this->cells[src.y][src.x]->setHighlighted(true);

		setfillstyle(SOLID_FILL, HIGHLIGHT_COLOR);

		setcolor(CELL_OUTLINE);*/
	}
	else
	{
		//setfillstyle(SOLID_FILL, HIGHLIGHT_COLOR);
	}

	bool validcols[9]{ true,true,true,true,true,true ,true,true,true };

	if(sourcePeice->getName() == "Pawn")
		this->colsWithoutPawns(validcols, color);

	for (int ri = 0; ri < BOARD_Y; ri++)
	{
		for (int ci = 0; ci < BOARD_X; ci++)
		{
			if ((sourcePeice->getCaptured() && sourcePeice->getName() == "Pawn" && validcols[ci]
				|| sourcePeice->isLegalMove({ ci,ri }))
				&& (sourcePeice->getCaptured() || !selfCheck(src, {ci,ri}, color)))
			{
				if (this->cells[ri][ci]->isempty())
				{
					this->cells[ri][ci]->highlight();
				}
				else if(this->cells[ri][ci]->getPeice()->getColor() != sourcePeice->getColor() && !sourcePeice->getCaptured())
				{
					this->cells[ri][ci]->draw(true);

					this->cells[ri][ci]->setHighlighted(true);
				}
			}
		}
	}
}

void Board::unhighlight()
{
	for (int ri = 0; ri < BOARD_Y; ri++)
	{
		for (int ci = 0; ci < BOARD_X; ci++)
		{
			if (this->cells[ri][ci]->getHighlighted())
			{
				if (!this->cells[ri][ci]->isempty())
				{
					this->cells[ri][ci]->draw();

					this->cells[ri][ci]->setHighlighted(false);
				}
				else
					this->cells[ri][ci]->unhighlight();
			}
		}
	}
}

void Board::colsWithoutPawns(bool* validcols, int color)
{
	for (int ci = 0; ci < NO_OF_COLS; ci++)
		for (int ri = 0; ri < NO_OF_ROWS; ri++)
			if (!this->cells[ri][ci]->isempty() && this->cells[ri][ci]->getPeice()->getName() == "Pawn"
				&& this->cells[ri][ci]->getPeice()->getColor() == color)
			{
				validcols[ci] = false;
			}
}

bool Board::inCheck(int color)
{
	Pos kingpos = findKing(color);

	for(int ri = 0; ri < NO_OF_ROWS; ri++)
		for (int ci = 0; ci < NO_OF_COLS; ci++)
			if (!this->cells[ri][ci]->isempty() && this->cells[ri][ci]->getPeice()->getColor() != color
				&& this->cells[ri][ci]->getPeice()->isLegalMove(kingpos))
				return true;
	return false;
}

bool Board::selfCheck(Pos src, Pos des, int player)
{
	Board tempB = *this;

	tempB.move(src, des);

	return tempB.inCheck(player);
}

void Board::move(Pos src, Pos des)
{
	if (src == des)
	{
		return;
	}
	if (src.x < 0)
	{
		this->cells[des.y][des.x]->setPeice(this->slabs[src.x + 2][src.y]->removePeice());
	}
	else
	{
		this->cells[des.y][des.x]->setPeice(this->cells[src.y][src.x]->getPeice());
		this->cells[src.y][src.x]->setPeice(nullptr);
	}
	this->cells[des.y][des.x]->getPeice()->moveTo(des);
}

bool Board::canMove(int player)
{
	for(int sri = 0; sri < NO_OF_ROWS; sri++)
		for (int sci = 0; sci < NO_OF_COLS; sci++)
			if (!this->cells[sri][sci]->isempty() && this->cells[sri][sci]->getPeice()->getColor() == player)
				for (int dri = 0; dri < NO_OF_ROWS; dri++)
					for (int dci = 0; dci < NO_OF_COLS; dci++)
						if (this->cells[sri][sci]->getPeice()->isLegalMove({ dri,dci })
							/*&& !this->cells[dri][dci]->isempty() && this->cells[dri][dci]->getPeice()->getColor() != player*/
							&& !selfCheck({sci, sri}, {dri, dci}, player))
							return true;
	return false;
}

void Board::saveBoard(std::ofstream& fout)
{
	for (int ri = 0; ri < NO_OF_ROWS; ri++)
		for (int ci = 0; ci < NO_OF_COLS; ci++) 
		{
			if (this->cells[ri][ci]->getPeice() == nullptr)
				fout << "- " << false << std::endl;
			else
				fout << this->cells[ri][ci]->getPeice()->getName() << " " << this->cells[ri][ci]->getPeice()->ispromoted() << std::endl;
		}

	for (int ri = 0; ri < NO_OF_PLAYERS; ri++)
		for (int ci = 0; ci < NO_OF_SLABS; ci++)
		{
			if (this->slabs[ri][ci]->getSize() - 1 == 0)
				fout << "-" << " ";
			else
				fout << this->slabs[ri][ci]->getPeice()->getName() << " ";
			fout << this->slabs[ri][ci]->getSize() << " ";
		}
}
void Board::saveBoard(std::fstream& fout)
{
	for (int ri = 0; ri < NO_OF_ROWS; ri++)
		for (int ci = 0; ci < NO_OF_COLS; ci++)
		{
			if (this->cells[ri][ci]->getPeice() == nullptr)
				fout << "- " << false << std::endl;
			else
				fout << this->cells[ri][ci]->getPeice()->getName() << " " << this->cells[ri][ci]->getPeice()->ispromoted() << std::endl;
		}

	for (int ri = 0; ri < NO_OF_PLAYERS; ri++)
		for (int ci = 0; ci < NO_OF_SLABS; ci++)
		{
			if (this->slabs[ri][ci]->getSize() - 1 == 0)
				fout << "-" << " ";
			else
				fout << this->slabs[ri][ci]->getPeice()->getName() << " ";
			fout << this->slabs[ri][ci]->getSize() << " ";
		}
}


Board::Board(std::ifstream&fin)
{
	this->cells = new Cell * *[NO_OF_ROWS];
	this->Ps = new Peice * [NO_OF_PEICES];

	for (int ri = 0; ri < NO_OF_ROWS; ri++)
	{
		this->cells[ri] = new Cell * [NO_OF_COLS];

		for (int ci = 0; ci < NO_OF_COLS; ci++)
		{
			std::string n{};	int color{};	bool isProm{};
			fin >> n >> isProm;

			if (ri <= 2)
				color = WHITE;

			if (n == "-")
				this->cells[ri][ci] = new Cell(nullptr, ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			else if (n == "Pawn")
				this->cells[ri][ci] = new Cell(new Pawn({ ci,ri }, color, isProm, this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			else if (n == "Lance")
				this->cells[ri][ci] = new Cell(new Lance({ ci,ri }, color, isProm, this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			else if (n == "Knight")
				this->cells[ri][ci] = new Cell(new Knight({ ci,ri }, color, isProm, this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			else if (n == "SilverGeneral")
				this->cells[ri][ci] = new Cell(new SilverGeneral({ ci,ri }, color, isProm, this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			else if (n == "GoldenGeneral")
				this->cells[ri][ci] = new Cell(new GoldenGeneral({ ci,ri }, color, isProm, this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			else if (n == "Bishop")
				this->cells[ri][ci] = new Cell(new Bishop({ ci,ri }, color, isProm, this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			else if (n == "Rook")
				this->cells[ri][ci] = new Cell(new Rook({ ci,ri }, color, isProm, this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);
			else if (n == "King")
				this->cells[ri][ci] = new Cell(new King({ ci,ri }, color, isProm, this), ci * CELL_X + X_TRANSLATE, ri * CELL_Y + Y_TRANSLATE);

			if (n != "-")
			{
				this->cells[ri][ci]->getPeice()->setCaptured(false);
			}
		}
	}

	this->slabs = new Slab** [NO_OF_PLAYERS];

	for (int ci = 0; ci < NO_OF_PLAYERS; ci++)
	{
		this->slabs[ci] = new Slab * [NO_OF_SLABS];

		int size{}, X{}, x{}, y{}, color{};

		if (ci == 0)
			color = WHITE, x = -2, X = X_TRANSLATE - 150;
		else
			color = BLACK, x = -1, X = X_TRANSLATE + (CELL_X * NO_OF_COLS) + 45;;

		for (int ri = 0; ri < NO_OF_SLABS; ri++)
		{
			std::string n{};		
			fin >> n >> size;

			this->slabs[ci][ri] = new Slab(X, ri * SLAB_Y + 10, color);
			
			if (n == "-")
				continue;

			for (int pi = 0; pi < size - 1; pi++)
			{
				if(n == "Pawn")
					this->slabs[ci][ri]->addPeice(new Pawn({x,ri}, color, false, this));
				else if (n == "Lance")
					this->slabs[ci][ri]->addPeice(new Lance({ x,ri }, color, false, this));
				else if (n == "Knight")
					this->slabs[ci][ri]->addPeice(new Knight({ x,ri }, color, false, this));
				else if (n == "SilverGeneral")
					this->slabs[ci][ri]->addPeice(new SilverGeneral({ x,ri }, color, false, this));
				else if (n == "GoldenGeneral")
					this->slabs[ci][ri]->addPeice(new GoldenGeneral({ x,ri }, color, false, this));
				else if (n == "King")
					this->slabs[ci][ri]->addPeice(new King({ x,ri }, color, false, this));
				else if (n == "Bishop")
					this->slabs[ci][ri]->addPeice(new Bishop({ x,ri }, color, false, this));
				else if (n == "Rook")
					this->slabs[ci][ri]->addPeice(new Rook({ x,ri }, color, false, this));

				if (n != "-")
					this->slabs[ci][ri]->getPeice()->setCaptured(true);
			}
		}
	}
}

Board::~Board()
{
	for (int ri = 0; ri < NO_OF_ROWS; ri++)
	{
		for (int ci = 0; ci < NO_OF_COLS; ci++)
		{
			cells[ri][ci]->~Cell();
		}
		delete[] this->cells[ri];
	}
	delete[]this->cells;

	delete[]this->Ps;
}


//				STATIC


bool Board::isVertClr(Pos p1, Pos p2, Board* B)
{
	int si = (p1.y < p2.y) ? p1.y : p2.y;
	int ei = (p1.y > p2.y) ? p1.y : p2.y;

	for (int i = si + 1; i < ei; i++)
		if (!B->cells[i][p1.x]->isempty())
			return false;
	
	return true;
}

bool Board::isHorzClr(Pos p1, Pos p2, Board* B)
{
	int si = (p1.x < p2.x) ? p1.x : p2.x;
	int ei = (p1.x > p2.x) ? p1.x : p2.x;

	for (int i = si + 1; i < ei; i++)
		if (!B->cells[p1.y][i]->isempty())
			return false;

	return true;
}

bool Board::isDiagClr(Pos p1, Pos p2, Board* B)
{
	int reps = abs(p1.y - p2.y);

	for (int i = 1; i < reps; i++)
	{
		if (p1.y > p2.y && p1.x > p2.x)
			if (!B->cells[p1.y - i][p1.x - i]->isempty())
				return false;
		if (p1.y < p2.y && p1.x > p2.x)
			if (!B->cells[p1.y + i][p1.x - i]->isempty())
				return false;
		if (p1.y > p2.y && p1.x < p2.x)
			if (!B->cells[p1.y - i][p1.x + i]->isempty())
				return false;
		if (p1.y < p2.y && p1.x < p2.x)
			if (!B->cells[p1.y + i][p1.x + i]->isempty())
				return false;
	}
	return true;
}