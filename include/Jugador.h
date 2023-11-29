#pragma once
#include <SDL2/SDL.h>
#include "Ventana.h"
#include "Animacion.h"
#include "Globales.h"
#include "tinyxml2.h"
#include <sstream>
#include <algorithm> 
#include <cmath>
#include "Rectangulo.h"
#include "Sprite.h"

using namespace std;

namespace constantes_jugador
{
    const float VELOCIDAD_CAMINAR = 0.2f;
}

class Ventana;

class Jugador : public Animacion
{
private:
    float _dx, _dy;

    Direccion _frente;
public:
    Jugador() {}
    Jugador(Ventana &ventana, float x,  float y);
    void dibujar(Ventana &ventana);
    void actualizar(float tiempoTranscurrido);

    void moveLeft();
    void moveRight();
    void stopMoving();

    virtual void hacerAnimacion(string animacionAct);
    virtual void confAnimaciones();

    void manejarColisiones(vector<Rectangulo> &otros);
};
