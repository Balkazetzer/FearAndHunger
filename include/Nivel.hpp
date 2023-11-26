#ifndef NIVEL_HPP
#define NIVEL_HPP

#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "Ventana.hpp"
#include "Recuadros.hpp"
#include "Globales.hpp"
#include "tinyxml2.h"
#include <sstream>
#include <algorithm>
#include <cmath>
#include <conio.h>
#include <stdexcept>
#include <vector>

using namespace std;
using namespace tinyxml2;


struct SDL_Texture;

class Nivel
{
private:
    string _nombreMapa;
    Vector2 _puntoSpawn;
    Vector2 _tamanyo;
    Vector2 _tamanyoRecuadro;

    SDL_Texture *_texturaFondo;

    vector<Recuadros> _recuadrosListaDe;
    vector<Recuadros> _recuadrosSet;

    void CargarMapa(string nombreMapa, Ventana &ventana);

    struct rectSet
    {
        SDL_Texture *textura;
        int primerCuadro;

        rectSet()
        {
            this->primerCuadro = -1;
        }

        rectSet(SDL_Texture *textura, int primerCuadro)
        {
            this->textura = textura;
            this->primerCuadro = primerCuadro;
        }
    };

public:
    Nivel(string nombreMapa, Vector2 puntoSpawn, Ventana &ventana);
    ~Nivel();

    void ActualizarMapa(int lapso);
    void Dibujar(Ventana &ventana);
};

Nivel::Nivel(string nombreMapa, Vector2 puntoSpawn, Ventana &ventana)
{
    this->CargarMapa(nombreMapa, ventana);
}

Nivel::~Nivel()
{
}

#include <stdexcept>

#include <stdexcept>

void Nivel::CargarMapa(string nombreMapa, Ventana &ventana)
{
    XMLDocument doc;
    stringstream ss;
    string nombreMapa;
    ss << "assets/maps/" << nombreMapa << ".tmx";
    doc.LoadFile(ss.str().c_str());

    XMLElement *nodoMapa = doc.FirstChildElement("map");
    int altura, anchura;
    nodoMapa->QueryIntAttribute("width", &anchura);
    nodoMapa->QueryIntAttribute("height", &altura);
    this->_tamanyo = Vector2(anchura, altura);

    int anchuraRecuadro, alturaRecuadro;
    nodoMapa->QueryIntAttribute("tilewidth", &anchuraRecuadro);
    nodoMapa->QueryIntAttribute("tileheight", &alturaRecuadro);
    this->_tamanyoRecuadro = Vector2(anchuraRecuadro, alturaRecuadro);

    XMLElement *nodoImagen = nodoMapa->FirstChildElement("tileset");
    if(nodoImagen == NULL) {
        while(nodoImagen){
            int primerCuadro;
            const char fuente = *nodoImagen->FirstChildElement("image")->Attribute("source");
            char *path;
            nodoImagen->QueryIntAttribute("firstgid", &primerCuadro);
            nodoImagen = nodoImagen->NextSiblingElement("tileset");
            stringstream ss;

            ss << "assets/tilesets/"  << fuente;
            nodoImagen->QueryIntAttribute("primercuadro", &primerCuadro);
            SDL_Texture *tex = SDL_CreateTextureFromSurface(ventana.GetRenderer(), ventana.cargarImagen(ss.str()));

            this->_recuadrosSet.push_back(rectSet(tex, primerCuadro));
        }
    }

    XMLElement *nodoCapa = nodoMapa->FirstChildElement("layer");
    if(nodoCapa != NULL){
        while(nodoCapa){
            XMLElement *nodoDatos = nodoCapa->FirstChildElement("data");
            if(nodoDatos != NULL){
                
                nodoDatos = nodoDatos->NextSiblingElement("tile");
            }
            nodoCapa = nodoCapa->NextSiblingElement("layer");
        }
    }

}

void Nivel::ActualizarMapa(int lapso)
{
}

void Nivel::Dibujar(Ventana &ventana)
{
    SDL_Rect rectfuente = {0, 0, 68, 68};
    SDL_Rect destRect;
    for (int x = 0; x < this->_tamanyo.x / 68; x++)
    {
        for (int y = 0; y < this->_tamanyo.y / 68; y++)
        {
            destRect.x = x * 68 * globales::ESCALA_SPRITE;
            destRect.y = y * 68 * globales::ESCALA_SPRITE;
            destRect.w = 68 * globales::ESCALA_SPRITE;
            destRect.h = 68 * globales::ESCALA_SPRITE;
            ventana.blitSuperficie(this->_texturaFondo, &rectfuente, &destRect);
        }
    }
}

#endif