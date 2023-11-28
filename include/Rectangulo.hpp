#ifndef RECTANGULO_HPP
#define RECTANGULO_HPP

#pragma once
#include <SDL2/SDL.h>
#include "Ventana.hpp"
#include "Globales.hpp"
#include <string>

class Rectangulo
{

private:
    int _x, _y, _ancho, _alto;

public:
    Rectangulo(/* args */);
    Rectangulo(int x, int y, int ancho, int alto) : _x(x), _y(y), _ancho(ancho), _alto(alto)
    {
    }

    const int getCentroX() const { return this->_x + this-> _ancho / 2; }
    const int getCentroY() const { return this->_y + this-> _alto / 2; }

    const int getIzq() const { return this->_x; }
    const int getDer() const { return this->_x + this->_ancho; }
    const int getArriba() const { return this->_y; }
    const int getAbajo() const { return this->_y + this->_alto; }

    const int getAncho() const { return this->_ancho; }
    const int getAlto() const { return this->_alto; }

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
        return (this->_x >= 0 && this->_y >= 0 && this->_ancho >= 0 && this->_alto >= 0);
    }
    ~Rectangulo();
};

#endif