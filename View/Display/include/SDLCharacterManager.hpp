#pragma once
#include "SDLTextureData.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <map>

struct CashIndex
{
    int size;
    std::string str;
    bool operator<(const CashIndex& rh);
    CashIndex(int size_arg, std::string str_arg):size(size_arg), str(str_arg){}
};

/// @brief テクスチャの生成とキャッシュを行う。
class SDLCharacterManager
{
    SDL_Color chara_color = SDL_Color({255,255,255,255});
    std::map<CashIndex, SDL_Texture*> textureCash;
    SDL_Renderer* m_renderer;
    std::map<int, TTF_Font*> fonts;
    
    const std::string font_name = "Amble-Regular.ttf";

public:
    SDLCharacterManager(SDL_Renderer* renderer);
    ~SDLCharacterManager();
    SDL_Texture* generateCharaTexture(std::string text, int font_size);
};