#include <stdio.h>
#include <conio.h>
#include <graphics.h>

void boundfill(int x, int y, int fillColor, int boundaryColor) {
    int cur = getpixel(x, y);
    if (cur != boundaryColor && cur != fillColor) {
        putpixel(x, y, fillColor);
        delay(1);

        boundfill(x + 1, y, fillColor, boundaryColor);
        boundfill(x - 1, y, fillColor, boundaryColor);
        boundfill(x, y + 1, fillColor, boundaryColor);
        boundfill(x, y - 1, fillColor, boundaryColor);
    }
}

void main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    rectangle(50, 50, 100 ,100);
    boundfill(75, 80, RED, WHITE);

    getch();
    closegraph();
}
