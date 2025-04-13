#include "game_logic.h"
#include "constants.h"

bool checkCollision(const SnakeSegment& head, const std::vector<SnakeSegment>& snake) {
    // Wall collision
    if (head.x < 40 || head.x >= SCREEN_WIDTH - 40 || head.y < 80 || head.y >= SCREEN_HEIGHT - 40) {
        return true;
    }
    // Self collision
    for (size_t i = 1; i < snake.size(); ++i) {
        if (head.x == snake[i].x && head.y == snake[i].y) {
            return true;
        }
    }
    return false;
}
