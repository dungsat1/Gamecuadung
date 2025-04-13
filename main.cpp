#include <iostream>
#include <vector>
#include <ctime>
#include "sdl_utils.h"
#include "game_logic.h"
#include "constants.h"

int main(int argc, char* args[]) {
    if (!init()) {
        std::cerr << "Initialization failed!" << std::endl;
        return 1;
    }

    // textures
    gBackgroundTexture = loadTexture("background.png");
    gHeadTexture = loadTexture("head.png");
    gBodyTexture = loadTexture("body.png");
    gTailTexture = loadTexture("tail.png");
    gCornerTexture = loadTexture("corner.png");
    gFoodTexture = loadTexture("apple.png");
    if (!gBackgroundTexture || !gHeadTexture || !gBodyTexture || !gTailTexture) {
        std::cerr << "Failed to load textures!" << std::endl;
        close();
        return 1;
    }

    // sound
    gEatSound = Mix_LoadWAV("eat.mp3");
    gGameOverSound = Mix_LoadWAV("gameover.mp3");
    if (!gEatSound || !gGameOverSound) {
        std::cerr << "Failed to load sound effects!" << std::endl;
        close();
        return 1;
    }

    bool quit = false;
    bool gameOver = false;
    bool gameStarted = false;
    int score = 0;
    SDL_Event e;

    // snake size with 3 grid_size
    std::vector<SnakeSegment> snake = {
        {GRID_SIZE * 6 + 40, GRID_SIZE * 7 + 80},  // Head at (6,7)
        {GRID_SIZE * 5 + 40, GRID_SIZE * 7 + 80},  // Body
        {GRID_SIZE * 4 + 40, GRID_SIZE * 7 + 80}   // Tail
    };

    Direction direction = Direction::RIGHT;
    std::vector<Direction> snakeDirections(snake.size(), Direction::RIGHT);

    // Initialize food
    srand(time(0));
    SnakeSegment food;
    bool foodValid;
    do {
        foodValid = true;
        food = {
            (rand() % GRID_WIDTH) * GRID_SIZE + 40,
            (rand() % GRID_HEIGHT) * GRID_SIZE + 80
        };

        for (const auto& segment : snake) {
            if (food.x == segment.x && food.y == segment.y) {
                foodValid = false;
                break;
            }
        }
    }
    while (!foodValid);

    // game loop
    while (!quit) {
        // event
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                if (!gameStarted && e.key.keysym.sym == SDLK_RETURN) {
                    gameStarted = true;
                } else if (gameOver && e.key.keysym.sym == SDLK_r) {
                    // Reset game
                    gameOver = false;
                    score = 0;
                    snake = {
                        {GRID_SIZE * 6, GRID_SIZE * 7},
                        {GRID_SIZE * 5, GRID_SIZE * 7},
                        {GRID_SIZE * 4, GRID_SIZE * 7}
                    };
                    direction = Direction::RIGHT;
                    snakeDirections = std::vector<Direction>(snake.size(), Direction::RIGHT);

                    // rand food
                    do {
                        foodValid = true;
                        food = {
                            (rand() % GRID_WIDTH) * GRID_SIZE + 40,
                            (rand() % GRID_HEIGHT) * GRID_SIZE + 80
                        };

                        for (const auto& segment : snake) {
                            if (food.x == segment.x && food.y == segment.y) {
                                foodValid = false;
                                break;
                            }
                        }
                    } while (!foodValid);
                } else if (gameStarted && !gameOver) {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP: if (direction != Direction::DOWN) direction = Direction::UP; break;
                        case SDLK_DOWN: if (direction != Direction::UP) direction = Direction::DOWN; break;
                        case SDLK_LEFT: if (direction != Direction::RIGHT) direction = Direction::LEFT; break;
                        case SDLK_RIGHT: if (direction != Direction::LEFT) direction = Direction::RIGHT; break;
                    }
                }
            }
        }

        // start/game over screen
        if (!gameStarted || gameOver) {
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
            SDL_RenderClear(gRenderer);

            if (!gameStarted) {
                renderText("PRESS ENTER TO START", SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2, WHITE);
            } else {
                FontGO("GAME OVER", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2 - 50, RED);
                renderText("SCORE: " + std::to_string(score), SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 + 40, WHITE);
                renderText("PRESS R TO RESTART", SCREEN_WIDTH/2 - 120, SCREEN_HEIGHT/2 + 80, WHITE);
            }

            SDL_RenderPresent(gRenderer);
            continue;
        }

        // game logic
        SnakeSegment newHead = snake.front();
        switch (direction) {
            case Direction::UP: newHead.y -= GRID_SIZE; break;
            case Direction::DOWN: newHead.y += GRID_SIZE; break;
            case Direction::LEFT: newHead.x -= GRID_SIZE; break;
            case Direction::RIGHT: newHead.x += GRID_SIZE; break;
        }

        // Check collisions
        if (checkCollision(newHead, snake)) {
            Mix_PlayChannel(-1, gGameOverSound, 0);
            gameOver = true;
            continue;
        }

        // Handle food
        if (newHead.x == food.x && newHead.y == food.y) {
            snake.insert(snake.begin(), food);
            score += 10;
            Mix_PlayChannel(-1, gEatSound, 0);

            // new food
            do {
                foodValid = true;
                food = {
                    (rand() % GRID_WIDTH) * GRID_SIZE + 40,
                    (rand() % GRID_HEIGHT) * GRID_SIZE + 80
                };

                for (const auto& segment : snake) {
                    if (food.x == segment.x && food.y == segment.y) {
                        foodValid = false;
                        break;
                    }
                }
            } while (!foodValid);
        } else {
            snake.insert(snake.begin(), newHead);
            snake.pop_back();
        }

        // Update directions
        snakeDirections.insert(snakeDirections.begin(), direction);
        snakeDirections.pop_back();

        // Render
        SDL_RenderClear(gRenderer);

        // draw background
        SDL_RenderCopy(gRenderer, gBackgroundTexture, nullptr, nullptr);

        // draw food
        SDL_Rect foodRect = {food.x, food.y, GRID_SIZE, GRID_SIZE};
        SDL_RenderCopy(gRenderer, gFoodTexture, nullptr, &foodRect);

        // draw snake
        for (size_t i = 0; i < snake.size(); ++i) {
            SDL_Rect segmentRect = {snake[i].x, snake[i].y, GRID_SIZE, GRID_SIZE};
            double angle = 0;
            SDL_RendererFlip flip = SDL_FLIP_NONE;
            SDL_Texture* currentTexture = gBodyTexture;

            if (i == 0) { // Head
                currentTexture = gHeadTexture;
                switch (direction) {
                    case Direction::UP: angle = 270; break;
                    case Direction::DOWN: angle = 90; break;
                    case Direction::LEFT: angle = 180; break;
                    case Direction::RIGHT: angle = 0; break;
                }
            }
            else if (i == snake.size() - 1) { // Tail
                currentTexture = gTailTexture;
                if (i > 0) {
                    SnakeSegment prevSegment = snake[i - 1];
                    if (prevSegment.y < snake[i].y) angle = 270;    // Up
                    else if (prevSegment.x > snake[i].x) angle = 0; // Right
                    else if (prevSegment.y > snake[i].y) angle = 90; // Down
                    else if (prevSegment.x < snake[i].x) angle = 180; // Left
                }
            }
            else { // Body segments
                // xac dinh huong cua segment hien tai và segment tiep theo
                SnakeSegment prevSegment = snake[i - 1];
                SnakeSegment nextSegment = snake[i + 1];

                bool isVertical = (prevSegment.x == nextSegment.x);
                bool isHorizontal = (prevSegment.y == nextSegment.y);

                if (isVertical) {
                    // Segment thang dung
                    angle = 90;
                    currentTexture = gBodyTexture;
                }
                else if (isHorizontal) {
                    // Segment nam ngang
                    angle = 0;
                    currentTexture = gBodyTexture;
                }
                else {
                    // Segment o góc (khúc cua)
                    currentTexture = gCornerTexture; // texture goc

                    if ((prevSegment.x < snake[i].x && nextSegment.y > snake[i].y) || (nextSegment.x < snake[i].x && prevSegment.y > snake[i].y)) {
                        angle = 180;
                    }
                    else if ((prevSegment.x > snake[i].x && nextSegment.y > snake[i].y) || (nextSegment.x > snake[i].x && prevSegment.y > snake[i].y)) {
                        angle = 90;
                    }
                    else if ((prevSegment.x > snake[i].x && nextSegment.y < snake[i].y) || (nextSegment.x > snake[i].x && prevSegment.y < snake[i].y)) {
                        // goc phan tu thu nhat
                        angle = 0;
                    }
                    else if ((prevSegment.x < snake[i].x && nextSegment.y < snake[i].y) || (nextSegment.x < snake[i].x && prevSegment.y < snake[i].y)) {
                        angle = 270;
                    }
                }
            }

            SDL_RenderCopyEx(gRenderer, currentTexture, nullptr, &segmentRect, angle, nullptr, flip);
        }
        // draw score
        renderText("Your Score: " + std::to_string(score), 10, 10, WHITE);

        SDL_RenderPresent(gRenderer);
        SDL_Delay(200-SPEED);
    }

    close();
    return 0;
}
