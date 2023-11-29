#ifndef SPRITE_H
#define SPRITE_H



#pragma once
#include <SDL2/SDL.h>
#include "Ventana.h"
#include "Globales.h"
#include "Rectangulo.h"
#include <string>
using namespace std;

class Sprite
{
protected:
    SDL_Rect _sourceRect;
    SDL_Texture* _spriteSheet;
    Rectangulo _contornos;
    float _x, _y;

public:
    Sprite();
    Sprite(Ventana &ventana, const string &path, int sourceX, int sourceY, int ancho, int altura, float posX, float posY);
    ~Sprite() = default;
    void actualizar();
    void dibujar(Ventana &ventena, int x, int y);
    const Rectangulo obtenerContornos() const;
    const lados::Lado obtenerLadoColision(const Rectangulo &otro) const;
};


#endif