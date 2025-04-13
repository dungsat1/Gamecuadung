#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL.h>

// Constants
const int SCREEN_WIDTH = 760;
const int SCREEN_HEIGHT = 720;
const int GRID_SIZE = 40;
const int GRID_WIDTH = (SCREEN_WIDTH - 40 * 2) / GRID_SIZE; // 17 columns
const int GRID_HEIGHT = (SCREEN_HEIGHT - 40 - 80) / GRID_SIZE; // 15 rows
const int SPEED = 80;

// Colors
struct Color {
    Uint8 r, g, b, a;
};
const Color RED = {255, 0, 0, 255};
const Color GREEN = {0, 255, 0, 255};
const Color WHITE = {255, 255, 255, 255};

// Movement direction
enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

// Snake segment
struct SnakeSegment {
    int x, y;
};

#endif
