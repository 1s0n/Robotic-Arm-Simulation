#include "ltexture.h"

LTexture::LTexture()
{

}

LTexture::~LTexture()
{
    SDL_DestroyTexture(mTexture);
}

void LTexture::free()
{

}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
    {
        LogError("Failed to load image", IMG_GetError(), ERROR);
        return false;
    }

    mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    if (mTexture == NULL)
    {
        LogError("Failed to load texture", SDL_GetError(), ERROR);
        return false;
    }

    SDL_FreeSurface(loadedSurface);

    return true;
}

void LTexture::setColour(int red, int green, int blue)
{

}

void LTexture::setBlendMode(SDL_BlendMode blending)
{

}

void LTexture::setAlpha(int alpha)
{

}

void LTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)
{
    SDL_Rect renderRect = {x, y, mWidth, mHeight};

    if (clip != NULL)
    {
        renderRect.w = clip->w;
        renderRect.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, mTexture, clip, &renderRect, angle, center, flip);
}   

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

SDL_Texture* LTexture::getTexture()
{
    return mTexture;
}