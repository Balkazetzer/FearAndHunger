#ifndef ENTRADAS_H
#define ENTRADAS_H

#pragma once
#include <SDL2/SDL.h>
#include <map>
using namespace std;

class Entradas
{
protected:
    map<SDL_Scancode, bool> _heldKeys;
    map<SDL_Scancode, bool> _pressedKeys;
    map<SDL_Scancode, bool> _releasedKeys;
public:
    Entradas(/* args */);
    ~Entradas();

    void ActualizarFrame();
    void IrArriba(const SDL_Event &evento);
    void IrAbajo(const SDL_Event &evento);
    void IrIzquierda(const SDL_Event &evento);
    void IrDerecha(const SDL_Event &evento);

    bool TeclaPresionada(SDL_Scancode key);
    bool TeclaLiberada(SDL_Scancode key);
    bool TeclaSostenida(SDL_Scancode key);
};

#endif