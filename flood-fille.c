#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>

// Function to implement Flood Fill
void floodFill(int x, int y, int new_color, int old_color) {
  // Check if the current pixel is within the boundary and still has the old_color
  if (getpixel(x, y) == old_color) {
    // Set the pixel to the new_color
    putpixel(x, y, new_color);
    delay(1);

    // Recursively call for all 4 neighbors (4-connected)
    floodFill(x + 1, y, new_color, old_color); // Right
    delay(1);
    floodFill(x - 1, y, new_color, old_color); // Left
    delay(1);
    floodFill(x, y + 1, new_color, old_color); // Down
    delay(1);
    floodFill(x, y - 1, new_color, old_color); // Up
  }
}

// Main function to demonstrate the algorithm
void main() {
  int x1 = 100, y1 = 100;
  int x2 = 200, y2 = 200;
  int x3 = 150, y3 = 50;
  
  // 2. Define the fill parameters
  int seed_x = 150;      // An interior point (e.g., the centroid)
  int seed_y = 100;
  int fill_color = RED;  // e.g., RED (4)
  int old_color = BLACK; // The current color of the interior area, which is usually the background (BLACK=0)
  
  // Initialize graphics mode
  int gd = DETECT, gm;
  initgraph(&gd, &gm, "C:\\TURBOC3\\BGI"); 

  line(x1, y1, x2, y2);
  line(x2, y2, x3, y3);
  line(x3, y3, x1, y1);

  // 3. Perform the Flood Fill
  printf("Starting Flood Fill...\n");
  floodFill(seed_x, seed_y, fill_color, old_color);

  getch();
  closegraph();
}