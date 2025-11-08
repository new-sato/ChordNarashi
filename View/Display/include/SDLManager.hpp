#pragma once
#include "Idisplay.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <queue>

/// @brief テクスチャのデータとサイズ、描画位置をまとめたもの
class SDLTextureData
{
    std::unique_ptr<SDL_Texture> m_texture;
    SDL_FRect m_destRect;
    int m_priority;

    bool operator<(const SDLTextureData&);

public:
    SDLTextureData(
        std::unique_ptr<SDL_Texture> texture,
        float x,
        float y,
        int priority
    );
};

class SDLManager:public Idisplay
{
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    int windowWidth = 500;
    int windowHight = 500;

    SDL_Event event;
    
    std::priority_queue<SDLTextureData,std::vector<SDLTextureData>> hoge;

    public:
    SDLManager();
    ~SDLManager();
    
    // TODO テクスチャの管理をどうするか決める

    /// @brief 現在のレンダラを描画する
    void updateDisplay()override;
    
    bool is_x_button_pressed()override;

    bool initialize();
    
};