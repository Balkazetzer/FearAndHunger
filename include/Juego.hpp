#ifndef JUEGO_HPP
#define JUEGO_HPP

#pragma once
#include <SDL2/SDL.h>
#include "Ventana.hpp"
#include "Nivel.hpp"
#include "Sprite.hpp"
#include "Animacion.hpp"
#include "Globales.hpp"
#include "Jugador.hpp"
#include "Entradas.hpp"
#include "Rectangulo.hpp"

class Juego
{
protected:
    Nivel _nivel;
    Ventana ventana;
    Jugador _player;
    void loop();
    void dibujar(Ventana &ventana);
    void actualizar(float lapso);

public:
    Juego(/* args */);
    ~Juego();
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

    this->_player = Jugador(ventana, 5, 5);
    this->_player.confAnimaciones();
    this->_player.comenzarAnimacion("RunLeft");
    this->_nivel = Nivel("map1", Vector2(480, 640), ventana);

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

        this->dibujar(ventana);
    }
}

void Juego::dibujar(Ventana &ventana)
{
    ventana.clear();

    this->_player.dibujar(ventana);
    this->_nivel.Dibujar(ventana);
    ventana.flip();
}

void Juego::actualizar(float lapso)
{
    this->_nivel.ActualizarMapa(lapso);
    this->_player.actualizar(lapso);

    // Apartado colisiones

    vector<Rectangulo> otros;
    if ((otros = this->_nivel.checkColisiones(this->_player.obtenerContornos())).size() > 0)
    {
        this->_player.manejarColisiones(otros);
    }
}

#endif