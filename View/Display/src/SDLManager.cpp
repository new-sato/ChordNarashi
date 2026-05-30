#include "SDLManager.hpp"
#include <SDL3/SDL_rect.h>
#include <algorithm>
#include <cmath>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

SDLManager::SDLManager() {
  if (!initialize()) {
    exit(1);
  }
  character_manager = SDLCharacterManager(mRenderer);
  m_circle_manager = SDLCircleManager(mRenderer, windowWidth, windowHight);
}

void SDLManager::addTextureToDraw(const SDLTextureData &input) {
  m_textures.push_back(input);
}

bool SDLManager::initialize() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDLを初期化できません");
    return false;
  }

  if (!TTF_Init()) {
    SDL_Log("TTF_Init Error");
    return false;
  }

  mWindow = SDL_CreateWindow("TEST", windowWidth, windowHight, 0);

  if (!mWindow) {
    SDL_Log("ウィンドウの作成に失敗しました");
    return false;
  }

  mRenderer = SDL_CreateRenderer(mWindow, nullptr);

  updateDisplay();

  return true;
}

SDLManager::~SDLManager() {
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);
  SDL_Quit();
}

void SDLManager::displayCharacter(const charaData &input) {
  SDL_Texture *t =
      character_manager.generateCharaTexture(input.str, input.font_size);
  double scale = std::min(windowWidth, windowHight) / 2.0;
  int x = input.x * scale + windowWidth / 2;
  int y = input.y * scale + windowHight / 2;
  SDLTextureData d(t, x, y, 0);
  addTextureToDraw(d);
}

void SDLManager::displayRectangle(const Rectangle &input) {
  double scale = std::min(windowWidth, windowHight) / 2.0;
  int x = input.x * scale + windowWidth / 2;
  int y = input.y * scale + windowHight / 2;

  SDL_Texture *targetTexture = SDL_CreateTexture(
      mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
      input.horizontal_length * scale * 2, input.vertical_length * scale * 2);

  SDL_SetRenderTarget(mRenderer, targetTexture);

  SDL_SetRenderDrawColor(mRenderer, input.red, input.green, input.blue,
                         input.alpha);
  SDL_RenderClear(mRenderer);
  SDL_SetRenderTarget(mRenderer, NULL);
  SDLTextureData d(targetTexture, x, y, -1);
  addTextureToDraw(d);
}

void SDLManager::displayCircle(const Circle &input) {
  m_circle_manager.updateWindowSize(windowWidth, windowHight);
  SDL_Texture *texture =
      m_circle_manager.generateCircleTexture(CircleInfo{.r = input.r,
                                                        .red = input.red,
                                                        .green = input.green,
                                                        .blue = input.blue,
                                                        .alpha = input.alpha});
  double scale = std::min(windowWidth, windowHight) / 2.0;
  int x = input.x * scale + windowWidth / 2;
  int y = input.y * scale + windowHight / 2;
  SDLTextureData d(texture, x, y, -1);
  addTextureToDraw(d);
}

void SDLManager::pollEvents() {
  SDL_GetWindowSize(mWindow, &windowWidth, &windowHight);

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      m_quit_requested = true;
    } else if (event.type == SDL_EVENT_WINDOW_FOCUS_GAINED) {
      is_focused = true;
    } else if (event.type == SDL_EVENT_WINDOW_FOCUS_LOST) {
      is_focused = false;
    } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      if (event.button.button == SDL_BUTTON_LEFT) {
        m_mouse_down = true;
        m_mouse_x = event.button.x;
        m_mouse_y = event.button.y;
      }
    } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
      if (event.button.button == SDL_BUTTON_LEFT) {
        m_mouse_down = false;
      }
    } else if (event.type == SDL_EVENT_MOUSE_MOTION) {
      m_mouse_x = event.motion.x;
      m_mouse_y = event.motion.y;
    } else if (event.type == SDL_EVENT_FINGER_DOWN ||
               event.type == SDL_EVENT_FINGER_MOTION) {
      m_touches[event.tfinger.fingerID] =
          TouchInfo{event.tfinger.x, event.tfinger.y};
    } else if (event.type == SDL_EVENT_FINGER_UP) {
      m_touches.erase(event.tfinger.fingerID);
    }
  }

  evaluateInputStates();
}

