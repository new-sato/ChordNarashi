#pragma once
#include "Idisplay.hpp"
#include "SDLCharacterManager.hpp"
#include <memory>
#include <vector>


class SDLManager:public Idisplay
{
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    int windowWidth = 500;
    int windowHight = 500;

    SDL_Event event;
    std::vector<SDLTextureData> m_textures;

    SDLCharacterManager character_manager = NULL;

    /// @brief レンダラーで描画したいテクスチャを、描画のための配列に追加する
    /// @param input 描画したいデータ
    void addTextureToDraw(const SDLTextureData& input);

    public:
    SDLManager();
    ~SDLManager();
    
    void displayCharacter(const charaData&)override;
    
    /// @brief 現在のレンダラを描画する
    void updateDisplay()override;
    
    bool is_x_button_pressed()override;
    

    bool initialize();
    
};