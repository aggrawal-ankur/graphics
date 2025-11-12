#include <stdio.h>
#include <graphics.h>
#include <conio.h>

int Xmin = 40, Ymin = 40;     // Clip Window
int Xmax = 100, Ymax = 100;

#define ABOVE    8    // Regions
#define BELOW    4
#define RIGHT    2
#define LEFT     1

int calcCode(int x, int y){
  int code = 0;

  if (y > Ymax) code |= ABOVE;
  if (y < Ymin) code |= BELOW;
  if (x > Xmax) code |= RIGHT;
  if (x < Xmin) code |= LEFT;

  return code;
}

int ClipLine(int x1, int y1, int x2, int y2){
  int rcodeP1, rcodeP2, outCode;
  int accept = 0, done = 0;
  float fx1 = x1, fy1 = y1, fx2 = x2, fy2 = y2, m;
  int xclip, yclip;

  rcodeP1 = calcCode(fx1, fy1);
  rcodeP2 = calcCode(fx2, fy2);

  do{
    if ((rcodeP1 | rcodeP2) == 0){        // Trivial accept
      accept = 1;
      done = 1;
    } else if ((rcodeP1 & rcodeP2) != 0){ // Trivial reject
      done = 1;
    } else{
      if (rcodeP1 != 0)  outCode = rcodeP1;
      else  outCode = rcodeP2;

      m = (fy2 - fy1)/(fx2 - fx1);        // Calculate slope

      // Find the edge the endpoint is intersecting with and calculate the intersection point
      if (outCode & ABOVE){
        xclip = (int)(fx1 + (Ymax - fy1)/m);
        yclip = Ymax;
      } else if (outCode & BELOW){
        xclip = (int)(fx1 + (Ymin - fy1)/m);
        yclip = Ymin;
      } else if (outCode & RIGHT){
        yclip = (int)(fy1 + m*(Xmax - fx1));
        xclip = Xmax;
      } else if (outCode & LEFT){
        yclip = (int)(fy1 + m*(Xmin - fx1));
        xclip = Xmin;
      }

      // Replace the point that was outside
      if (outCode == rcodeP1){
        fx1 = xclip;
        fy1 = yclip;
      } else{
        fx2 = xclip;
        fy2 = yclip;
      }

      // Update the region codes for the new points
      rcodeP1 = calcCode(fx1, fy1);
      rcodeP2 = calcCode(fx2, fy2);
    }
  } while(!done);

  if (accept){
    // Draw the cliped line
    setcolor(YELLOW);
    line((int)fx1, (int)fy1, (int)fx2, (int)fy2);
  }
  return 0;
}

void main(){
  int gd = DETECT, gm;
  initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

  rectangle(Xmin, Ymin, Xmax, Ymax);    // Draw the clip window

  setcolor(WHITE);
  line(10, 10, 70, 70);
  line(10, 90, 70, 100);
  line(90, 10, 100, 70);
  line(-20, -10, -10, -50);
  line(40, 40, 100, 100);
  line(-10, 10, 90, 70);
  getch();

  ClipLine(10, 10, 70, 70);
  ClipLine(10, 90, 70, 100);
  ClipLine(90, 10, 100, 70);
  ClipLine(-20, -10, -10, -50);
  ClipLine(40, 40, 100, 100);
  ClipLine(-10, 10, 90, 70);
  getch();

  closegraph();
}