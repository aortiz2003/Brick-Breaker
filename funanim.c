//Angel Ortiz
//funanim.c
//AORTIZ22

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "gfx.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct {
    float x, y;
    float radius;
    float angle;
} Shape;

void drawCircle(float x, float y, float radius, int red, int green, int blue) {
    gfx_color(red, green, blue);
    for (float theta = 0; theta < 2 * M_PI; theta += 0.01) {
        float xPos = x + radius * cos(theta);
        float yPos = y + radius * sin(theta);
        gfx_point((int)xPos, (int)yPos);
    }
}

void drawSquare(float x, float y, float size, int red, int green, int blue) {
    gfx_color(red, green, blue);
    float halfSize = size / 2;
    gfx_line(x - halfSize, y - halfSize, x + halfSize, y - halfSize);
    gfx_line(x + halfSize, y - halfSize, x + halfSize, y + halfSize);
    gfx_line(x + halfSize, y + halfSize, x - halfSize, y + halfSize);
    gfx_line(x - halfSize, y + halfSize, x - halfSize, y - halfSize);
}

int main() {
    gfx_open(WINDOW_WIDTH, WINDOW_HEIGHT, "Fun Animation");

    Shape circle = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 100, 0};
    Shape square = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 80, 0};

    int circleRed = 255, circleGreen = 0, circleBlue = 0;
    int squareRed = 0, squareGreen = 0, squareBlue = 255;

    while (1) {
        gfx_clear();

        float circleX = circle.x + 200 * cos(circle.angle);
        float circleY = circle.y + 100 * sin(circle.angle);
        drawCircle(circleX, circleY, circle.radius, circleRed, circleGreen, circleBlue);
        circle.angle += 0.03;

        float squareX = square.x + 150 * cos(square.angle);
        float squareY = square.y + 80 * sin(square.angle);
        drawSquare(squareX, squareY, square.radius, squareRed, squareGreen, squareBlue);
        square.angle -= 0.02;

        
        if (gfx_event_waiting()) {
            char c = gfx_wait();
            if (c == 'q') break;
            if (c == 'r') {
                circleRed = rand() % 256;
                circleGreen = rand() % 256;
                circleBlue = rand() % 256;
            }
            if (c == 's') {
                squareRed = rand() % 256;
                squareGreen = rand() % 256;
                squareBlue = rand() % 256;
            }
        }

        gfx_flush();
        usleep(10000);
    }

    return 0;
}
