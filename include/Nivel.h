#ifndef NIVEL_H
#define NIVEL_H

#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "Ventana.h"
#include "Recuadros.h"
#include "Globales.h"
#include "tinyxml2.h"
#include <sstream>
#include <algorithm>
#include <cmath>
#include <conio.h>
#include <stdexcept>
#include "Rectangulo.h"
#include <vector>

using namespace std;
using namespace tinyxml2;

struct SDL_Texture;
struct SDL_Rect;
struct recuadrosSet;

struct cuadSet
{
    SDL_Texture *textura;
    int primerCuadro;

    cuadSet()
    {
        this->primerCuadro = -1;
    }

    cuadSet(SDL_Texture *textura, int primerCuadro)
    {
        this->textura = textura;
        this->primerCuadro = primerCuadro;
    }
};

class Nivel
{
protected:
    string _nombreMapa;
    Vector2 _puntoSpawn;
    Vector2 _tamanyo;
    Vector2 _tamanyoRecuadro;

    SDL_Texture *_texturaFondo;

    vector<Recuadros> _recuadrosLista;
    vector<cuadSet> _recuadrosSet;
    vector<Rectangulo> _colisiones;

    void CargarMapa(string nombreMapa, Ventana &ventana);

    Vector2 _posicionRecuadro(recuadrosSet tls, int gid, int anchuraRecuadro, int alturaRecuadro);

public:
    Nivel();
    Nivel(string nombreMapa, Vector2 puntoSpawn, Ventana &ventana);
    ~Nivel();

    void ActualizarMapa(int lapso);
    void Dibujar(Ventana &ventana);
    vector<Rectangulo> checkColisiones(Rectangulo otro);
    const Rectangulo getContorno() const;
    const lados::Lado getLadoColision(const Rectangulo &otro) const;
};

#endif