#include "../include/Image_Handler.h"

Image_Handler::Image_Handler(){}


Image_Handler::Image_Handler(std::vector <std::string> Image_names, SDL_Renderer* renderer) {

	for (int i = 0; i < Image_names.size(); i++) {
		char* name = &Image_names[i][0];
		auto surface = std::shared_ptr<SDL_Surface> (IMG_Load(name), SDL_FreeSurface);
		Textures.insert(std::pair < std::string, std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>>(Image_names[i], 
			std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>(SDL_CreateTextureFromSurface(renderer, surface.get()), SDL_DestroyTexture)));
	}
}

SDL_Texture* Image_Handler::get_Texture(std::string image_name) {
	if (!Textures.empty()) {
		if (Textures.find(image_name) != Textures.end()) {
			return Textures[image_name].get();
		}
	}
}