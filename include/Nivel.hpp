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
#include "Rectangulo.hpp"
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
    Nivel(string nombreMapa, Vector2 puntoSpawn, Ventana &ventana);
    ~Nivel();

    void ActualizarMapa(int lapso);
    void Dibujar(Ventana &ventana);
    vector<Rectangulo> checkColisiones(Rectangulo otro);
    const Rectangulo getContorno() const;
    const lados::Lado getLadoColision(const Rectangulo &otro) const;
};

Nivel::Nivel(string nombreMapa, Vector2 puntoSpawn, Ventana &ventana)
{
    this->CargarMapa(nombreMapa, ventana);
}

Nivel::~Nivel()
{
}

#include <stdexcept>

void Nivel::CargarMapa(string nombreMapa, Ventana &ventana)
{

    XMLDocument doc;
    stringstream ss;
    ss << "assets/tilesets/" << nombreMapa << ".tsx";
    doc.LoadFile(ss.str().c_str());

    XMLElement *nodoTileset = doc.FirstChildElement("tileset");

    int anchuraRecuadro, alturaRecuadro;
    nodoTileset->QueryIntAttribute("tilewidth", &anchuraRecuadro);
    nodoTileset->QueryIntAttribute("tileheight", &alturaRecuadro);
    this->_tamanyoRecuadro = Vector2(anchuraRecuadro, alturaRecuadro);

    XMLElement *nodoImagen = nodoTileset->FirstChildElement("image");
    const char *fuente = nodoImagen->Attribute("source");
    stringstream ssFuente;
    ssFuente << "assets/tilesets/" << fuente;
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ventana.GetRenderer(), ventana.cargarImagen(ssFuente.str()));

    this->_recuadrosSet.push_back(cuadSet(tex, 1));

    // XMLDocument doc;
    // stringstream ss;
    // string nombreMapa;
    // ss << "assets/maps/" << nombreMapa << ".tmx";
    // doc.LoadFile(ss.str().c_str());

    XMLElement *nodoMapa = doc.FirstChildElement("map");
    // int altura, anchura;
    // nodoMapa->QueryIntAttribute("width", &anchura);
    // nodoMapa->QueryIntAttribute("height", &altura);
    // this->_tamanyo = Vector2(anchura, altura);

    // int anchuraRecuadro, alturaRecuadro;
    // nodoMapa->QueryIntAttribute("tilewidth", &anchuraRecuadro);
    // nodoMapa->QueryIntAttribute("tileheight", &alturaRecuadro);
    // this->_tamanyoRecuadro = Vector2(anchuraRecuadro, alturaRecuadro);

    // XMLElement *nodoImagen = nodoMapa->FirstChildElement("tileset");
    // if (nodoImagen == NULL)
    // {
    //     while (nodoImagen)
    //     {
    //         int primerCuadro;
    //         const char *fuente = nodoImagen->FirstChildElement("image")->Attribute("source");
    //         char *path;
    //         nodoImagen->QueryIntAttribute("firstgid", &primerCuadro);
    //         nodoImagen = nodoImagen->NextSiblingElement("tileset");
    //         stringstream ss;

    //         ss << "assets/tilesets/" << fuente;
    //         nodoImagen->QueryIntAttribute("primercuadro", &primerCuadro);
    //         SDL_Texture *tex = SDL_CreateTextureFromSurface(ventana.GetRenderer(), ventana.cargarImagen(ss.str()));

    //         this->_recuadrosSet.push_back(cuadSet(tex, primerCuadro));
    //     }
    // }

    // XMLElement *nodoCapa = nodoMapa->FirstChildElement("layer");
    // if (nodoCapa != NULL)
    // {
    //     while (nodoCapa)
    //     {
    //         XMLElement *nodoDatos = nodoCapa->FirstChildElement("data");
    //         if (nodoDatos != NULL)
    //         {

    //             while (nodoDatos)
    //             {
    //                 XMLElement *nodoRecuadro = nodoDatos->FirstChildElement("tile");
    //                 if (nodoRecuadro != NULL)
    //                 {
    //                     int recContador = 0;
    //                     while (nodoRecuadro)
    //                     {
    //                         if (nodoRecuadro->IntAttribute("gid") == 0)
    //                         {
    //                             recContador++;
    //                             if (nodoRecuadro->NextSiblingElement("tile"))
    //                             {
    //                                 nodoRecuadro = nodoRecuadro->NextSiblingElement("tile");
    //                                 continue;
    //                             }
    //                             else
    //                             {

    //                                 break;
    //                             }
    //                         }

    //                         int gid = nodoRecuadro->IntAttribute("gid");
    //                         cuadSet recs;
    //                         for (int i = 0; i < this->_recuadrosSet.size(); i++)
    //                         {
    //                             if (this->_recuadrosSet[i].primerCuadro <= gid)
    //                             {

    //                                 recs = this->_recuadrosSet.at(i);
    //                                 break;
    //                             }
    //                         }

    //                         if (recs.primerCuadro == -1)
    //                         {

    //                             recContador++;
    //                             if (nodoRecuadro->NextSiblingElement("title"))
    //                             {
    //                                 nodoRecuadro = nodoRecuadro->NextSiblingElement("tile");
    //                                 continue;
    //                             }
    //                             else
    //                             {
    //                                 break;
    //                             }
    //                         }

    //                         int xx = 0;
    //                         int yy = 0;
    //                         xx = recContador % anchura;
    //                         xx *= anchuraRecuadro;
    //                         yy += alturaRecuadro * (recContador / anchura);
    //                         Vector2 posRecFinal = Vector2(xx, yy);

    //                         int recSetAnchura, recSetAltura;
    //                         SDL_QueryTexture(recs.textura, NULL, NULL, &recSetAnchura, &recSetAltura);
    //                         int tsxx = (gid % (recSetAnchura/ recSetAltura)) ? 1 : 0;
    //                         tsxx *= recSetAltura;
    //                         int tsyy = 0;

    //                         Vector2 posRecSet = Vector2(tsxx, tsyy);
    //                         Recuadros rec(recs.textura, Vector2(recSetAnchura, recSetAltura), posRecFinal, posRecFinal);
    //                         this->_recuadrosLista.push_back(rec);
    //                         recContador++;
    //                         nodoRecuadro = nodoRecuadro->NextSiblingElement("tile");
    //                     }
    //                 }
    //             }

    //             nodoDatos = nodoDatos->NextSiblingElement("tile");
    //         }
    //         nodoCapa = nodoCapa->NextSiblingElement("layer");
    //     }
    // }

    // Colisiones

    XMLElement *nodoObjetoGrupo = nodoMapa->FirstChildElement("objectgroup");
    if (nodoObjetoGrupo != NULL)
    {
        while (nodoObjetoGrupo)
        {
            const char *nombreObjeto = nodoObjetoGrupo->Attribute("name");
            stringstream ss;
            ss << nombreObjeto;
            if (ss.str() == "colisones")
            {
                XMLElement *nodoObjeto = nodoObjetoGrupo->FirstChildElement("object");
                if (nodoObjeto != NULL)
                {
                    while (nodoObjeto)
                    {
                        float x, y, ancho, alto;
                        x = nodoObjeto->FloatAttribute("x");
                        y = nodoObjeto->FloatAttribute("y");
                        ancho = nodoObjeto->FloatAttribute("width");
                        alto = nodoObjeto->FloatAttribute("height");
                        this->_colisiones.push_back(Rectangulo(x, y, ancho, alto));
                        nodoObjeto = nodoObjeto->NextSiblingElement("object");
                    }
                }
            }

            nodoObjetoGrupo = nodoObjetoGrupo->NextSiblingElement("objectgroup");
        }
    }
}

void Nivel::ActualizarMapa(int lapso)
{
}

void Nivel::Dibujar(Ventana &ventana)
{
    for (int i = 0; i < this->_recuadrosLista.size(); i++)
    {
        this->_recuadrosLista.at(i).Dibujar(ventana);
    }
}

vector<Rectangulo> Nivel::checkColisiones(Rectangulo otro)
{
    vector<Rectangulo> otros;
    for (int i = 0; i < this->_colisiones.size(); i++)
    {
        if (this->_colisiones.at(i).intersectaCon(otro))
        {
            otros.push_back(this->_colisiones.at(i));
        }
    }
    return otros;
}

#endif