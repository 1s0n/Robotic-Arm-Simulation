#include "player.h"

Player::Player()
{
    movement_enabled = true;
    x = 200;
    y = 200;
    mRect.h = 50;
    mRect.w = 50;

    rotatedAngle = 0;

    toRotateTo = 0;

    mRect.x = 100;
    mRect.y = 100;


    xvel = 0;
    yvel = 0;

    upkeydown = 0;
    downkeydown = 0;
}

void Player::LoadTexture(const char* path, SDL_Renderer* renderer)
{
    mTexture.loadFromFile(path, renderer);
}

Player::~Player()
{
    delete &mTexture;
}

void Player::Draw(SDL_Renderer* renderer)
{
    mRect.x = renderedX;
    mRect.y = renderedY;
    SDL_SetRenderDrawColor(renderer, colour[0], colour[1], colour[2], colour[3]);
    // SDL_RenderFillRect(renderer, &rect);
    mTexture.getTexture();
    SDL_RenderCopyEx(renderer, mTexture.getTexture(), NULL, &mRect, rotatedAngle, NULL, SDL_FLIP_NONE);
}

void Player::SetPos(int to_x, int to_y)
{
    x = to_x;
    y = to_y;
}

void Player::MoveIP(int offset_x, int offset_y)
{
    x += offset_x;
    y += offset_y;
}

void Player::HandleInput(SDL_Event event)
{

    if (!movement_enabled)
        return;

    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_w:
                upkeydown = 1;
                yvel = -basevelocity;
                break;
            
            case SDLK_s:
                downkeydown = 1;
                yvel = basevelocity;
                break;

            case SDLK_a:
                leftkeydown = 1;
                xvel = -basevelocity;
                break;

            case SDLK_d:
                rightkeydown = 1;
                xvel = basevelocity;
                break;
            
            case SDLK_j:
                pCamera->MoveIP(10, 10);
        }
    }

    if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_w:
                upkeydown = 0;
                if (!downkeydown)
                    yvel = 0;
                break;

            case SDLK_s:
                downkeydown = 0;
                if (!upkeydown)
                    yvel = 0;
                break;

            case SDLK_a:
                leftkeydown = 0;
                if (!rightkeydown)
                    xvel = 0;
                break;

            case SDLK_d:
                rightkeydown = 0;
                if (!leftkeydown)
                    xvel = 0;
                break;
        }
    }

    if (event.type == SDL_MOUSEMOTION)
    {
        SDL_GetMouseState(&mouseX, &mouseY);
    }
}

void Player::Update()
{
    MoveIP(xvel, yvel);

    _rotateSelf();

    // std::cout << "Mouse X: " << mouseX << "    Mouse Y: " << mouseY << "\n";q

    
    pCamera->GetRelativePosition(x, y, &renderedX, &renderedY);

    /*
    int ang = GetRotationTowardsMouse(rotatedAngle, renderedX, renderedY, mouseX, mouseY);

    std::cout << rotatedAngle;

    setRotation(ang);
    */
}   

void Player::setRotation(double angle)
{
    rotatedAngle = angle;
}

void Player::_rotateSelf()
{
    // std::cout << yvel << "\n";

    // std::cout << rotatedAngle << "\n";

    // If the rotation is not done
    if (rotatedAngle != toRotateTo)
    {
        if (rotatedAngle == 0)
        {
            if (toRotateTo == 360)
            {
                toRotateTo = 0;
            }
        }

        // Find the closest way to rotate to the destination
        // For now, just rotate clockwise
        if (abs(toRotateTo - rotatedAngle) <= 180 || 1) // Always triggers because of the (... or 1)
        {
            if (abs(toRotateTo - rotatedAngle) < rotationSpeed)
            {
                rotatedAngle = toRotateTo;
            }

            rotatedAngle += rotationSpeed;
        }

        /*
        if (abs(toRotateTo - rotatedAngle) > 180)
        {
            
            std::cout << toRotateTo << "AAAA\n";

            if (abs(toRotateTo - rotatedAngle) < rotationSpeed)
            {
                rotatedAngle = toRotateTo;
            } 

            rotatedAngle -= rotationSpeed;
        }*/
    }

    if (rotatedAngle >= 360)
    {
        rotatedAngle = 360 - rotatedAngle;
    }
}

double Player::RotateTo(double angle)
{
    toRotateTo = angle;

    /*
    if (abs(toRotateTo - rotatedAngle) > 180)
    {
        rotatedAngle = 360.0 - rotatedAngle;
    }*/

    if (toRotateTo > 360)
    {
        LogError("[Player->RotateTo]", "toRotateTo is > 360!", WARNING);
    }

    return rotatedAngle;
}

double Player::GetRotationTowardsMouse(double currentRotation, int x, int y, int mouseX, int mouseY)
{
    std::cout << "[GetRotationTowardsMouse()] ";
    // Elevation
    if (y > mouseY)
    {
        std::cout << "Elevation!  ";
        
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
        std::cout << opposite << "   " << adjacent << "   " << ratio;
        double radians = atan(ratio);

        double radiansToAngles = 180.0 / M_PI;

        double angle = radiansToAngles * radians;

        std::cout << "  calc\n";

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
        std::cout << "Depression!";

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
        std::cout << opposite << "   " << adjacent << "   " << ratio;
        double radians = atan(ratio);

        double radiansToAngles = 180.0 / M_PI;

        double angle = radiansToAngles * radians;

        std::cout << "  calc\n";

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

    std::cout << "\n";

    return 0;
}

void Player::RenderDebugInfo(TTF_Font* font, SDL_Renderer* renderer)
{
    SDL_Color Black = {0, 0, 0};

    std::string txt1 = "X Pos: " + std::to_string(x);

    SDL_Surface* text_surf = TTF_RenderText_Solid(font, txt1.c_str(), Black);

    int width;
    int height;

    TTF_SizeText(font, txt1.c_str(), &width, &height);

    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, text_surf);
    
    SDL_Rect Message_rect; 
    Message_rect.x = 0;
    Message_rect.y = 0;
    Message_rect.w = width; 
    Message_rect.h = height;
    
    SDL_RenderCopy(renderer, text, NULL, &Message_rect);

    SDL_DestroyTexture(text);
	SDL_FreeSurface(text_surf);
}

void Player::LoadCamera(Camera* camera)
{
    pCamera = camera;
}

void Player::DisableInput()
{
    movement_enabled = false;
}