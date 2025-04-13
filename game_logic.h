#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include "constants.h"

bool checkCollision(const SnakeSegment& head, const std::vector<SnakeSegment>& snake);

#endif
