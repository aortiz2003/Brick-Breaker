// Angel Ortiz
// symbl.c
// Aortiz22

#include <stdio.h>
#include <math.h>
#include "gfx.h"

#define SIZE 50

void drawSquare(int x, int y, int size);
void drawCircle(int x, int y, int diameter);
void drawTriangle(int x, int y, int size);
void drawPolygon(int x, int y, int sides, int diameter);

int main() {
    int x, y;

    gfx_open(800, 600, "Symbol Program");
    
    while (1) {
        if (gfx_event_waiting()) {
            int event = gfx_wait();

            if (event == 1) {
                x = gfx_xpos();
                y = gfx_ypos();
                gfx_color(0, 0, 255);
                drawSquare(x, y, SIZE);
            } else {
                char key = event;

                if (key == 'c') {
                    gfx_color(255, 255, 255);
                    drawCircle(gfx_xpos(), gfx_ypos(), SIZE);
                } else if (key == 't') {
                    gfx_color(0, 255, 0);
                    drawTriangle(gfx_xpos(), gfx_ypos(), SIZE);
                } else if (key >= '3' && key <= '9') {
                    gfx_color(128, 0, 128);
                    drawPolygon(gfx_xpos(), gfx_ypos(), key - '0', SIZE);
                } else if (key == 27) {
                    gfx_clear();
                } else if (key == 'q') {
                    break;
                }
            }
        }
    }

    return 0;
}

void drawSquare(int x, int y, int size) {
    int halfSize = size / 2;
    gfx_line(x - halfSize, y - halfSize, x + halfSize, y - halfSize);
    gfx_line(x + halfSize, y - halfSize, x + halfSize, y + halfSize);
    gfx_line(x + halfSize, y + halfSize, x - halfSize, y + halfSize);
    gfx_line(x - halfSize, y + halfSize, x - halfSize, y - halfSize);
}

void drawCircle(int x, int y, int diameter) {
    int radius = diameter / 2;
    int centerX = x;
    int centerY = y;
    int xValue = radius;
    int yValue = 0;
    int error = 0;

    while (xValue >= yValue) {
        gfx_point(centerX + xValue, centerY + yValue);
        gfx_point(centerX + yValue, centerY + xValue);
        gfx_point(centerX - yValue, centerY + xValue);
        gfx_point(centerX - xValue, centerY + yValue);
        gfx_point(centerX - xValue, centerY - yValue);
        gfx_point(centerX - yValue, centerY - xValue);
        gfx_point(centerX + yValue, centerY - xValue);
        gfx_point(centerX + xValue, centerY - yValue);

        yValue += 1;
        error += 1 + 2 * yValue;

        if (2 * (error - xValue) + 1 > 0) {
            xValue -= 1;
            error += 1 - 2 * xValue;
        }
    }
}

void drawTriangle(int x, int y, int size) {
    int halfSize = size / 2;
    gfx_line(x, y - halfSize, x + halfSize, y + halfSize);
    gfx_line(x + halfSize, y + halfSize, x - halfSize, y + halfSize);
    gfx_line(x - halfSize, y + halfSize, x, y - halfSize);
}

void drawPolygon(int x, int y, int sides, int diameter) {
    int radius = diameter / 2;
    int centerX = x;
    int centerY = y;
    double angle = 3.14159 * 2 / sides;

    for (int i = 0; i < sides; i++) {
        int x1 = centerX + radius * cos(i * angle);
        int y1 = centerY + radius * sin(i * angle);
        int x2 = centerX + radius * cos((i + 1) * angle);
        int y2 = centerY + radius * sin((i + 1) * angle);
        gfx_line(x1, y1, x2, y2);
    }
}
