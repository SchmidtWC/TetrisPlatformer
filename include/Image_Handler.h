#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <memory>

class Image_Handler {
private:
	std::map <std::string, std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>> Textures;

public:
	Image_Handler();
	Image_Handler(std::vector <std::string> Image_names, SDL_Renderer* renderer);
	SDL_Texture* get_Texture(std::string image_name);
};