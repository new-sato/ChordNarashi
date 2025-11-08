#pragma once
#include "IcharacterManager.hpp"
#include "SDLTextureData.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <map>

/// @brief テクスチャの生成とキャッシュを行う。
class SDLCharacterManager:public IcharacterManager
{
    std::map<std::string, SDL_Texture*> cash;
    SDL_Renderer* m_renderer;
public:
    SDLCharacterManager(SDL_Renderer* renderer);
    SDL_Texture* generateCharaTexture(std::string text, int font_size);
};