void SDLManager::evaluateInputStates() {
  // 全てクリア
  for (auto &row : m_virtual_chord_buttons) {
    std::fill(row.begin(), row.end(), false);
  }
  m_virtual_ring_pressed = false;
  m_virtual_sustain_pressed = false;
  m_virtual_dom_pressed = false;
  m_virtual_subdom_pressed = false;
  m_virtual_semiup_pressed = false;
  m_virtual_semidown_pressed = false;

  // アクティブなタッチ座標の収集
  std::vector<std::pair<float, float>> active_points;
  if (!m_touches.empty()) {
    for (const auto &pair : m_touches) {
      active_points.push_back(
          {pair.second.x * windowWidth, pair.second.y * windowHight});
    }
  } else if (m_mouse_down) {
    active_points.push_back({m_mouse_x, m_mouse_y});
  }

  float button_r = std::min(windowWidth, windowHight) * 0.07f;
  float sustain_cx = windowWidth * 0.08;
  float sustain_cy = windowHight * 0.85f;
  float subdom_cx = windowWidth * 0.08f;
  float subdom_cy = windowHight * 0.65f;
  float semidown_cx = windowWidth * 0.08f;
  float semidown_cy = windowHight * 0.45f;

  float play_cx = windowWidth * 0.92f;
  float play_cy = windowHight * 0.85f;
  float dom_cx = windowWidth * 0.92f;
  float dom_cy = windowHight * 0.65f;
  float semiup_cx = windowWidth * 0.92f;
  float semiup_cy = windowHight * 0.45f;

  for (const auto &pt : active_points) {
    float px = pt.first;
    float py = pt.second;

    // Check Sustain Button
    float dx_sus = px - sustain_cx;
    float dy_sus = py - sustain_cy;
    if (dx_sus * dx_sus + dy_sus * dy_sus <= button_r * button_r) {
      m_virtual_sustain_pressed = true;
      continue;
    }

    // Check Subdominant Modulation Button (j)
    float dx_sub = px - subdom_cx;
    float dy_sub = py - subdom_cy;
    if (dx_sub * dx_sub + dy_sub * dy_sub <= button_r * button_r) {
      m_virtual_subdom_pressed = true;
      continue;
    }

    // Check Semi-down Modulation Button (m)
    float dx_semidown = px - semidown_cx;
    float dy_semidown = py - semidown_cy;
    if (dx_semidown * dx_semidown + dy_semidown * dy_semidown <=
        button_r * button_r) {
      m_virtual_semidown_pressed = true;
      continue;
    }

    // Check Play Button
    float dx_play = px - play_cx;
    float dy_play = py - play_cy;
    if (dx_play * dx_play + dy_play * dy_play <= button_r * button_r) {
      m_virtual_ring_pressed = true;
      continue;
    }

    // Check Dominant Modulation Button (l)
    float dx_dom = px - dom_cx;
    float dy_dom = py - dom_cy;
    if (dx_dom * dx_dom + dy_dom * dy_dom <= button_r * button_r) {
      m_virtual_dom_pressed = true;
      continue;
    }

    // Check Semi-up Modulation Button (o)
    float dx_semiup = px - semiup_cx;
    float dy_semiup = py - semiup_cy;
    if (dx_semiup * dx_semiup + dy_semiup * dy_semiup <= button_r * button_r) {
      m_virtual_semiup_pressed = true;
      continue;
    }

    // Otherwise check the Circle of Fifths
    processClickOrTouch(px, py, true);
  }
}

void SDLManager::processClickOrTouch(float x, float y, bool is_pressed) {
  if (!is_pressed) {
    return;
  }

  // 画面中心基準の正規化座標 (-1.0 〜 1.0) に変換 (アスペクト比を維持)
  double scale = std::min(windowWidth, windowHight) / 2.0;
  double norm_x = (x - windowWidth / 2.0) / scale;
  double norm_y = (y - windowHight / 2.0) / scale;

  // 中心からの距離
  double r = std::sqrt(norm_x * norm_x + norm_y * norm_y);

  // 半径の境界判定 (Major=0.75, minor=0.55, dim=0.35)
  int ring = -1;
  if (r >= 0.65 && r <= 0.95) {
    ring = 0; // Major
  } else if (r >= 0.45 && r < 0.65) {
    ring = 1; // minor
  } else if (r >= 0.25 && r < 0.45) {
    ring = 2; // dim
  }

  if (ring == -1) {
    return;
  }

  // クリックされた角度の計算 (上方向が 0, 時計回りが正)
  double angle_clicked = std::atan2(norm_x, -norm_y);

  // 角度を [-PI, PI] の範囲に正規化
  while (angle_clicked < -M_PI)
    angle_clicked += 2.0 * M_PI;
  while (angle_clicked > M_PI)
    angle_clicked -= 2.0 * M_PI;

  // 角度から 12 個のセクターインデックス (0〜11) を算出
  double sector = angle_clicked * 12.0 / (2.0 * M_PI);
  if (sector < 0)
    sector += 12.0;

  int sector_idx = static_cast<int>(std::round(sector)) % 12;
  if (sector_idx < 0)
    sector_idx += 12;

  if (sector_idx >= 0 && sector_idx < 12) {
    m_virtual_chord_buttons[ring][sector_idx] = true;
  }
}

