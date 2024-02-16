#include <graphics.h>
#include <cstdlib>
#include <stdio.h>
#include <cmath>

void drawLineBresenham(int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int x = x0, y = y0;

    int xStep = (x0 < x1) ? 1 : -1;
    int yStep = (y0 < y1) ? 1 : -1;

    if (dx >= dy) {
        int p = 2 * dy - dx;
        while (x != x1) {
            putpixel(x, y, color);
            x += xStep;
            if (p >= 0) {
                y += yStep;
                p -= 2 * dx;
            }
            p += 2 * dy;
        }
    } else {
        int p = 2 * dx - dy;
        while (y != y1) {
            putpixel(x, y, color);
            y += yStep;
            if (p >= 0) {
                x += xStep;
                p -= 2 * dy;
            }
            p += 2 * dx;
        }
    }
    putpixel(x, y, YELLOW);
}


void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xc = (float)dx / steps;
    float yc = (float)dy / steps;

    float x = x1, y = y1;

    for (int i = 0; i <= steps; ++i) {
        putpixel(round(x), round(y), WHITE);
        x += xc;
        y += yc;
    }
}


void drawRectangle(int x1, int y1, int x2, int y2) {
    drawLineDDA(x1, y1, x2, y1);
    drawLineDDA(x2, y1, x2, y2);
    drawLineDDA(x2, y2, x1, y2);
    drawLineDDA(x1, y2, x1, y1);
}

void plotOctant(int xc ,int x, int yc, int y, int color){

    putpixel(xc + y, yc - x, color);
    putpixel(xc + x, yc - y, color);


    putpixel(xc - x, yc - y, color);
    putpixel(xc - y, yc - x, color);


    putpixel(xc - y, yc + x, color);
    putpixel(xc - x, yc + y, color);


    putpixel(xc + x, yc + y, color);
    putpixel(xc + y, yc + x, color);
}

void drawCircle(int xc, int yc, int radius) {
    int y = radius, x = 0;
    int radiusError = 1 - radius;
    while (x <= y) {
        plotOctant(xc,x,yc,y,WHITE);
        x++;

        if (radiusError < 0)
            radiusError += 2 * x + 1;
        else {
            y--;
            radiusError += 2 * (x - y) + 1;
        }
    }
}




void drawCircleBresenham(int xc, int yc, int r) {
    int x = 0, y = r;
    int s = 3 - 2 * r;

    while (x <= y) {

        putpixel(xc + x, yc + y, YELLOW);
        putpixel(xc - x, yc + y, YELLOW);
        putpixel(xc + x, yc - y, YELLOW);
        putpixel(xc - x, yc - y, YELLOW);
        putpixel(xc + y, yc + x, YELLOW);
        putpixel(xc - y, yc + x, YELLOW);
        putpixel(xc + y, yc - x, YELLOW);
        putpixel(xc - y, yc - x, YELLOW);

        x++;

        if (s <= 0)
            s = s + 4 * x + 6;
        else {
            y--;
            s = s + 4 * (x - y) + 10;
        }
    }


}

