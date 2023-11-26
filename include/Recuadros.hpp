#ifndef RECUADROS_HPP
#define RECUADROS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Globales.hpp"
#include "Ventana.hpp"


class Recuadros
{
private:
    SDL_Texture *recSet;
    Vector2 _tamanyoRecuadro;
    Vector2 _posicionRecuadro;
    Vector2 _posicion;

public:
    Recuadros();
    Recuadros(SDL_Texture *recSet, Vector2 tamanyoRecuadro, Vector2 posicionRecuadro, Vector2 posicion);
    void Actualizar(float lapso);
    void Dibujar(Ventana &ventana);
    ~Recuadros();
};

Recuadros::Recuadros(/* args */)
{
}

Recuadros::Recuadros(SDL_Texture *recSet, Vector2 tamanyoRecuadro, Vector2 posicionRecuadro, Vector2 posicion):
    recSet(recSet),
    _tamanyoRecuadro(tamanyoRecuadro),
    _posicionRecuadro(posicionRecuadro),
    _posicion(Vector2(posicion.x*globales::ESCALA_SPRITE, posicion.y*globales::ESCALA_SPRITE))
{

}

void Recuadros::Actualizar(float lapso)
{
}

void Recuadros::Dibujar(Ventana &ventana){

    SDL_Rect destRect = {this->_posicion.x, this->_posicion.y, this->_tamanyoRecuadro.x*globales::ESCALA_SPRITE, this->_tamanyoRecuadro.y*globales::ESCALA_SPRITE};
    SDL_Rect rectfuente = {this->_posicionRecuadro.x, this->_posicionRecuadro.y, this->_tamanyoRecuadro.x, this->_tamanyoRecuadro.y};
    ventana.blitSuperficie(this->recSet, &rectfuente, &destRect);

}



Recuadros::~Recuadros()
{
}



#endif 
