#include <string>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <SDL2/SDL_image.h>

#include "player.h"
#include "line.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 1200

// This is using a game i made a long time ago

int main(int argv, char** args)
{
    std::cout << "[*] Initing SDL...\n";

    SDL_Init(SDL_INIT_EVERYTHING);

    IMG_Init(IMG_INIT_PNG);

    if (TTF_Init() == -1)
    {
        std::cout << "[Fatal] TTF_Init() Failed! Error: " << TTF_GetError() << "\n";
        return -1;
    } 

    SDL_Window *window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_HEIGHT, WINDOW_WIDTH, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;

    Player player;
    Player ArmOrigin;
    std::cout << "[*] Starting game loop...\n";

    player.LoadTexture("assets/Player.png", renderer);
    ArmOrigin.LoadTexture("assets/Origin.png", renderer);
    // player.RotateTo(360);

    Camera camera;

    TTF_Font* font = TTF_OpenFont("assets/font/JetBrainsMono-Light.ttf", 24);
    
    if (font == NULL)
    {
        std::cout << "[TFF_OpenFont()] Failed to open font!\n";
        SDL_Quit();

        TTF_CloseFont(font);
        TTF_Quit();
        return 0;
    }

    player.LoadCamera(&camera);
    ArmOrigin.LoadCamera(&camera);
    ArmOrigin.DisableInput();

    ArmOrigin.MoveIP(600, 0);

    int playerX;
    int playerY;

    int originX;
    int originY;
    
    player.GetPos(&playerX, &playerY);
    ArmOrigin.GetPos(&originX, &originY);

    Line line;
    line.SetThickness(20);
    line.LoadTexture("assets/BlackSquare.png", renderer);

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
                std::cout << "[*] QUITTING in loop!\n";
            }

            player.HandleInput(event);
        }   

        // To quit the game instantly preventing problems in the loop...
        if (running == false) break;


        // Update game
        player.Update();
        ArmOrigin.Update();

        player.GetPos(&playerX, &playerY);
        ArmOrigin.GetPos(&originX, &originY);

        

        // Draw game
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        player.Draw(renderer);
        ArmOrigin.Draw(renderer);
        line.Draw(playerX, playerY, originX, originY, renderer);


        player.RenderDebugInfo(font, renderer);

        SDL_RenderPresent(renderer);
    }


    std::cout << "[*] Destroying window and renderer...\n";

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    std::cout << "[*] Calling SDL_Quit()...\n";

    SDL_Quit();

    std::cout << "[*] Calling TFF_CloseFont()...\n";
    TTF_CloseFont(font);
    std::cout << "[*] Calling TTF_Quit()...\n";
    TTF_Quit();

    std::cout << "[*] Closing...\n";

    return 0;
}