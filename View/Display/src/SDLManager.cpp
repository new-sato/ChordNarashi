#include "SDLManager.hpp"
#include <cmath>
#include <string>
#include <algorithm>
#include <SDL3/SDL_rect.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


SDLManager::SDLManager()
{
    if(!initialize())
    {
        exit(1);
    }
    character_manager = SDLCharacterManager(mRenderer);
    m_circle_manager = SDLCircleManager(mRenderer, windowWidth, windowHight);
}

void SDLManager::addTextureToDraw(const SDLTextureData &input)
{
    m_textures.push_back(input);
}

bool SDLManager::initialize()
{
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDLを初期化できません");
        return false;
    }
    
    if(!TTF_Init())
    {
        SDL_Log("TTF_Init Error");
        return false;
    }

    mWindow = SDL_CreateWindow(
        "TEST",
        windowWidth,
        windowHight,
        0
    );

    if(!mWindow)
    {
        SDL_Log("ウィンドウの作成に失敗しました");
        return false;
    }
    
    mRenderer = SDL_CreateRenderer(
        mWindow,
        nullptr
    );

    updateDisplay();

    return true;
}

SDLManager::~SDLManager()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void SDLManager::displayCharacter(const charaData& input)
{
    SDL_Texture* t = character_manager.generateCharaTexture(input.str, input.font_size);
    int x = input.x*(windowWidth/2) + windowWidth/2;
    int y = input.y*(windowHight/2) + windowHight/2;
    SDLTextureData d(t, x, y, 0);
    addTextureToDraw(d);
}

void SDLManager::displayRectangle(const Rectangle & input)
{
    double upper_left_x = input.x - input.horizontal_length/2;
    double upper_left_y = input.y - input.vertical_length/2;
    
    int x = input.x*(windowWidth/2) + windowWidth/2;
    int y = input.y*(windowHight/2) + windowHight/2;
    
    SDL_Texture* targetTexture = SDL_CreateTexture(
        mRenderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        input.horizontal_length*windowWidth,
        input.vertical_length*windowHight
    );
    
    SDL_SetRenderTarget(mRenderer, targetTexture);
    
    SDL_SetRenderDrawColor(mRenderer, input.red, input.green, input.blue, input.alpha);
    SDL_RenderClear(mRenderer);
    SDL_SetRenderTarget(mRenderer, NULL);
    SDLTextureData d(targetTexture, x, y, -1);    
    addTextureToDraw(d);
}

void SDLManager::displayCircle(const Circle & input)
{
    SDL_Texture* texture = m_circle_manager.generateCircleTexture(
        CircleInfo{
            .r = input.r,
            .red = input.red,
            .green = input.green,
            .blue = input.blue,
            .alpha = input.alpha
        }
    );
    int x = input.x*(windowWidth/2) + windowWidth/2;
    int y = input.y*(windowHight/2) + windowHight/2;
    SDLTextureData d(texture, x, y, -1);
    addTextureToDraw(d);
}

void SDLManager::pollEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_EVENT_QUIT)
        {
            m_quit_requested = true;
        }
        else if(event.type == SDL_EVENT_WINDOW_FOCUS_GAINED)
        {
            is_focused = true;
        }
        else if(event.type == SDL_EVENT_WINDOW_FOCUS_LOST)
        {
            is_focused = false;
        }
        else if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                m_mouse_down = true;
                processClickOrTouch(event.button.x, event.button.y, true);
            }
        }
        else if(event.type == SDL_EVENT_MOUSE_BUTTON_UP)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                m_mouse_down = false;
                processClickOrTouch(event.button.x, event.button.y, false);
            }
        }
        else if(event.type == SDL_EVENT_MOUSE_MOTION)
        {
            if(m_mouse_down)
            {
                processClickOrTouch(event.motion.x, event.motion.y, true);
            }
        }
    }
}

void SDLManager::processClickOrTouch(float x, float y, bool is_pressed)
{
    // 全てクリア
    for(auto& row : m_virtual_chord_buttons)
    {
        std::fill(row.begin(), row.end(), false);
    }

    if(!is_pressed)
    {
        return;
    }

    // 画面中心基準の正規化座標 (-1.0 〜 1.0) に変換
    double norm_x = (x - windowWidth / 2.0) / (windowWidth / 2.0);
    double norm_y = (y - windowHight / 2.0) / (windowHight / 2.0);

    // 中心からの距離
    double r = std::sqrt(norm_x * norm_x + norm_y * norm_y);

    // 半径の境界判定 (Major=0.75, minor=0.55, dim=0.35)
    int ring = -1;
    if(r >= 0.65 && r <= 0.95)
    {
        ring = 0; // Major
    }
    else if(r >= 0.45 && r < 0.65)
    {
        ring = 1; // minor
    }
    else if(r >= 0.25 && r < 0.45)
    {
        ring = 2; // dim
    }

    if(ring == -1)
    {
        return;
    }

    // クリックされた角度の計算 (上方向が 0, 時計回りが正)
    double angle_clicked = std::atan2(norm_x, -norm_y);

    // 現在のキーによる回転角度を補正
    double target_angle = -m_key * 2.0 * M_PI / 12.0;
    double relative_angle = angle_clicked - target_angle;

    // 角度を [-PI, PI] の範囲に正規化
    while(relative_angle < -M_PI) relative_angle += 2.0 * M_PI;
    while(relative_angle > M_PI) relative_angle -= 2.0 * M_PI;

    // 角度から 12 個のセクターインデックス (0〜11) を算出
    double sector = relative_angle * 12.0 / (2.0 * M_PI);
    if(sector < 0) sector += 12.0;

    int sector_idx = static_cast<int>(std::round(sector)) % 12;
    if(sector_idx < 0) sector_idx += 12;

    // 音楽理論的なノート解決 (リングごとのオフセット適用)
    // Major: offset = 0 => note = sector_idx
    // minor: offset = -3 => note = (sector_idx + 3) % 12
    // dim:   offset = -5 => note = (sector_idx + 5) % 12
    int note = -1;
    if(ring == 0) // Major
    {
        note = sector_idx;
    }
    else if(ring == 1) // minor
    {
        note = (sector_idx + 3) % 12;
    }
    else if(ring == 2) // dim
    {
        note = (sector_idx + 5) % 12;
    }

    if(note >= 0 && note < 12)
    {
        m_virtual_chord_buttons[ring][note] = true;
    }
}

void SDLManager::updateDisplay()
{
    SDL_SetRenderDrawColor(
        mRenderer,
        20,
        20,
        20,
        255
    );

    // 塗りつぶし
    SDL_RenderClear(mRenderer);

    std::sort(m_textures.begin(), m_textures.end());
    for(SDLTextureData s: m_textures)
    {
        SDL_RenderTexture(mRenderer, s.getTexture(), NULL, &s.getRect());
    }
    
    SDL_RenderPresent(mRenderer);
    
    m_textures.clear();
}

bool SDLManager::is_x_button_pressed()
{
    return m_quit_requested;
}

bool SDLManager::isKeyPressed(int scancode) const
{
    int numkeys;
    const bool* state = SDL_GetKeyboardState(&numkeys);
    if(state && scancode >= 0 && scancode < numkeys)
    {
        return state[scancode] != 0;
    }
    return false;
}

