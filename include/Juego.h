#ifndef JUEGO_H
#define JUEGO_H

#pragma once
#include <SDL2/SDL.h>
#include "Ventana.h"
#include "Nivel.h"
#include "Sprite.h"
#include "Animacion.h"
#include "Globales.h"
#include "Jugador.h"
#include "Entradas.h"
#include "Rectangulo.h"

namespace
{
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

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

#endif