#include <graphics.h>
#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

// Function to check if a point is inside the clipping window
bool isInside(Point p, double xmin, double ymin, double xmax, double ymax) {
    return (p.x >= xmin && p.x <= xmax && p.y >= ymin && p.y <= ymax);
}

// Function to draw a line between two points
void drawLine(Point p1, Point p2) {
    line((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
}

// Function to highlight a point as a small circle
void highlightPoint(Point p) {
    setcolor(YELLOW);
    circle((int)p.x, (int)p.y, 5); // Draw a small circle with radius 5
    floodfill((int)p.x, (int)p.y, YELLOW);
}

// Recursive midpoint subdivision function
void midpointSubdivision(Point p1, Point p2, double xmin, double ymin, double xmax, double ymax) {
    // Check if the entire line is inside the window
    if (isInside(p1, xmin, ymin, xmax, ymax) && isInside(p2, xmin, ymin, xmax, ymax)) {
        drawLine(p1, p2); // Draw line if fully inside
        return;
    }

    // Calculate the midpoint
    Point mid;
    mid.x = (p1.x + p2.x) / 2;
    mid.y = (p1.y + p2.y) / 2;

    // If the midpoint is too close to the endpoints, highlight and stop recursion
    if (fabs(p1.x - p2.x) < 1 && fabs(p1.y - p2.y) < 1) {
        if (isInside(p1, xmin, ymin, xmax, ymax) && !isInside(p2, xmin, ymin, xmax, ymax)) {
            highlightPoint(p1);
        } else if (!isInside(p1, xmin, ymin, xmax, ymax) && isInside(p2, xmin, ymin, xmax, ymax)) {
            highlightPoint(p2);
        }
        return;
    }

    // Recursively check each half of the line segment
    midpointSubdivision(p1, mid, xmin, ymin, xmax, ymax);
    midpointSubdivision(mid, p2, xmin, ymin, xmax, ymax);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Define the clipping window coordinates
    double xmin = 100, ymin = 100, xmax = 400, ymax = 400;
    rectangle((int)xmin, (int)ymin, (int)xmax, (int)ymax);

    // Define the line endpoints
    Point A = {-4, 2};  // Given in the example
    Point B = {-1, 7};  // Given in the example

    // Scale points for better visualization within the graphics window
    A.x = 100 + (A.x + 3) * 50;
    A.y = 500 - (A.y - 1) * 50;
    B.x = 100 + (B.x + 3) * 50;
    B.y = 500 - (B.y - 1) * 50;

    // Perform midpoint subdivision line clipping
    midpointSubdivision(A, B, xmin, ymin, xmax, ymax);

    getch();
    closegraph();
    return 0;
}
