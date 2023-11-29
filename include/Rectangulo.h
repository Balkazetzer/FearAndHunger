#ifndef RECTANGULO_H
#define RECTANGULO_H

#pragma once
#include <SDL2/SDL.h>
#include "Ventana.h"
#include "Globales.h"
#include <stdexcept>
#include <string>
using namespace std;

class Rectangulo
{

private:
    int _x, _y, _ancho, _alto;

public:
    Rectangulo(/* args */);
    Rectangulo(int x, int y, int ancho, int alto);
    int getCentroX() const { return this->_x + this-> _ancho / 2; }
    int getCentroY() const { return this->_y + this-> _alto / 2; }

    int getIzq() const { return this->_x; }
    int getDer() const { return this->_x + this->_ancho; }
    int getArriba() const { return this->_y; }
    int getAbajo() const { return this->_y + this->_alto; }

    int getAncho() const { return this->_ancho; }
    int getAlto() const { return this->_alto; }

    const int getLado(const lados::Lado lado) const
    {
        return
            lado == lados::IZQUIERDO ? this->getIzq() :
            lado == lados::DERECHO ? this->getDer() :
            lado == lados::ARRIBA ? this->getArriba() :
            lado == lados::ABAJO ? this->getAbajo() :
            lados:: NINGUNO;
    }

    const bool intersectaCon(const Rectangulo &otro) const
    {
        return
            this->getDer() >= otro.getIzq() &&
            this->getIzq() <= otro.getDer() &&
            this->getArriba() <= otro.getAbajo() &&
            this->getAbajo() >= otro.getArriba();
            

    }

    const bool validar(const Rectangulo &otro){
    if (this->_x < 0 || this->_y < 0 || this->_ancho < 0 || this->_alto < 0) {
        throw invalid_argument("Invalid rectangle dimensions");
    }
    return true;
}
    ~Rectangulo() = default;
};

#endif