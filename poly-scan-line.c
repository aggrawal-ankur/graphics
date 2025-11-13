#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h> // For qsort

struct Point { int x, y; };

// Comparison function for qsort: sorts intersection X-coordinates in ascending order.
int compareIntersec(const void *a, const void *b) {
  return ( *(int*)a - *(int*)b );
}

void scanLineFill(struct Point poly[], int n, int fill_color) {
  int i, j, p, y;
  int y_min = poly[0].y;
  int y_max = poly[0].y;
  int y_start, y_end, x_start, x_end, temp;
  float m_inv, x_intersect;

  // 1. Find Y_min and Y_max (global extremes of the polygon)
  for (i = 1; i < n; i++) {
    if (poly[i].y < y_min) y_min = poly[i].y;
    if (poly[i].y > y_max) y_max = poly[i].y;
  }

  // Set the color for the filled area
  setcolor(fill_color);

  // 2. Iterate through each scan line (Y) from bottom to top
  for (y = y_min; y <= y_max; y++) {
    int intersections[20]; // Array to store intersection X-coordinates (arbitrary max size)
    int k = 0;             // Intersection count for the current scan line

    // 3. Find intersection points (X-coordinates)
    for (i = 0; i < n; i++){
      j = (i + 1) % n; // Connects point i to the next point j

      y_start = poly[i].y;
      y_end = poly[j].y;
      x_start = poly[i].x;
      x_end = poly[j].x;

      // Simple vertical swap to ensure P_i is the lower vertex for calculation
      if (y_start > y_end) {
        temp = y_start; y_start = y_end; y_end = temp;
        temp = x_start; x_start = x_end; x_end = temp;
      }

      // Check if the scan line (y) intersects the edge [P_i, P_j]
      // We use 'y_start <= y < y_end' to properly handle shared vertices.
      if (y >= y_start && y < y_end) {
        // Ignore perfectly horizontal edges
        if (y_end == y_start) continue;

        // Calculate the inverse slope (m_inv = dx / dy)
        m_inv = (float)(x_end - x_start) / (float)(y_end - y_start);

        // Calculate X intersection: x = x_start + (y - y_start) * m_inv
        x_intersect = x_start + (y - y_start) * m_inv;

        // Store the rounded integer X intersection (add 0.5 for rounding)
        intersections[k++] = (int)(x_intersect + 0.5); 
      }
    }

    // 4. Sort the intersection points
    if (k > 0) {
      // k should always be even for a closed polygon if handled correctly
      qsort(intersections, k, sizeof(int), compareIntersec);

      // 5. Fill the segments: draw lines between consecutive pairs
      // (x0 to x1), (x2 to x3), etc.
      for (p = 0; p < k; p += 2) {
        if (p + 1 < k) {
          // Draw a horizontal line segment (the fill)
          delay(50);
          line(intersections[p], y, intersections[p + 1], y);
        }
      }
    }
  }
}

void main() {
  struct Point polygon[] = {
    {100, 100}, // P0
    {350, 100}, // P1
    {300, 300}, // P2
    {150, 300}  // P3
  };
  int num_vertices = 4;
  
  int gd = DETECT, gm;
  initgraph(&gd, &gm, "C:\\TURBOC3\\BGI"); 

  line(100, 100, 350, 100);
  line(350, 100, 300, 300);
  line(300, 300, 150, 300);
  line(150, 300, 100, 100);

  scanLineFill(polygon, num_vertices, RED);

  getch();
  closegraph();
}