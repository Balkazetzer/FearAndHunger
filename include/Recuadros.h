#ifndef RECUADROS_H
#define RECUADROS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Globales.h"
#include "Ventana.h"

class Recuadros
{
protected:
    SDL_Texture *recSet;
    Vector2 _tamanyoRecuadro;
    Vector2 _posicionRecuadro;
    Vector2 _posicion;

public:
    Recuadros();
    Recuadros(SDL_Texture *recSet, Vector2 tamanyoRecuadro, Vector2 posicionRecuadro, Vector2 posicion);
    void Actualizar(float lapso);
    void Dibujar(Ventana &ventana);
    ~Recuadros() = default;
};


#endif
