/* drawpoly example */



#include "graphics.h"

#include <stdlib.h>

#include <stdio.h>

#include "Shogi.h"

#include "Board.h"



void drawBase(int x, int y, int color)
{
    int maxx = x + 15, minx = x - 15;

    bar3d(minx, y + 20, maxx, y + 28, 0, false);

    if (true)
    {
        arc(x, y + 40, 55, 125, 25);

        floodfill(x, y + 19, OUTLINE);
    }

    if (color == BLACK) {
        setfillstyle(SOLID_FILL, BLACK_DARK);
        setcolor(BLACK_DARK);
    }
    else {
        setfillstyle(SOLID_FILL, WHITE_DARK);
        setcolor(WHITE_DARK);
    }
    bar3d(maxx - 9, y + 21, maxx - 1, y + 27, 0, false);

    if (color == BLACK) {
        setfillstyle(SOLID_FILL, BLACK_SHADE);
        setcolor(BLACK_SHADE);
    }
    else {
        setfillstyle(SOLID_FILL, WHITE_SHADE);
        setcolor(WHITE_SHADE);
    }
    bar3d(minx + 1, y + 21, minx + 7, y + 27, 0, false);
}

void draw(int x, int y, bool ispromoted)
{
	int maxx = x + 12, minx = x - 12;

   // bar3d(minx + 2, y - 19, maxx - 2, y - 15, 0, false);

    int Ps[12] = {
        x - 4, y - 12,
        x - 8, y + 2,
        minx, y + 10,
        maxx, y + 10,
        x + 8, y + 2,
        x + 4, y - 12
    };

   // fillpoly(6, Ps);

    drawBase(x, y, WHITE);

    if (ispromoted)
    {
        int ps[10] = {
       x - 7, y - 22,
       x + 7, y - 22,
       maxx - 6, y - 30,
       x , y - 34,
       minx + 6, y - 30
        };

//        fillpoly(5, ps);


        //fillellipse(x, y - 18, 4, 7);

        y -= 3;

        x += 5;

        int Ps[14] = {
            x + 10, y - 8,
            x + 15, y - 18,
            x + 14, y - 38,
            x + 21, y - 19,
            x + 17, y - 8,
            x + 10, y - 8
        };

        fillpoly(6, Ps);

        y += 8;

        int Ps1[12] = {
            x + 6, y,
            x + 20, y - 11,
            maxx + 23, y - 25,
            maxx + 21, y - 12,
            x + 19, y - 2,
            x + 15, y - 3 
        };

        fillpoly(5, Ps1);


        ///////////////////////////////////////////////////////////////////


        y -= 8;

        x -= 10;

        int Ps2[14] = {
            x - 10, y - 8,
            x - 15, y - 18,
            x - 14, y - 38,
            x - 21, y - 19,
            x - 17, y - 8,
            x - 10, y - 8
        };

        fillpoly(6, Ps2);

        y += 8;

        int Ps3[14] = {
            x - 6, y,
            x - 20, y - 11,
            minx - 23, y - 25,
            minx - 21, y - 12,
            x - 19, y - 2,
            x - 15, y - 3
        };

        fillpoly(6, Ps3);
    }
    else
    {
        int Ps1[8] = {
       x - 7, y - 22,
       x + 7, y - 22,
       maxx, y - 32,
       minx, y - 32
        };

        fillpoly(4, Ps1);
    }

    x += 5, y -= 5;

}



int main(void)

{

    /* request autodetection */

    int gdriver = DETECT, gmode, errorcode;



    int mainwin = initwindow(1530, 780, "Shogi");


    int maxx = getmaxx(), maxy = getmaxy();

  
    errorcode = graphresult();

    if (errorcode != grOk) { /* an error occurred */

        printf("Graphics error: %s\n", grapherrormsg(errorcode));



        printf("Press any key to halt:");

        getch();

        exit(1);             /* terminate with an error code */

    }


    Shogi shogi;

    shogi.play(mainwin);




    /* clean up */

    getch();

    closegraph();

    return 0;

}
