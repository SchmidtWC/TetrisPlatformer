  
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <iostream>
#include <string>
#include <math.h>
#include <vector>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>
#include <functional>
#include <memory>

class GameEngine {
    private:
        std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> my_window;
        std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> my_renderer;
        int screenWidth;
        int screenHeight;
        bool is_running;

    public: 
        GameEngine(int w, int h) {
            screenWidth = w;
            screenHeight = h;
            my_window = NULL;
            my_renderer = NULL;
        }

        ~GameEngine() {}

        void my_SDL_init();
        void gameLoop();

};

#endif