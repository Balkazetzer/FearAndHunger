#ifndef JUEGO_HPP
#define JUEGO_HPP

#pragma once
#include <SDL2/SDL.h>
#include "Ventana.hpp"
#include "Nivel.hpp"

#include "../include/Entradas.hpp"

class Juego
{
private:
    Nivel _nivel;
    Ventana ventana;
public:
    Juego(/* args */);
    ~Juego();

    void loop();
    void dibujar(Ventana &ventana);
    void actualizar(float lapso);
};

namespace
{
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Juego::Juego() : _nivel("", Vector2(0, 0), ventana)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    this->loop();
}


void Juego::loop()
{
    Entradas entrada;
    SDL_Event evento;

    this->_nivel = Nivel("map1", Vector2(480,640), ventana);

    int LAST_UPDATE_TIME = SDL_GetTicks();

    while (true)
    {
        entrada.ActualizarFrame();
        while (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_KEYUP)
            {
                entrada.IrArriba(evento);
            }
            else if (evento.type == SDL_KEYDOWN)
            {
                entrada.IrAbajo(evento);
            }
            else if (evento.key.keysym.sym == SDLK_LEFT)
            {
                entrada.IrIzquierda(evento);
            }
            else if (evento.key.keysym.sym == SDLK_RIGHT)
            {
                entrada.IrDerecha(evento);
            }
            else if (evento.type == SDL_QUIT)
            {
                return;
            }
            else if (entrada.TeclaPresionada(SDL_SCANCODE_ESCAPE) == true)
            {
                return;
            }
        }

        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        this->actualizar(min(ELAPSED_TIME, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;
    }
}

void Juego::dibujar(Ventana &ventana)
{
    this->_nivel.Dibujar(ventana);
}

void Juego::actualizar(float lapso)
{
    this->_nivel.ActualizarMapa(lapso);
}

#endif