#include <stdio.h>
#include <graphics.h>
#include <conio.h>

#define MAX 50

typedef struct {
  float x, y;
} Point;

typedef struct {
  Point vertices[MAX];
  int n; // number of vertices
} Polygon;

// Clip window boundaries
typedef struct {
  float xmin, ymin, xmax, ymax;
} ClipWindow;

// Helper: compute intersection with a boundary
Point intersect(Point A, Point B, char boundary, ClipWindow clip) {
  Point I;
  float m;

  if (boundary == 'L') { // Left
    I.x = clip.xmin;
    m = (B.y - A.y) / (B.x - A.x);
    I.y = A.y + m * (clip.xmin - A.x);
  }
  else if (boundary == 'R') { // Right
    I.x = clip.xmax;
    m = (B.y - A.y) / (B.x - A.x);
    I.y = A.y + m * (clip.xmax - A.x);
  } 
  else if (boundary == 'B') { // Bottom
    I.y = clip.ymin;
    m = (B.x - A.x) / (B.y - A.y);
    I.x = A.x + m * (clip.ymin - A.y);
  } 
  else if (boundary == 'T') { // Top
    I.y = clip.ymax;
    m = (B.x - A.x) / (B.y - A.y);
    I.x = A.x + m * (clip.ymax - A.y);
  }
  return I;
}

// Helper: check if point is inside a boundary
int inside(Point p, char boundary, ClipWindow clip) {
  if (boundary == 'L') return p.x >= clip.xmin;
  if (boundary == 'R') return p.x <= clip.xmax;
  if (boundary == 'B') return p.y >= clip.ymin;
  if (boundary == 'T') return p.y <= clip.ymax;
  return 0;
}

// Clip polygon against one boundary
Polygon clipPolygon(Polygon poly, char boundary, ClipWindow clipW) {
  int i = 0;
  Point S = poly.vertices[poly.n - 1];        // Last vertex of polygon

  Polygon out;
  out.n = 0;


  for (; i < poly.n; i++) {
    Point P = poly.vertices[i];               // First vertex of polygon

    if (inside(P, boundary, clipW)) {
      if (inside(S, boundary, clipW)) {
        // Case 1: S in, P in
        out.vertices[out.n++] = P;
      } 
      else {
        // Case 3: S out, P in
        out.vertices[out.n++] = intersect(S, P, boundary, clipW);
        out.vertices[out.n++] = P;
      }
    }
    else {
      if (inside(S, boundary, clipW)) {
        // Case 2: S in, P out
        out.vertices[out.n++] = intersect(S, P, boundary, clipW);
      }
      // Case 4: both out → do nothing
    }
    S = P;
  }
  return out;
}

// Full Sutherland-Hodgman algorithm
Polygon sutherlandHodgman(Polygon poly, ClipWindow clipW) {
  char boundaries[4] = {'L', 'R', 'B', 'T'};
  int i = 0;

  for (; i < 4; i++) {
    poly = clipPolygon(poly, boundaries[i], clipW);
  }
  return poly;
}

int main() {
  int gd = DETECT, gm;
  int i = 0;
  ClipWindow clipW = {100, 100, 300, 300};
  Polygon orgPoly = {
    {
      {140, 150},
      {150, 160},
      {260, 260},
      {250, 200},
      {160, 250}
      // {50, 150},
      // {150, 50},
      // {350, 160},
      // {250, 350},
      // {60, 250}
    }, 
    5
  };
  Polygon clipPoly;

  // printf("enter:\n");
  // scanf("%d", &i);
  initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

  rectangle(clipW.xmin, clipW.ymin, clipW.xmax, clipW.ymax);

  printf("Original polygon in WHITE:\n");
  for (; i < orgPoly.n; i++) {
    if (i == (orgPoly.n - 1)){
      line(orgPoly.vertices[i].x, orgPoly.vertices[i].y, orgPoly.vertices[0].x, orgPoly.vertices[0].y);
      break;
    }

    line(orgPoly.vertices[i].x, orgPoly.vertices[i].y, orgPoly.vertices[i+1].x, orgPoly.vertices[i+1].y);
  }
  getch();
  
  clipPoly = sutherlandHodgman(orgPoly, clipW);
  i = 0;

  printf("Clipped polygon in RED:\n");
  setcolor(RED);
  for (; i < clipPoly.n; i++) {
    if (i == (clipPoly.n - 1)){
      line(clipPoly.vertices[i].x, clipPoly.vertices[i].y, clipPoly.vertices[0].x, clipPoly.vertices[0].y);
      break;
    }

    line(clipPoly.vertices[i].x, clipPoly.vertices[i].y, clipPoly.vertices[i+1].x, clipPoly.vertices[i+1].y);
  }

  getch();
  closegraph();

  return 0;
}
