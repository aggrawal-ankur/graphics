#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>

void main() {
    int gd = DETECT, gm;
    int x1, y1, x2, y2, x3, y3;
    float theta, x1_new, y1_new, x2_new, y2_new, x3_new, y3_new;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    printf("Enter (x1, y1): ");
    scanf("%d %d", &x1, &y1);

    printf("Enter (x2, y2): ");
    scanf("%d %d", &x2, &y2);

    printf("Enter (x3, y3): ");
    scanf("%d %d", &x3, &y3);

    printf("Enter rotation angle (in degrees, positive): ");
    scanf("%f", &theta);

    theta = theta * 3.14159 / 180.0; // Convert to radians

    printf("Original triangle in white\n");
    setcolor(WHITE);
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);

    // Rotate and draw new triangle
    x1_new = x1 * cos(theta) - y1 * sin(theta);
    y1_new = x1 * sin(theta) + y1 * cos(theta);
    x2_new = x2 * cos(theta) - y2 * sin(theta);
    y2_new = x2 * sin(theta) + y2 * cos(theta);
    x3_new = x3 * cos(theta) - y3 * sin(theta);
    y3_new = x3 * sin(theta) + y3 * cos(theta);

    printf("Rotated triangle in yellow\n");
    setcolor(YELLOW);
    line(x1_new, y1_new, x2_new, y2_new);
    line(x2_new, y2_new, x3_new, y3_new);
    line(x3_new, y3_new, x1_new, y1_new);

    getch();
    closegraph();
}
