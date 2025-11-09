#include "SDLManager.hpp"
#include "cmath"
#include <string>
#include <algorithm>


SDLManager::SDLManager()
{
    if(!initialize())
    {
        exit(1);
    }
    character_manager = SDLCharacterManager(mRenderer);
}

void SDLManager::addTextureToDraw(const SDLTextureData &input)
{
    m_textures.push_back(input);
}

bool SDLManager::initialize()
{
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDLを初期化できません");
        return false;
    }
    
    if(!TTF_Init())
    {
        SDL_Log("TTF_Init Error");
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

void SDLManager::displayCharacter(const charaData& input)
{
    SDL_Texture* t = character_manager.generateCharaTexture(input.str, input.font_size);
    int x = input.x*(windowWidth/2) + windowWidth/2;
    int y = input.y*(windowHight/2) + windowHight/2;
    SDLTextureData d(t, x, y, 0);
    addTextureToDraw(d);
}

void SDLManager::updateDisplay()
{
    SDL_SetRenderDrawColor(
        mRenderer,
        20,
        20,
        20,
        255
    );

    // 塗りつぶし
    SDL_RenderClear(mRenderer);

    std::sort(m_textures.begin(), m_textures.end());
    for(SDLTextureData s: m_textures)
    {
        SDL_RenderTexture(mRenderer, s.getTexture(), NULL, &s.getRect());
    }
    
    SDL_RenderPresent(mRenderer);

}

bool SDLManager::is_x_button_pressed()
{
    SDL_PollEvent(&event);

    if(event.type == SDL_EVENT_QUIT) return true;
    else return false;
}