void SDLManager::drawFilledCircle(float cx, float cy, float r,
                                  SDL_Color color) {
  SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
  for (float dy = -r; dy <= r; dy += 1.0f) {
    float dx = std::sqrt(r * r - dy * dy);
    SDL_RenderLine(mRenderer, cx - dx, cy + dy, cx + dx, cy + dy);
  }
}

void SDLManager::drawVirtualButtons() {
  float button_r = std::min(windowWidth, windowHight) * 0.08f;

  float sustain_cx = windowWidth * 0.08f;
  float sustain_cy = windowHight * 0.85f;
  float subdom_cx = windowWidth * 0.08f;
  float subdom_cy = windowHight * 0.65f;
  float semidown_cx = windowWidth * 0.08f;
  float semidown_cy = windowHight * 0.45f;

  float play_cx = windowWidth * 0.92f;
  float play_cy = windowHight * 0.85f;
  float dom_cx = windowWidth * 0.92f;
  float dom_cy = windowHight * 0.65f;
  float semiup_cx = windowWidth * 0.92f;
  float semiup_cy = windowHight * 0.45f;

  SDL_Color border_color = {255, 255, 255, 255};
  SDL_Color sustain_bg = m_virtual_sustain_pressed
                             ? SDL_Color{80, 180, 240, 255}
                             : SDL_Color{50, 50, 60, 200};
  SDL_Color subdom_bg = m_virtual_subdom_pressed ? SDL_Color{80, 220, 200, 255}
                                                 : SDL_Color{50, 50, 60, 200};
  SDL_Color semidown_bg = m_virtual_semidown_pressed
                              ? SDL_Color{240, 150, 50, 255}
                              : SDL_Color{50, 50, 60, 200};

  SDL_Color play_bg = m_virtual_ring_pressed ? SDL_Color{100, 220, 120, 255}
                                             : SDL_Color{50, 50, 60, 200};
  SDL_Color dom_bg = m_virtual_dom_pressed ? SDL_Color{80, 220, 200, 255}
                                           : SDL_Color{50, 50, 60, 200};
  SDL_Color semiup_bg = m_virtual_semiup_pressed ? SDL_Color{240, 150, 50, 255}
                                                 : SDL_Color{50, 50, 60, 200};

  auto drawBtn = [this, button_r, border_color](
                     float cx, float cy, SDL_Color bg, const char *label) {
    drawFilledCircle(cx, cy, button_r + 3.0f, border_color);
    drawFilledCircle(cx, cy, button_r, bg);
    SDL_Texture *tex =
        character_manager.generateCharaTexture(label, button_r * 0.4f);
    if (tex) {
      float w, h;
      SDL_GetTextureSize(tex, &w, &h);
      SDL_FRect dest = {cx - w / 2.0f, cy - h / 2.0f, w, h};
      SDL_RenderTexture(mRenderer, tex, NULL, &dest);
    }
  };

  // Draw Left Column (Sustain, Subdominant, Semi-down)
  drawBtn(sustain_cx, sustain_cy, sustain_bg, "SUS");
  drawBtn(subdom_cx, subdom_cy, subdom_bg, "SUB");
  drawBtn(semidown_cx, semidown_cy, semidown_bg, "-1");

  // Draw Right Column (Play, Dominant, Semi-up)
  drawBtn(play_cx, play_cy, play_bg, "PLAY");
  drawBtn(dom_cx, dom_cy, dom_bg, "DOM");
  drawBtn(semiup_cx, semiup_cy, semiup_bg, "+1");
}

void SDLManager::updateDisplay() {
  SDL_SetRenderDrawColor(mRenderer, 20, 20, 20, 255);

  // 塗りつぶし
  SDL_RenderClear(mRenderer);

  std::sort(m_textures.begin(), m_textures.end());
  for (SDLTextureData s : m_textures) {
    SDL_RenderTexture(mRenderer, s.getTexture(), NULL, &s.getRect());
  }

  // 仮想ボタンの描画
  drawVirtualButtons();

  SDL_RenderPresent(mRenderer);

  m_textures.clear();
}

bool SDLManager::is_x_button_pressed() { return m_quit_requested; }

bool SDLManager::isKeyPressed(int scancode) const {
  int numkeys;
  const bool *state = SDL_GetKeyboardState(&numkeys);
  if (state && scancode >= 0 && scancode < numkeys) {
    return state[scancode] != 0;
  }
  return false;
}
