#pragma once

#include <map>
#include <SDL2/SDL.h>
#include <string>


class AssetDataBase
{
    public:
        AssetDataBase();
        ~AssetDataBase();
        void ClearTextures();
        void AddTexture(SDL_Renderer* renderer, const std::string& ID, const std::string& imgPath);
        SDL_Texture* GetTexture(const std::string& ID);
        
    private:  
        std::map<std::string, SDL_Texture*> textures;
        
};
