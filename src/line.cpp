#include "line.h"

Line::Line()
{
    thickness = 1;
    mRect.h = 100;
    mRect.w = thickness;
    mRect.x = 0;
    mRect.y = 0;
}

Line::~Line()
{

}

void Line::Draw(int p1x, int p1y, int p2x, int p2y, SDL_Renderer* renderer)
{
    mRect.x = p1x;
    mRect.y = p1y;

    SDL_SetRenderDrawColor(renderer, colour[0], colour[1], colour[2], colour[3]);

    SDL_RenderCopyEx(renderer, mTexture.getTexture(), NULL, &mRect, rotatedAngle, NULL, SDL_FLIP_NONE);
}

void Line::SetThickness(int thickness)
{
    thickness = thickness;
    mRect.w = thickness;
}

void Line::LoadTexture(const char* path, SDL_Renderer* renderer)
{
    mTexture.loadFromFile(path, renderer);
}