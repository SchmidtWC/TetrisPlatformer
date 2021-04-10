#include "Image_Handler.h"

Image_Handler::Image_Handler(){}


Image_Handler::Image_Handler(std::vector <std::string> Image_names, SDL_Renderer* renderer) {

	for (int i = 0; i < Image_names.size(); i++) {
		char* name = &Image_names[i][0];
		SDL_Surface* temp = IMG_Load(name);
		Textures.insert(std::pair < std::string, SDL_Texture*>(Image_names[i], SDL_CreateTextureFromSurface(renderer, temp)));
		SDL_FreeSurface(temp);
	}
}

SDL_Texture* Image_Handler::get_Texture(std::string image_name) {
	if (!Textures.empty()) {
		if (Textures.find(image_name) != Textures.end()) {
			return Textures[image_name];
		}
	}
}