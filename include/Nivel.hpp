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
    Nivel(string nombreMapa, Vector2 puntoSpawn, Ventana &ventana);
    ~Nivel();

    void ActualizarMapa(int lapso);
    void Dibujar(Ventana &ventana);
};

Nivel::Nivel(string nombreMapa, Vector2 puntoSpawn, Ventana &ventana):

_nombreMapa(nombreMapa), 
_puntoSpawn(puntoSpawn),
_tamanyo(Vector2(0,0))

{
    this->CargarMapa(nombreMapa, ventana);
}

Nivel::~Nivel(){
    // Aquí puedes liberar cualquier recurso que hayas asignado en Nivel
}

void Nivel::CargarMapa(string nombreMapa, Ventana &ventana){
    this->_texturaFondo = SDL_CreateTextureFromSurface(ventana.GetRenderer(), ventana.cargarImagen("assets/backgrounds/!floor_1.png"));
    this->_tamanyo = Vector2(1280,960);

    // Aquí puedes agregar un mensaje de error o de registro para verificar si la textura se cargó correctamente
}

void Nivel::ActualizarMapa(int lapso){
    // Implementa este método si es necesario
}

void Nivel::Dibujar(Ventana &ventana){
    SDL_Rect rectfuente = {0, 0, 576, 384};
    SDL_Rect destRect;
    for(int x = 0; x<this->_tamanyo.x/64; x++){
        for(int y = 0; y<this->_tamanyo.y/64; y++){
            destRect.x = x *64;
            destRect.y = y*64;
            destRect.w = 64;
            destRect.h = 64;
            ventana.blitSuperficie(this->_texturaFondo, &rectfuente, &destRect);
        }
    }
}
