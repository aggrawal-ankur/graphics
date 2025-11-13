#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <graphics.h>

#define MIN(a, b)    ( a < b ? a : b )
#define MAX(a, b)    ( a > b ? a : b )
#define ROUND(x)     ( (int)(x + 0.5) )

void drawLine(int x1, int y1, int x2, int y2) {
  float dx, dy, m, b;
  int start_x, end_x, x, y;
  float y_float, x_float;

  dx = x2 - x1;
  dy = y2 - y1;

  // Check for a vertical line (m is infinite)
  if (dx == 0) {
    // Iterate along the y-axis
    for (y = MIN(y1, y2); y <= MAX(y1, y2); y++) {
      putpixel(x1, y, WHITE);
    }
    return; // Exit the function for vertical lines
  }
  y = 0;

  m = dy / dx;        // Slope (m)
  b = y1 - m * x1;    // Y-Intercept (b = y - mx)

  // Determine the dominant axis for iteration
  if (fabs(m) <= 1) { // Iterate along X-axis
    // Ensure x1 is the start and x2 is the end for iteration
    start_x = MIN(x1, x2);
    end_x = MAX(x1, x2);

    // Iterate and print
    for (x = start_x; x <= end_x; x++) {
      y_float = m * x + b;
      putpixel(x, ROUND(y_float), WHITE);
    }
  }
  else { // Iterate along Y-axis    
    // Ensure y1 is the start and y2 is the end for iteration
    int start_y = MIN(y1, y2);
    int end_y = MAX(y1, y2);

    // Iterate and print
    for (y = start_y; y <= end_y; y++) {
      x_float = (y - b) / m;
      putpixel(ROUND(x_float), y, WHITE);
    }
  }
}

void main() {
  int gd = DETECT, gm;
  initgraph(&gd, &gm, "C:\\TURBOC3\\BGI"); 
  
  drawLine(50, 50, 300, 150);
  getch();
  closegraph();
}