void drawMarioLevel() {
    //levels gorund
    drawLineDDA(0, 600, 1599, 600);
    setfillstyle(WIDE_DOT_FILL, LIGHTRED);
    floodfill(1400, 700, WHITE);

//white clouds
    drawCircle(1400, 50, 30);
    setfillstyle(SOLID_FILL, WHITE);//first cloud
    floodfill(1400, 50, WHITE);

    drawCircle(1360, 68, 30); // left cloud
    setfillstyle(SOLID_FILL, WHITE);
    floodfill(1360, 68, WHITE);

    drawCircle(1400, 79, 35);
    setfillstyle(SOLID_FILL, WHITE);
    floodfill(1400, 79, WHITE);


    drawCircle(1440, 69, 30); // rightcloud
    setfillstyle(SOLID_FILL, WHITE);
    floodfill(1440, 69, WHITE);


    //BIG M FOR MARIO
    drawLineDDA(100, 150, 110, 100);
    drawLineDDA(110, 100, 120, 150);
    drawLineDDA(120, 150, 130, 100);
    drawLineDDA(130, 100, 140, 150);


    //LEVEL FINISH FLAG
    drawLineDDA(900, 600, 900, 100);
    drawLineDDA(880, 110, 900, 90); //left
    drawLineDDA(880, 110, 900, 110); //top
    drawCircle(900,85,5);
    drawLineDDA(900, 90, 900, 110); //Right


    //red flag
    setfillstyle(SOLID_FILL, RED);
    floodfill(890, 105, WHITE); // Assuming WHITE represents the border color

    //flag corcle styuling
    setfillstyle(SOLID_FILL, GREEN);
    floodfill(900, 85, WHITE); // Assuming WHITE represents the border color

//left block
    drawLineDDA(1000, 600, 1000, 400);
    drawLineDDA(1000, 400, 1100, 400);


//middle block
    drawLineDDA(1100, 300, 1300, 300);
    drawLineDDA(1100, 300, 1100, 400);
    drawLineDDA(1300, 300, 1300, 400);
    drawRectangle(1150,350,1175,395);//LEFT WINDOW
    drawRectangle(1225,350,1250,395);//RIGHT WINDOW
    // Draw the door
    drawLineDDA(1165, 500, 1165, 600);
    drawLineDDA(1235, 500, 1235, 600);
    drawLineDDA(1165, 598, 1235, 598);

//main door
    setfillstyle(LTSLASH_FILL, BLACK);
    floodfill(1200, 590, WHITE);

    drawLineDDA(1165, 500, 1200, 450);
    drawLineDDA(1235, 500, 1200, 450);

//right side block
    drawLineDDA(1300, 400, 1400, 400);
    drawLineDDA(1400, 400, 1400, 600);

    //castle stlying
    setfillstyle(HATCH_FILL, LIGHTRED);
    floodfill(1050, 500, WHITE);

    //PIPE
    drawLineDDA(350, 600, 350, 500);
    drawLineDDA(400, 600, 400, 500);
    drawLineDDA(340, 500, 410, 500);

    //pipe top
    drawLineDDA(340, 470, 340, 500); // Left side of the pipe
    drawLineDDA(340, 470, 410, 470); // top of pipe
    drawLineDDA(410, 470, 410, 500); //RIGHT SIDE OF THE PIPE
    setfillstyle(SOLID_FILL, GREEN);
    floodfill(375, 550, WHITE);
    setfillstyle(SOLID_FILL, GREEN);
    floodfill(345, 490, WHITE);

    //platform
    drawLineDDA(400, 300, 400, 350); // Left
    drawLineDDA(400, 300, 600, 300); // top
    drawLineDDA(600, 300, 600, 350); // right
    drawLineDDA(400, 350, 600, 350); //bottom

    //coins
    drawCircleBresenham(425, 275, 15);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(425, 275, YELLOW);
    drawCircleBresenham(500, 275, 15);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(500, 275, YELLOW);
    drawCircleBresenham(575, 275, 15);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(575, 275, YELLOW);


    setfillstyle(HATCH_FILL, LIGHTRED);
    floodfill(410, 325, WHITE);
    //steps
    int stepHeight = 40;
    for (int i = 0; i < 5; i++) {
        drawLineDDA(500 + i * 30, 600 - i * stepHeight, 530 + i * 30, 600 - i * stepHeight);
        drawLineDDA(530 + i * 30, 600 - i * stepHeight, 530 + i * 30, 600 - (i + 1) * stepHeight);
        drawLineDDA(530 + i * 30, 600 - (i + 1) * stepHeight, 560 + i * 30, 600 - (i + 1) * stepHeight);
    }
    drawLineBresenham(680,400,680,600,WHITE);
    drawLineBresenham(530,600,680,600,WHITE);
    setfillstyle(HATCH_FILL, LIGHTRED);
    floodfill(535, 585, WHITE);
}
void drawMario() {

    //marios hat
    drawCircle(100, 500, 20);
    drawLineDDA(90, 470, 110, 470); //hat bottom
    drawLineDDA(90, 470, 80, 480); //hat left
    drawLineDDA(110, 470, 120, 480); //hat right
    drawLineDDA(80, 480, 120, 480); //hat top
    drawLineDDA(120, 480, 130, 480); //hat line
    setfillstyle(SOLID_FILL, RED);
    floodfill(92, 475, WHITE); //hats color


    //marios body
    drawLineDDA(100, 520, 100, 570);

    //hands
    drawLineDDA(70, 540, 100, 530); //lefthand
    drawLineDDA(130, 540, 100, 530); //righthand

    //legs
    drawLineDDA(90, 600, 100, 560); //left
    drawLineDDA(110, 600, 100, 560); //right
}


int main() {
    int gd = DETECT, gm;
    initwindow(1600,800);
    drawMarioLevel();
    drawMario();

    drawLineBresenham(100,100,400,200,WHITE);
    drawLineBresenham(400,200,200,400,WHITE);
    drawLineBresenham(200,400,100,100,WHITE);
    getch();

    closegraph();
    return 0;
}




