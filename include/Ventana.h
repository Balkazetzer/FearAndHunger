#ifndef VENTANAS_H
#define VENTANAS_H

#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <map>
#include <SDL2/SDL_image.h>

using namespace std;

class Ventana
{
protected:
    // INFORMACIÓN PARA INICIALIZAR LA VENTANA
    const int SCREEN_WIDTH = 840;
    const int SCREEN_HEIGHT = 680;

    SDL_Window *mainVentana = NULL;      // Ventana de contenido
    SDL_Renderer *mainSuperficie = NULL; // Contenido base
    map<string, SDL_Surface *> _sprites;

public:
    Ventana(/* args */);
    ~Ventana();

    SDL_Surface *cargarImagen(const string &path);
    void blitSuperficie(SDL_Texture *fuente, SDL_Rect *rectFuente, SDL_Rect *rectDestino);
    void flip();
    void clear();

    SDL_Renderer *GetRenderer() const;
};

/*-----------------DEFINICION DE LAS FUNCIONES-------------*/

// CONSTRUCTOR Y DESTRUCTOR

#endif