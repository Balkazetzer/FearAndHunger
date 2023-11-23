#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>

class Ventana
{
protected:
    // INFORMACIÓN PARA INICIALIZAR LA VENTANA
    const int SCREEN_WIDTH = 840;
    const int SCREEN_HEIGHT = 680;

    SDL_Window *mainVentana = NULL;      // Ventana de contenido
    SDL_Renderer *mainSuperficie = NULL; // Contenido base

public:
    Ventana(/* args */);
    ~Ventana();
};

// CONSTRUCTOR Y DESTRUCTOR
Ventana::Ventana(/* args */){
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH,SCREEN_HEIGHT, 0, &this->mainVentana, &this->mainSuperficie);
    SDL_SetWindowTitle(this->mainVentana, "Fear and Hunger");
    }

Ventana::~Ventana()
{
    SDL_DestroyWindow(this->mainVentana);
    
}
