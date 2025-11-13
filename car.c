#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>

void draw_car(int x, int y){
  setcolor(YELLOW);
  rectangle(x, y+20, x+100, y+50);        // Body

  setcolor(RED);
  rectangle(x + 20, y, x + 80, y + 20);   // Roof

  setcolor(BLUE);
  circle(x + 25, y + 50, 10);             // Wheel
  circle(x + 75, y + 50, 10);             // Wheel
}

int main(void) {
  int car_x = 0;    // Horizontal distance of car from the starting point (left)
  int car_y = 100;  // Vertical distance of car from the top of view
  int step = 5;     // Increment; to create animation
  int max_x;        // Max(x-corrdinate)

  int gd = DETECT, gm;
  initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
  
  max_x = getmaxx();
  while(!kbhit() && car_x < max_x){
    cleardevice();            // Clear the previous car
    car_x = car_x + step;
    draw_car(car_x, car_y);
    delay(500);

    if (car_x > max_x){       // wrap around
      car_x = -100;
    }
  }

  getch();
  closegraph();
}
