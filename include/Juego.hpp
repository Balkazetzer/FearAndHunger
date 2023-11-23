#pragma once
#include <SDL2/SDL.h>
#include "Ventana.hpp"

#include "../include/Entradas.hpp"
class Juego
{
private:
    /* data */
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

Juego::Juego()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    this->loop();
}

void Juego::loop()
{
    Ventana ventana;
    Entradas entrada;
    SDL_Event evento;

    int LAST_UPDATE_TIME = SDL_GetTicks();

    while (true)
    {
        entrada.ActualizarFrame();
        if (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_KEYUP)
            {
                entrada.IrArriba(evento);
            }
            if (evento.type == SDL_KEYDOWN)
            {
                entrada.IrAbajo(evento);
            }
            if (evento.type == SDLK_LEFT)
            {
                entrada.IrIzquierda(evento);
            }
            if (evento.type == SDLK_RIGHT)
            {
                entrada.IrDerecha(evento);
            }
            if (evento.type == SDL_QUIT)
            {
                return;
            }
            if (entrada.TeclaPresionada(SDL_SCANCODE_ESCAPE) == true)
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
}

void Juego::actualizar(float lapso)
{
}
