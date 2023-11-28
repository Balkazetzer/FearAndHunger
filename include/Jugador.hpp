#pragma once
#include <SDL2/SDL.h>
#include "Ventana.hpp"
#include "Animacion.hpp"
#include "Globales.hpp"
#include "tinyxml2.h"
#include <sstream>
#include <algorithm> 
#include <cmath>
#include "Rectangulo.hpp"
#include "Sprite.hpp"

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

Jugador::Jugador(Ventana &ventana, float x, float y) :
    Animacion(ventana, "assets/sprites/pCahara.png", 0, 0, 16, 16, x, y, 100)
{
    ventana.cargarImagen("assets/sprites/pCahara.png");

    this->confAnimaciones();
    this->comenzarAnimacion("RunRight");
}

void Jugador::confAnimaciones()
{
    this->agregarAnimacion(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
    this->agregarAnimacion(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
    this->agregarAnimacion(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
    this->agregarAnimacion(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
}

void Jugador::hacerAnimacion(string animacionAct) {}

void Jugador::moveLeft()
{
    this->_dx = -constantes_jugador::VELOCIDAD_CAMINAR;
    this->comenzarAnimacion("RunLeft");
    this->_frente = LEFT;
}

void Jugador::moveRight()
{
    this->_dx = constantes_jugador::VELOCIDAD_CAMINAR;
    this->comenzarAnimacion("RunRight");
    this->_frente = RIGHT;
}

void Jugador::stopMoving()
{
    this->_dx = 0.0f;
    this->comenzarAnimacion(this->_frente == RIGHT ? "IdleRight" : "IdleLeft");
}


void Jugador:: manejarColisiones(vector<Rectangulo> &otros)
{
    for (int i = 0; i<otros.size(); i++){
        lados::Lado ladoColision = this->obtenerLadoColision(otros.at(i));
        if(ladoColision != lados::NINGUNO){
            switch(ladoColision){
                case lados::ARRIBA:
                    this->_y = otros.at(i).getAbajo() + 1;
                    this->_dy = 0;
                    break;
                case lados::ABAJO:
                    this->_y = otros.at(i).getArriba() - this->_contornos.getArriba() - 1;
                    this->_dy = 0;
                    break;
                case lados::IZQUIERDO:
                    this->_x = otros.at(i).getDer() + 1;
                    this->_dx = 0;
                    break;
                case lados::DERECHO:
                    this->_x = otros.at(i).getIzq() - this->_contornos.getAncho() - 1;
                    this->_dx = 0;
                    break;
            }
        }
    }
}

void Jugador::actualizar(float tiempoTranscurrido)
{
    this->_x += this->_dx * tiempoTranscurrido;
    Animacion::actualizar(tiempoTranscurrido);
}

void Jugador::dibujar(Ventana &ventana)
{
    Animacion::dibujar(ventana, this->_x, this->_y);
}

