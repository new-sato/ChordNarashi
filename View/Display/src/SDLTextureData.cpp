#include "SDLTextureData.hpp"

SDLTextureData::SDLTextureData(
    SDL_Texture *texture,
    float x_arg, float y_arg,
    int priority
):
    m_texture(texture),
    m_priority(priority)
{
    SDL_GetTextureSize(m_texture, &m_destRect.w, &m_destRect.h);
    m_destRect.x = x_arg - m_destRect.w/2;
    m_destRect.y = y_arg - m_destRect.h/2;
}
