#pragma once
#include "Iui.hpp"
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include "enumNote.hpp"
#include <map>
#include <vector>

class SDLManager:public iUi
{
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    TTF_Font* fontL;
    TTF_Font* fontM;
    TTF_Font* fontS;

    
    std::vector<SDL_Texture*> texturesL;
    std::vector<SDL_Texture*> texturesM;
    
    //HACK 実際には使われてない。
    Note nowKey = Note::C;

    // 表示するときに五度円を回転させるかどうか
    bool doOfset = true;
    int key = 0;
    void displayCircle();
    
    SDL_Color charaColor{.r =255, .g = 255, .b = 255, .a = 255};

    int windowWidth = 500;
    int windowHight = 500;

    public:
    SDLManager();
    ~SDLManager();
    void updateView();

    /// @brief GUIの制御側にキーの変更を反映させるためのもの。
    /// HACK キーはallClassManagerとかでまとめて管理したほうが良くないか？
    /// @param keyDiff キーを五度円でどれだけ回転させるか
    void updateKey(int keyDiff)override{key=(key+keyDiff)%12;}

    /// @brief 未実装。キーの変更ではない一時的な回転をGUIに反映させるためのもの
    /// @param rotateNum 5度円でどれだけ回転させるか
    void updateRotateState(int rotateNum)override{return;}
    
    /// @brief 表示する五度円を回転させるかどうかを切り替える
    void toggleDoOfset(){doOfset=!doOfset;}
    bool initialize();
};