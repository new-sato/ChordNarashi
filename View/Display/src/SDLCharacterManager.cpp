#include "SDLCharacterManager.hpp"

SDLCharacterManager::SDLCharacterManager(SDL_Renderer *renderer)
{
    m_renderer = renderer;
    if(!TTF_Init())
    {
        SDL_Log("error");
        exit(-1);
    }
}

SDLCharacterManager::~SDLCharacterManager()
{
    for(auto c: textureCash)
    {
        SDL_DestroyTexture(c.second);
    }
}

SDL_Texture *SDLCharacterManager::generateCharaTexture
(
    std::string text,
    int font_size
)
{
    CashIndex index(font_size, text);
    if(textureCash.contains(CashIndex{font_size, text}))
    {
        return textureCash[index];
    }
    // TODO テクスチャを生成し、キャッシュに追加
    if(!fonts.contains(font_size))
    {
        TTF_Font* f = TTF_OpenFont(font_name.c_str(),font_size);
        fonts.insert({font_size, f});
    }
    SDL_Surface* textSurface = TTF_RenderText_Blended(fonts[font_size],text.c_str(),0,chara_color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    textureCash.insert({CashIndex(font_size, text),textTexture});
    return textTexture;
}

bool CashIndex::operator<(const CashIndex &rh)const
{
    if(size!=rh.size)
    {
        return size < rh.size;
    }
    else
    {
        return str < rh.str;
    }
}
