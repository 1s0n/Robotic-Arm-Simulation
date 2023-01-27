#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "log.h"

class LTexture 
{
    public:
        LTexture();
        ~LTexture();

        bool loadFromFile(std::string path, SDL_Renderer* renderer);
        
        void free();

        void setColour(int red, int green, int blue);

        void setBlendMode(SDL_BlendMode blending);

        void setAlpha(int alpha);

        void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

        int getWidth();
        int getHeight();

        SDL_Texture* getTexture();

    private:

        SDL_Texture* mTexture = NULL;

        int mHeight = 50;
        int mWidth = 50;
};