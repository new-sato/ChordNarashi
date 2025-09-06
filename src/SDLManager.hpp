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

    std::vector<SDL_Texture*> textures;
    
    Note nowKey = Note::C;
    
    int key = 0;
    void displayCircle();
    
    SDL_Color charaColor{.r =255, .g = 255, .b = 255, .a = 255};

    int windowWidth = 1000;
    int windowHight = 700;

    public:
    SDLManager();
    ~SDLManager();
    void updateView();
    void updateKey(int keyDiff)override{key=(key+keyDiff)%12;}
    void updateRotateState(int rotateNum)override{return;}

    bool initialize();
};