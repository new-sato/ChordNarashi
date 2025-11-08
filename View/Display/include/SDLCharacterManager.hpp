#pragma once
#include "IcharacterManager.hpp"
#include "SDLTextureData.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class SDLCharacterManager:public IcharacterManager
{
    std::vector<SDLTextureData> m_character_to_draw;
    SDL_Texture* test;
public:
    SDLCharacterManager()
    {
        TTF_Font* font = TTF_OpenFont("Amble-Regular.ttf",20);
        SDL_Color white={255,255,255,255};
    }
    
    std::vector<SDLTextureData> getCharacterToDraw()const
    {
        // TODO テスト
        SDLTextureData tes(test, 250, 250, 0);
        return std::vector<SDLTextureData>{tes};
    };
};