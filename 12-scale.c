#include <stdio.h>
#include <conio.h>
#include <graphics.h>

void main() {
    int gd = DETECT, gm;
    int x1, y1, x2, y2, x3, y3;
    float sx, sy;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    printf("Enter (x1, y1): ");
    scanf("%d %d", &x1, &y1);

    printf("Enter (x2, y2): ");
    scanf("%d %d", &x2, &y2);

    printf("Enter (x3, y3): ");
    scanf("%d %d", &x3, &y3);

    printf("Enter scaling factors (sx, sy): ");
    scanf("%f %f", &sx, &sy);

    printf("Original triangle in white\n");
    setcolor(WHITE);
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);

    printf("Scaled triangle in yellow\n");
    setcolor(YELLOW);
    line(x1 * sx, y1 * sy, x2 * sx, y2 * sy);
    line(x2 * sx, y2 * sy, x3 * sx, y3 * sy);
    line(x3 * sx, y3 * sy, x1 * sx, y1 * sy);

    getch();
    closegraph();
}
