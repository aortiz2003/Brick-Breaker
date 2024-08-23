// Angel Ortiz
// bounce.c
// AORTIZ22

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "gfx.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define CIRCLE_RADIUS 20
#define VELOCITY_RANGE 70

typedef struct {
    float x, y;
    float vx, vy;
} Circle;

void handleWallCollision(Circle *circle) {
    if (circle->x - CIRCLE_RADIUS < 0 || circle->x + CIRCLE_RADIUS > WINDOW_WIDTH) {
        circle->vx *= -1;
    }
    if (circle->y - CIRCLE_RADIUS < 0 || circle->y + CIRCLE_RADIUS > WINDOW_HEIGHT) {
        circle->vy *= -1;
    }
}

int main() {
    float dt = 0.1;

    gfx_open(WINDOW_WIDTH, WINDOW_HEIGHT, "Bouncing Circle");

    Circle circle = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 2, 3};

    srand(time(NULL));

    while (1) {
        if (gfx_event_waiting()) {
            char c = gfx_wait();
            if (c == 'q') {
                break; 
            }
            if (c == 1) {
                circle.x = gfx_xpos();
                circle.y = gfx_ypos();
                circle.vx = rand() % (2 * VELOCITY_RANGE) - VELOCITY_RANGE;
                circle.vy = rand() % (2 * VELOCITY_RANGE) - VELOCITY_RANGE;
            }
        }

        circle.x += circle.vx * dt;
        circle.y += circle.vy * dt;

        handleWallCollision(&circle);

        gfx_clear();

        gfx_color(255, 255, 255);
        gfx_circle(circle.x, circle.y, CIRCLE_RADIUS);

        gfx_flush();
        usleep(10000);
    }

    return 0;
}
