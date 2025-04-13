#include "sdl_utils.h"
#include <iostream>

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* gBackgroundTexture = nullptr;
SDL_Texture* gHeadTexture = nullptr;
SDL_Texture* gBodyTexture = nullptr;
SDL_Texture* gTailTexture = nullptr;
SDL_Texture* gCornerTexture = nullptr;
SDL_Texture* gFoodTexture = nullptr;
TTF_Font* gFont = nullptr;
TTF_Font* gFontGO = nullptr;
Mix_Chunk* gEatSound = nullptr;
Mix_Chunk* gGameOverSound = nullptr;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image initialization failed: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("Snake Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!gWindow) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    gFont = TTF_OpenFont("arial.ttf", 24);
    gFontGO = TTF_OpenFont("Showg.ttf", 80);
    if (!gFont) {
        std::cerr << "Font loading failed: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

SDL_Texture* loadTexture(const std::string& path) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        std::cerr << "Unable to load image " << path << ": " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return texture;
}

void renderText(const std::string& text, int x, int y, Color color) {
    SDL_Color textColor = {color.r, color.g, color.b, color.a};
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(gRenderer, textTexture, nullptr, &renderQuad);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void FontGO(const std::string& text, int x, int y, Color color) {
    SDL_Color textColor = {color.r, color.g, color.b, color.a};
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFontGO, text.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(gRenderer, textTexture, nullptr, &renderQuad);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void close() {
    SDL_DestroyTexture(gBackgroundTexture);
    SDL_DestroyTexture(gHeadTexture);
    SDL_DestroyTexture(gBodyTexture);
    SDL_DestroyTexture(gTailTexture);
    SDL_DestroyTexture(gCornerTexture);
    SDL_DestroyTexture(gFoodTexture);

    Mix_FreeChunk(gEatSound);
    Mix_FreeChunk(gGameOverSound);

    TTF_CloseFont(gFont);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
