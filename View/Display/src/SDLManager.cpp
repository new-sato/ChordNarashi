#include "SDLManager.hpp"
#include "cmath"
#include <string>

SDLManager::SDLManager()
{
    if(!initialize())
    {
        exit(1);
    }
}

bool SDLManager::initialize()
{
    
    int sdlResult= SDL_Init(SDL_INIT_VIDEO);
    if(sdlResult < 0)
    
    {
        SDL_Log("SDLを初期化できません");
        return false;
    }
    mWindow = SDL_CreateWindow(
        "TEST",
        windowWidth,
        windowHight,
        SDL_WINDOW_RESIZABLE
    );

    if(!mWindow)
    {
        SDL_Log("ウィンドウの作成に失敗しました");
        return false;
    }
    
    mRenderer = SDL_CreateRenderer(
        mWindow,
        nullptr
    );

    updateDisplay();

    return true;
}

SDLManager::~SDLManager()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

/// @brief 表示までを行う
void SDLManager::updateDisplay()
{
    SDL_SetRenderDrawColor(
        mRenderer,
        20,
        20,
        20,
        255
    );

    SDL_RenderClear(mRenderer);

    SDL_RenderPresent(mRenderer);

}

bool SDLManager::is_x_button_pressed()
{
    SDL_PollEvent(&event);

    if(event.type == SDL_EVENT_QUIT) return true;
    else return false;
}
