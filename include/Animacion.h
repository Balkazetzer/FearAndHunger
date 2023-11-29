#ifndef ANIMACION_H
#define ANIMACION_H



#pragma once
#include <SDL2/SDL.h>
#include "Globales.h"
#include "Sprite.h"
#include "Ventana.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

class Ventana;

class Animacion : public Sprite
{
protected:
    double _tiempoAct;
    bool _animacionActualOnce;
    string _animacionAct;

    void agregarAnimacion(int cuadros, int x, int y, string nombre, int ancho, int altura, Vector2 offset);

    void restablecerAnimacion();

    void detenerAnimacion();

    void establecerVisible(bool visible);

    virtual void hacerAnimacion(string animacionActual);

protected:
    map<string, vector<SDL_Rect>> _animaciones;
    map<string, Vector2> _offsets;

    size_t _indiceCuadro;
    double _tiempoTranscurrido;
    bool _visible;

public:
    Animacion();
    Animacion(Ventana &ventana, const string &path, int sourceX, int sourceY, int ancho, int altura, float posX, int posY, float tiempoAct);

    void comenzarAnimacion(string animacion, bool once = false);

    void actualizar(int tiempoTranscurrido);

    void dibujar(Ventana &ventana, int x, int y);

    virtual void confAnimaciones();
};

#endif