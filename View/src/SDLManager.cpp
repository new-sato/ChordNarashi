#include "SDLManager.hpp"
#include "cmath"
#include <string>

namespace 
{
    std::vector<std::string> buttonNameArray
    {
        "C",
        "G",
        "D",
        "A",
        "E",
        "B",
        "Fs",
        "Df",
        "Af",
        "Ef",
        "Bf",
        "F"
    };
}

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
    if(sdlResult != 0)
    {
        SDL_Log("SDLを初期化できません");
        return false;
    }
    
    TTF_Init();
    
    mWindow = SDL_CreateWindow(
        "TEST",
        100,
        100,
        windowWidth,
        windowHight,
        0
    );

    if(!mWindow)
    {
        SDL_Log("ウィンドウの作成に失敗しました");
        return false;
    }
    
    mRenderer = SDL_CreateRenderer(
        mWindow,
        -1,
        SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
    );

    TTF_Init();
    fontL = TTF_OpenFont("Amble-Regular.ttf", 36);
    fontM = TTF_OpenFont("Amble-Regular.ttf", 24);
    fontS = TTF_OpenFont("Amble-Regular.ttf", 18);
    if(fontL == nullptr)
    {
        SDL_Log("fonto yomikome nakatta");
        return false;
    }

    for(std::string s:buttonNameArray)
    {
        SDL_Surface* surf = TTF_RenderText_Blended(fontL,s.c_str(), charaColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surf);
        texturesL.push_back(texture);

        surf = TTF_RenderText_Blended(fontM,s.c_str(), charaColor);
        texture = SDL_CreateTextureFromSurface(mRenderer, surf);
        texturesM.push_back(texture);
    }
    
    updateView();

    return true;
}

SDLManager::~SDLManager()
{
    TTF_CloseFont(fontL);
    TTF_CloseFont(fontM);
    TTF_CloseFont(fontS);
    TTF_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}


/// @brief 画面の中央に五度円をレンダラーに描画する
void SDLManager::displayCircle()
{
    int texWidth, texHeight;
    
    int R = 0.4 * ((windowHight<windowWidth)?windowHight:windowWidth);
    int offset = (doOfset)?-key:0;

    
    SDL_QueryTexture(texturesL[key], nullptr, nullptr, &texWidth, &texHeight);
    SDL_Rect r;
    r.w = texWidth;
    r.h = texHeight;
    r.x = windowWidth/2 - texWidth/2;
    r.y = windowHight/2 - texHeight/2;
    SDL_RenderCopy(mRenderer, texturesL[key], nullptr, &r);

    for(int i=0;i<12;i++)
    {
        SDL_QueryTexture(texturesL[i], nullptr, nullptr, &texWidth, &texHeight);

        SDL_Rect r;
        r.w = texWidth;
        r.h = texHeight;
        r.x = R*sin(M_PI*(i+offset)/6)+windowWidth/2 - texWidth/2;
        r.y = -R*cos(M_PI*(i+offset)/6)+windowHight/2 - texHeight/2;
        SDL_RenderCopy(mRenderer, texturesL[i], nullptr, &r);
    }
    
    int Rm = 0.3 * ((windowHight<windowWidth)?windowHight:windowWidth);
    for(int i=0;i<12;i++)
    {
        SDL_QueryTexture(texturesL[i], nullptr, nullptr, &texWidth, &texHeight);

        SDL_Rect r;
        r.w = texWidth;
        r.h = texHeight;
        r.x = Rm*sin(M_PI*(i+offset-3)/6)+windowWidth/2 - texWidth/2;
        r.y = -Rm*cos(M_PI*(i+offset-3)/6)+windowHight/2 - texHeight/2 ;
        SDL_RenderCopy(mRenderer, texturesL[i], nullptr, &r);
    }
    int Rdim = 0.2 * ((windowHight<windowWidth)?windowHight:windowWidth);
    for(int i=0;i<12;i++)
    {
        SDL_QueryTexture(texturesM[i], nullptr, nullptr, &texWidth, &texHeight);

        SDL_Rect r;
        r.w = texWidth;
        r.h = texHeight;
        r.x = Rdim*sin(M_PI*(i+offset-5)/6)+windowWidth/2 - texWidth/2;
        r.y = -Rdim*cos(M_PI*(i+offset-5)/6)+windowHight/2 - texHeight/2;
        SDL_RenderCopy(mRenderer, texturesM[i], nullptr, &r);
    }

}

/// @brief 表示までを行う
void SDLManager::updateView()
{
    SDL_SetRenderDrawColor(
        mRenderer,
        20,
        20,
        20,
        255
    );

    SDL_RenderClear(mRenderer);
    
    displayCircle();

    SDL_RenderPresent(mRenderer);

}

