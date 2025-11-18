#pragma once
#include <SDL3/SDL.h>

/// @brief テクスチャのデータとサイズ、描画位置をまとめたもの
class SDLTextureData
{
    SDL_Texture* m_texture;
    SDL_FRect m_destRect;
    
    /// @brief テクスチャの優先度。数字が大きいほうが優先度が高い(最後に描画される)
    int m_priority;
    

public:
    
    /// @brief コンストラクタ
    /// @param texture 描画したいテクスチャ
    /// @param x テクスチャの中心のx座標
    /// @param y テクスチャの中心のy座標
    /// @param priority 
    SDLTextureData(
        SDL_Texture* texture,
        float x,
        float y,
        int priority
    );

    SDL_Texture* getTexture()const{return m_texture;}
    const SDL_FRect& getRect()const{return m_destRect;}
    
    bool operator<(const SDLTextureData&)const;
};