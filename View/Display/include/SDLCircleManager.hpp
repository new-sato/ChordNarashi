#pragma once
// テクスチャの管理、バッファの生成を行う
#include "SDLTextureData.hpp"

#include <map>

struct CircleInfo
{
    double r;
    int red;
    int green;
    int blue;
    int alpha;
    bool operator<(const CircleInfo& rh)const;
};

class SDLCircleManager
{
    std::map<CircleInfo, SDL_Texture*> textureCash;
    SDL_Renderer* m_renderer;

    int m_window_width;
    int m_window_hight;
public:
    SDLCircleManager(SDL_Renderer* renderer, int w, int h);
    ~SDLCircleManager();
    SDL_Texture* generateCircleTexture(CircleInfo);
};