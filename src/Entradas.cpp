#include "../include/Entradas.h"
#include <SDL2/SDL.h>
#include <map>
using namespace std;

Entradas::Entradas(/* args */)
{
}

Entradas::~Entradas()
{
}

void Entradas::ActualizarFrame(){
    this->_pressedKeys.clear();
    this-> _releasedKeys.clear();

}


// DETECTAR Y ACTUALIZAR POLL DE EVENTOS
void Entradas::IrArriba(const SDL_Event &evento){
    this->_pressedKeys[evento.key.keysym.scancode] = true;
    this->_heldKeys[evento.key.keysym.scancode] = true;

}

void Entradas::IrAbajo(const SDL_Event &evento){
    this->_pressedKeys[evento.key.keysym.scancode] = true;
    this->_heldKeys[evento.key.keysym.scancode] = true;

}
void Entradas::IrIzquierda(const SDL_Event &evento){
    this->_pressedKeys[evento.key.keysym.scancode] = true;
    this->_heldKeys[evento.key.keysym.scancode] = true;

}
void Entradas::IrDerecha(const SDL_Event &evento){
    this->_pressedKeys[evento.key.keysym.scancode] = true;
    this->_heldKeys[evento.key.keysym.scancode] = true;

}

// DETECTAR EVENTO EN TURNO

bool Entradas::TeclaPresionada(SDL_Scancode key){
    return this->_pressedKeys[key];
}

bool Entradas::TeclaLiberada(SDL_Scancode key){
    return this->_releasedKeys[key];
}

bool Entradas::TeclaSostenida(SDL_Scancode key){
    return this->_heldKeys[key];
}
