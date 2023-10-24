#include "assetdatabase.hpp"
#include <SDL2/SDL_image.h>
#include "logger.hpp"

AssetDataBase::AssetDataBase()  { Logger::Log(LOG_INFO, "New asset database created."); }

AssetDataBase::~AssetDataBase() 
{
    ClearTextures();
    Logger::Log(LOG_INFO, "Asset database destroyed.");
}

void AssetDataBase::AddTexture(SDL_Renderer* renderer, const std::string& ID, const std::string& imgPath)
{
    SDL_Surface* surface = IMG_Load(imgPath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    textures.emplace(ID, texture);
    Logger::Log(LOG_INFO, "Added asset " + ID + " to asset database.");
}

void AssetDataBase::ClearTextures()
{
    for (auto texture: textures)
    {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();
    Logger::Log(LOG_INFO, "Cleared asset database.");
}

SDL_Texture* AssetDataBase::GetTexture(const std::string& ID) 
{
    return textures[ID];
}
