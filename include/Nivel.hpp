#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "Ventana.hpp"
#include "Globales.hpp"

using namespace std;
struct SDL_Texture;

class Nivel
{
private:
    string _nombreMapa;
    Vector2 _puntoSpawn;
    Vector2 _tamanyo;

    SDL_Texture* _texturaFondo;
    void CargarMapa(string nombreMapa, Ventana &ventana);

public:
    Nivel(string nombreMapa, Vector2 puntoSpawn, Ventana &Ventana);
    ~Nivel();

    void ActualizarMapa(int lapso);
    void Dibujar(Ventana &ventana);
};

Nivel::Nivel(string nombreMapa, Vector2 puntoSpawn, Ventana &Ventana):

_nombreMapa(nombreMapa), 
_puntoSpawn(puntoSpawn),
_tamanyo(Vector2(0,0))

{
    this->CargarMapa(nombreMapa, Ventana);
}

void Nivel::CargarMapa(string nombreMapa, Ventana &ventana){
    this->_texturaFondo = SDL_CreateTextureFromSurface(ventana.GetRenderer)

}