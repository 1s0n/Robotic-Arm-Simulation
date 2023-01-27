#include <SDL2/SDL.h>
#include "joint.h"
#include "ltexture.h"

class Line
{
    public:
        Line();
        ~Line();

        void Draw(int p1x, int p1y, int p2x, int p2y, SDL_Renderer* renderer);
        void SetThickness(int thickness);
        void LoadTexture(const char* path, SDL_Renderer* renderer);
        
    private:
        int thickness;

        SDL_Rect mRect;

        double rotatedAngle;
        double toRotateTo;
        double rotationSpeed = 10; // 1 degree per frame

        LTexture mTexture;

        int colour[4] = {2, 53, 53, 255};

        int basevelocity = 1;
        int xvel;
        int yvel;
};