#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>

void floodFill(int x, int y, int fillColor, int bgColor) {
  // Check if the current pixel is within the boundary and still has the bgColor
  if (getpixel(x, y) == bgColor) {
    putpixel(x, y, fillColor);
    delay(1);

    floodFill(x + 1, y, fillColor, bgColor);
    floodFill(x - 1, y, fillColor, bgColor);
    floodFill(x, y + 1, fillColor, bgColor);
    floodFill(x, y - 1, fillColor, bgColor);
  }
}

void main(){  
  int gd = DETECT, gm;
  initgraph(&gd, &gm, "C:\\TURBOC3\\BGI"); 

  line(100, 100, 200, 200);
  line(200, 200, 150, 50);
  line(150, 50, 100, 100);

  printf("Starting Flood Fill...\n");
  floodFill(150, 100, RED, BLACK);      // Start with a point inside the polygon

  getch();
  closegraph();
}