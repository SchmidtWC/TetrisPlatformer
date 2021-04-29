
#pragma once

#include <SDL.h>
#include <SDL_image.h> 
#include <SDL_ttf.h> 
#include <vector> 
#include <string> 
#include "Button.h"
#include <iostream>

class Menu{
private:

    int menuType; // 0 for start menu, 1 for level select, 2 for pause
    bool menuRunning;
    int res;

    int windowWidth;
    int windowHeight;

    std::vector<Button> startButtons;
    std::vector<Button> levelButtons;
    std::vector<Button> pauseButtons;

public:
    Menu(){}

    Menu(SDL_Window* window, Image_Handler* image){
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        menuRunning = true;

        // start menu buttons
        startButtons.push_back(Button((windowWidth-256)/2, windowHeight/2-96, 256, 96, 0, "./asset/button.png", image)); //start
        startButtons.push_back(Button((windowWidth-256)/2, windowHeight/2+96, 256, 96, 1, "./asset/button.png", image)); //quit
        // level menu buttons
        levelButtons.push_back(Button(100, 200, 96, 96, 2, "./asset/button.png", image)); // 0
        levelButtons.push_back(Button(250, 200, 96, 96, 3, "./asset/button.png", image)); // 1
        // pause menu buttons
        pauseButtons.push_back(Button((windowWidth-256)/2, windowHeight/2-96, 256, 96, 4, "./asset/button.png", image)); // resume
        pauseButtons.push_back(Button((windowWidth-256)/2, windowHeight/2+96, 256, 96, 5, "./asset/button.png", image)); // main
    }

    ~Menu() {}
    
    int menuLoop(int type, SDL_Renderer* renderer);
    void eventHandler();
    void menuSetup(SDL_Renderer* renderer);
    void renderText(int x, int y, const char* text, SDL_Renderer* renderer);
    
};