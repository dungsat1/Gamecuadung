#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include "constants.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Texture* gBackgroundTexture;
extern SDL_Texture* gHeadTexture;
extern SDL_Texture* gBodyTexture;
extern SDL_Texture* gTailTexture;
extern SDL_Texture* gCornerTexture;
extern SDL_Texture* gFoodTexture;
extern TTF_Font* gFont;
extern Mix_Chunk* gEatSound;
extern Mix_Chunk* gGameOverSound;

bool init();
SDL_Texture* loadTexture(const std::string& path);
void renderText(const std::string& text, int x, int y, Color color);
void FontGO(const std::string& text, int x, int y, Color color);
void close();

#endif
