#include "SDLCircleManager.hpp"

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

SDL_Texture *SDLCircleManager::generateCircleTexture(CircleInfo input)
{
    if(textureCash.contains(input))
    {
        return textureCash[input];
    }

    SDL_Texture* targetTexture = SDL_CreateTexture(
        m_renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        input.r*2*m_window_width,
        input.r*2*m_window_hight
    );
    
    SDL_SetRenderTarget(m_renderer, targetTexture);
    
    SDL_SetRenderDrawColor(m_renderer, input.red, input.green, input.blue, input.alpha);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderTarget(m_renderer, NULL);
    textureCash.insert({input ,targetTexture});
    return targetTexture;
}
