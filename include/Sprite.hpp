#ifndef SPRITE_HPP
#define SPRITE_HPP



#pragma once
#include <SDL2/SDL.h>
#include "Ventana.hpp"
#include "Globales.hpp"
#include "Rectangulo.hpp"
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

    virtual ~Sprite();
    virtual void actualizar();
    void dibujar(Ventana &ventena, int x, int y);
    const Rectangulo obtenerContornos() const;
    const lados::Lado obtenerLadoColision(const Rectangulo &otro) const;
};

Sprite::Sprite() {}

Sprite::Sprite(Ventana &ventana, const string &path, int sourceX, int sourceY, int ancho, int altura, float posX, float posY) : _x(posX), _y(posY)
{
    this->_sourceRect.x = sourceX;
    this->_sourceRect.y = sourceY;
    this->_sourceRect.w = ancho;
    this->_sourceRect.h = altura;

    this->_spriteSheet = SDL_CreateTextureFromSurface(ventana.GetRenderer(), ventana.cargarImagen(path));
    if (this->_spriteSheet == NULL)
    {
        printf("\nError: No se puede cargar la imagen\n");
    }

    this-> _contornos = Rectangulo(this->_x, this->_y, ancho * globales::ESCALA_SPRITE, altura * globales::ESCALA_SPRITE);
    
}

Sprite::~Sprite() {}

void Sprite::dibujar(Ventana &ventana, int x, int y)
{
    SDL_Rect rectanguloDestinado = {x, y, this->_sourceRect.w * globales::ESCALA_SPRITE, this->_sourceRect.h * globales::ESCALA_SPRITE};
    ventana.blitSuperficie(this->_spriteSheet, &this->_sourceRect, &rectanguloDestinado);
}

void Sprite::actualizar() {
    this->_contornos = Rectangulo(this->_x, this->_y, this->_sourceRect.w * globales::ESCALA_SPRITE, this->_sourceRect.h * globales::ESCALA_SPRITE);
}

const Rectangulo Sprite::obtenerContornos() const {
    return this->_contornos;
}

const lados::Lado Sprite::obtenerLadoColision(const Rectangulo &otro) const {
    int amtRight, amtLeft, amtTop, amtBottom;
    amtRight = this->_contornos.getDer() - otro.getIzq();
    amtLeft = otro.getDer() - this->_contornos.getIzq();
    amtTop = otro.getAbajo() - this->_contornos.getArriba();
    amtBottom = this->_contornos.getAbajo() - otro.getArriba();

    int vals[4] = {abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom)};
    int lowest = vals[0];
    for (int i = 0; i < 4; i++)
    {
        if (vals[i] < lowest)
        {
            lowest = vals[i];
        }
    }

    return lowest == abs(amtRight) ? lados::DERECHO :
           lowest == abs(amtLeft) ? lados::IZQUIERDO :
           lowest == abs(amtTop) ? lados::ARRIBA :
           lowest == abs(amtBottom) ? lados::ABAJO :
           lados::NINGUNO;
}

#endif