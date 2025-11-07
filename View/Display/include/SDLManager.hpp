#pragma once
#include "Idisplay.hpp"
#include "SDL3/SDL.h"

class SDLManager:public Idisplay
{
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    int windowWidth = 500;
    int windowHight = 500;

    SDL_Event event;

    public:
    SDLManager();
    ~SDLManager();
    void updateDisplay()override;
    
    bool is_x_button_pressed()override;

    bool initialize();
    
};