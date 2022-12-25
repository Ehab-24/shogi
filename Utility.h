#pragma once

#include <Windows.h>

#include <iostream>

#include <string>

#include <vector>

#include "graphics.h"

#include <stdlib.h>

#include <stdio.h>


#define NO_OF_PEICES 40
#define NO_OF_ROWS 9
#define NO_OF_COLS 9

#define STYLE GRADIENT_FILL_TRIANGLE
#define CLR COLOR(100, 100, 100)

#define OUTLINE COLOR(0,0,0)
#define CELL_OUTLINE COLOR(100,60,0)

#define BOARD_Y 9
#define BOARD_X 9

#define CELL_X 82
#define CELL_Y 72

#define SLAB_X 105
#define SLAB_Y 95

#define MAXY getmaxy()
#define MAXX getmaxx()

#define MIDY MAXY/2
#define MIDX MAXX/2

#define X_TRANSLATE 346
#define Y_TRANSLATE 20

#define CELL_COLOR COLOR(220, 160, 65)
#define HIGHLIGHT_COLOR COLOR(245, 195, 95)

#define SOURCE_HIGHLIGHT COLOR(250, 225, 105)
#define KILL_HIGHLIGHT COLOR(255,165,105)

#define TEXT_COLOR COLOR(255,255,0)
#define BK_COLOR COLOR(0,0,0)

#define TEXT_FONT SIMPLEX_FONT

#define COLOR_OF_WHITE COLOR(245, 200, 155)
#define COLOR_OF_BLACK COLOR(90, 25, 10)

#define WHITE_SHADE COLOR(250,240,240)
#define BLACK_SHADE COLOR(185, 110,0)

#define WHITE_DARK COLOR(185, 150, 120)
#define BLACK_DARK COLOR(50,10,0)

#define PAWN_I 0
#define LANCE_I 1
#define KNIGHT_I 2
#define SILVER_I 3
#define GOLD_I 4
#define BISHOP_I 5
#define ROOK_I 6

#define NO_OF_SLABS 7
#define NO_OF_PLAYERS 2

#define SLAB_COLOR COLOR(210, 130, 50)
#define SLAB_OUTLINE BLACK



struct Pos {
	int x{}, y{};
	Pos(int a = 0, int b = 0) :x(a), y(b) {}
	bool operator==(const Pos&p)
	{
		return this->x == p.x && this->y == p.y;
	}
};
