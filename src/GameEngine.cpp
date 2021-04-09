#include "../include/GameEngine.h"

void GameEngine::my_SDL_init() {
      if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { 
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl; 
    }

    //Enable gpu_enhanced textures
    IMG_Init(IMG_INIT_PNG);
    
    my_window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> (SDL_CreateWindow("my_game", 
                    SDL_WINDOWPOS_CENTERED, 
                    SDL_WINDOWPOS_CENTERED, 
                    screenWidth,
                    screenHeight, 0), 
                    SDL_DestroyWindow);

    my_renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> 
        (SDL_CreateRenderer(my_window.get(), -1, SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer);
}

void GameEngine::gameLoop() {
    is_running = true;
    SDL_Event event;
    
    // game loop
    while(is_running){
        bool eventStatus= SDL_PollEvent(&event);

        SDL_RenderClear(my_renderer.get());
        SDL_SetRenderDrawColor(my_renderer.get(), 171, 106, 140, 255);

        if(eventStatus) {
            if (event.type == SDL_QUIT) {
                is_running = false;
            }
        }

        SDL_RenderPresent(my_renderer.get());

    }
}
