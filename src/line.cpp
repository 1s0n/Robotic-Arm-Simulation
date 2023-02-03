#include "line.h"

Line::Line()
{
    thickness = 1;
    mRect.h = 200;
    mRect.w = thickness;
    mRect.x = 0;
    mRect.y = 0;

    mouseX = 0;
    mouseY = 0;
}

Line::~Line()
{

}

void Line::Update()
{
    
}

void Line::flipRotation()
{
    rotatedAngle = rotatedAngle - 180;
}

void Line::Draw(int p1x, int p1y, int p2x, int p2y, SDL_Renderer* renderer)
{
    int ang = GetRotationTowardsMouse(rotatedAngle, mRect.x, mRect.y, p2x + 25, p2y + 25);

    setRotation(ang);

    std::cout << "[Line::Draw()] " << rotatedAngle;

    flipRotation();

    std::cout << "   " << rotatedAngle << "\n";

    // HARDCODED VALUE 25 = half of player size (50x50)
    mRect.x = p1x + 25; 
    mRect.y = p1y + 25;
    
    // TODO: CHANGE THIS

    SDL_Point center;
    center.x = mRect.w / 2;
    // Change the real x position to make up for the change because of changing center point
    mRect.x -= mRect.w / 2;
    
    center.y = 0;


    SDL_SetRenderDrawColor(renderer, colour[0], colour[1], colour[2], colour[3]);

    SDL_RenderCopyEx(renderer, mTexture.getTexture(), NULL, &mRect, rotatedAngle, &center, SDL_FLIP_NONE);
}

void Line::SetThickness(int thickness)
{
    thickness = thickness;
    mRect.w = thickness;
}

void Line::setRotation(double angle)
{
    rotatedAngle = angle;
}

double Line::GetRotationTowardsMouse(double currentRotation, int x, int y, int mouseX, int mouseY)
{
    // std::cout << "[GetRotationTowardsMouse()] ";
    // Elevation
    if (y > mouseY)
    {
        // std::cout << "Elevation!  ";
        
        int opposite = 0; 
        int adjacent = 0;

        // Looking left
        if (x > mouseX)
        {
            // Do trigonometry
            opposite = y - mouseY;
            adjacent = x - mouseX;
        }

        // Looking right
        if (x <= mouseX)
        {
            // Do trigonometry
            opposite = mouseY - y;
            adjacent = mouseX - x;
        }

        double ratio = (double)opposite/(double)adjacent;
        // std::cout << opposite << "   " << adjacent << "   " << ratio;
        double radians = atan(ratio);

        double radiansToAngles = 180.0 / M_PI;

        double angle = radiansToAngles * radians;

        // std::cout << "  calc\n";

        if (x > mouseX)
        {
            angle = 270 + angle;
        }

        if (x <= mouseX)
        {
            angle += 90;
        }

        return angle;
    }

    // Depression
    if (y <= mouseY)
    {
        // std::cout << "Depression!";

        int opposite = 0; 
        int adjacent = 0;

        // Looking left
        if (x > mouseX)
        {
            // Do trigonometry
            opposite = y - mouseY;
            adjacent = x - mouseX;
        }

        // Looking right
        if (x <= mouseX)
        {
            // Do trigonometry
            opposite = mouseY - y;
            adjacent = mouseX - x;
        }

        double ratio = (double)opposite/(double)adjacent;
        // std::cout << opposite << "   " << adjacent << "   " << ratio;
        double radians = atan(ratio);

        double radiansToAngles = 180.0 / M_PI;

        double angle = radiansToAngles * radians;

        // std::cout << "  calc\n";

        if (x > mouseX)
        {
            angle = 270 + angle;
        }

        if (x <= mouseX)
        {
            angle += 90;
        }

        return angle;
    }

    // std::cout << "\n";

    return 0;
}

void Line::LoadTexture(const char* path, SDL_Renderer* renderer)
{
    mTexture.loadFromFile(path, renderer);
}

void Line::HandleInput(SDL_Event event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        SDL_GetMouseState(&mouseX, &mouseY);
    }
}