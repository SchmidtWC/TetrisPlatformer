#include "../include/Button.h"

SDL_Rect Button::getRect() {
    return destRect;
}

int Button::getID() {
    return ID;
}

void Button::render(SDL_Renderer* renderer) {
    sprite->render(renderer, destRect, false);
}

bool Button::inside(int x, int y) {
    //Check if mouse is in button
    bool inside = true;

    //Mouse is left of the button
    if( x < destRect.x )
    {
        inside = false;
    }
    //Mouse is right of the button
    else if( x > destRect.x + destRect.w )
    {
        inside = false;
    }
    //Mouse above the button
    else if( y < destRect.y )
    {
        inside = false;
    }
    //Mouse below the button
    else if( y > destRect.y + destRect.h )
    {
        inside = false;
    }

    return inside;
} 