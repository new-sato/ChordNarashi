#pragma once
#include "Idisplay.hpp"
#include "SDLCharacterManager.hpp"
#include "SDLCircleManager.hpp"
#include <map>

struct TouchInfo {
    float x;
    float y;
};

class SDLManager:public Idisplay
{
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    int windowWidth = 500;
    int windowHight = 500;
    
    /// @brief ウィンドウがアクティブかどうか
    bool is_focused = true;
    bool m_quit_requested = false;

    SDL_Event event;
    std::vector<SDLTextureData> m_textures;

    SDLCharacterManager character_manager = NULL;
    SDLCircleManager m_circle_manager = {NULL, 0, 0};

    // バーチャルボタンの押下状態（5種類 × 12音）
    std::vector<std::vector<bool>> m_virtual_chord_buttons = std::vector<std::vector<bool>>(5, std::vector<bool>(12, false));
    bool m_mouse_down = false;
    float m_mouse_x = 0.0f;
    float m_mouse_y = 0.0f;
    
    std::map<SDL_FingerID, TouchInfo> m_touches;
    bool m_virtual_ring_pressed = false;
    bool m_virtual_sustain_pressed = false;

    int m_key = 0; // 現在のキー

    /// @brief レンダラーで描画したいテクスチャを、描画のための配列に追加する
    /// @param input 描画したいデータ
    void addTextureToDraw(const SDLTextureData& input);

    void processClickOrTouch(float x, float y, bool is_pressed);
    void evaluateInputStates();
    void drawVirtualButtons();
    void drawFilledCircle(float cx, float cy, float r, SDL_Color color);

    public:
    SDLManager();
    ~SDLManager();
    
    void pollEvents()override;
    void displayCharacter(const charaData&)override;
    
    /// @brief 長方形を描画する関数。呼び出した時点で効果を効果を発揮する
    /// @param 
    void displayRectangle(const Rectangle&)override;

    void displayCircle(const Circle&)override;
    
    /// @brief 現在のレンダラを描画する
    void updateDisplay()override;
    
    bool is_x_button_pressed()override;
    
    bool get_is_focused()const override{return is_focused;};
    
    bool isKeyPressed(int scancode) const override;
    const std::vector<std::vector<bool>>& getVirtualChordButtons() const override { return m_virtual_chord_buttons; }
    bool isVirtualRingButtonPressed() const override { return m_virtual_ring_pressed; }
    bool isVirtualSustainButtonPressed() const override { return m_virtual_sustain_pressed; }

    void setKey(int key) { m_key = key; }

    bool initialize();
    
};