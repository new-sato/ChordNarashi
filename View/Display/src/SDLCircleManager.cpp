#include "SDLCircleManager.hpp"
#include <cmath>
#include <algorithm>

bool CircleInfo::operator<(const CircleInfo &rh) const
{
    if(r!=rh.r) return r < rh.r;
    else if(red!=rh.red) return red < rh.red;
    else if(green!=rh.green) return green < rh.green;
    else if(blue!=rh.blue) return blue < rh.blue;
    else return alpha < rh.alpha;
}

SDLCircleManager::SDLCircleManager(
    SDL_Renderer *renderer,
    int w,
    int h
):
    m_renderer(renderer),
    m_window_width(w),
    m_window_hight(h)
{
}

SDLCircleManager::~SDLCircleManager()
{
    for(auto c:textureCash)
    {
        SDL_DestroyTexture(c.second);
    }
}

void SDLCircleManager::updateWindowSize(int w, int h)
{
    if (m_window_width != w || m_window_hight != h)
    {
        m_window_width = w;
        m_window_hight = h;
        // Invalidate texture cache on resize
        for (auto c : textureCash)
        {
            SDL_DestroyTexture(c.second);
        }
        textureCash.clear();
    }
}

SDL_Texture *SDLCircleManager::generateCircleTexture(CircleInfo input)
{
    if(textureCash.contains(input))
    {
        return textureCash[input];
    }

    int size = std::max(2, static_cast<int>(std::round(input.r * 2.0 * std::min(m_window_width, m_window_hight))));

    SDL_Texture* targetTexture = SDL_CreateTexture(
        m_renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        size,
        size
    );
    
    SDL_SetRenderTarget(m_renderer, targetTexture);
    
    // Set texture blending mode so transparent background works perfectly
    SDL_SetTextureBlendMode(targetTexture, SDL_BLENDMODE_BLEND);

    // Clear texture with completely transparent pixels
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
    SDL_RenderClear(m_renderer);

    // Render true filled circle using sweep lines
    SDL_SetRenderDrawColor(m_renderer, input.red, input.green, input.blue, input.alpha);
    float cx = size / 2.0f;
    float cy = size / 2.0f;
    float r = size / 2.0f;
    for (float dy = -r; dy <= r; dy += 1.0f)
    {
        float dx = std::sqrt(std::max(0.0f, r * r - dy * dy));
        SDL_RenderLine(m_renderer, cx - dx, cy + dy, cx + dx, cy + dy);
    }

    SDL_SetRenderTarget(m_renderer, NULL);
    textureCash.insert({input ,targetTexture});
    return targetTexture;
}
