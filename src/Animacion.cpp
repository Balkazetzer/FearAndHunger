#include "../include/Animacion.h"
#include "../include/Globales.h"
#include "../include/Sprite.h"
#include "../include/Ventana.h"
#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>
using namespace std;



Animacion::Animacion() {}

Animacion::Animacion(Ventana &ventana, const string &path, int sourceX, int sourceY, int ancho, int altura, float posX, int posY, float tiempoAct)
        : Sprite(ventana, path, sourceX, sourceY, ancho, altura, posX, posY),
            _tiempoAct(tiempoAct),
            _animacionActualOnce(false),
            _animacionAct(""),
            _indiceCuadro(0),
            _visible(true)
{
}


void Animacion::agregarAnimacion(int cuadros, int x, int y, string name, int ancho, int altura, Vector2 offset)
{
    vector<SDL_Rect> rectangulos;
    for (int i = 0; i < cuadros; i++)
    {
        SDL_Rect newRect = {(i + x) * ancho, y, ancho, altura};
        rectangulos.push_back(newRect);
    }
    this->_animaciones.insert(pair<string, vector<SDL_Rect>>(name, rectangulos));
    this->_offsets.insert(pair<string, Vector2>(name, offset));
}

void Animacion::restablecerAnimacion()
{
    this->_animaciones.clear();
    this->_offsets.clear();
}

void Animacion::comenzarAnimacion(string animacion, bool once)
{
    this->_animacionActualOnce = once;
    if (this->_animacionAct != animacion)
    {
        this->_animacionAct = animacion;
        this->_indiceCuadro = 0;
    }
}

void Animacion::establecerVisible(bool visible)
{
    this->_visible = visible;
}

void Animacion::detenerAnimacion()
{
    this->_indiceCuadro = 0;
    this->hacerAnimacion(this->_animacionAct);
}

void Animacion::actualizar(int tiempoTranscurrido)
{
    Sprite::actualizar();

    this->_tiempoTranscurrido += tiempoTranscurrido;
    if (this->_tiempoTranscurrido > this->_tiempoAct)
    {
        this->_tiempoTranscurrido -= this->_tiempoAct;
        if (this->_indiceCuadro < this->_animaciones[this->_animacionAct].size() - 1)
        {
            
            this->_indiceCuadro++;
        }
        else
        {
            if (this->_animacionActualOnce == true)
            {
                this->_indiceCuadro = 0;
                this->hacerAnimacion(this->_animacionAct);
            }
        }
    }
}

void Animacion::dibujar(Ventana &ventana, int x, int y)
{
    if (this->_visible)
    {
        SDL_Rect rectanguloDest;
        rectanguloDest.x = x + this->_offsets[this->_animacionAct].x;
        rectanguloDest.y = y + this->_offsets[this->_animacionAct].y;
        rectanguloDest.w = this->_sourceRect.w * globales::ESCALA_SPRITE;
        rectanguloDest.h = this->_sourceRect.h * globales::ESCALA_SPRITE;

        SDL_Rect sourceRect = this->_animaciones[this->_animacionAct][this->_indiceCuadro];
        ventana.blitSuperficie(this->_spriteSheet, &sourceRect, &rectanguloDest);
    }
}

void Animacion::hacerAnimacion(string animacionActual)
{
}

void Animacion::confAnimaciones()
{
    this->agregarAnimacion(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
    this->agregarAnimacion(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
}