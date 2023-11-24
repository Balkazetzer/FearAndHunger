#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <map>
#include <SDL2/SDL_image.h>

using namespace std;

class Ventana
{
protected:
    // INFORMACIÓN PARA INICIALIZAR LA VENTANA
    const int SCREEN_WIDTH = 840;
    const int SCREEN_HEIGHT = 680;

    SDL_Window *mainVentana = NULL;      // Ventana de contenido
    SDL_Renderer *mainSuperficie = NULL; // Contenido base
    map<string, SDL_Surface *> _sprites;

public:
    Ventana(/* args */);
    ~Ventana();

    SDL_Surface *cargarImagen(const string &path);
    void blitSuperficie(SDL_Texture *fuente, SDL_Rect *rectFuente, SDL_Rect *rectDestino);
    void flip();
    void clear();

    SDL_Renderer *GetRenderer() const;
};

/*-----------------DEFINICION DE LAS FUNCIONES-------------*/

// CONSTRUCTOR Y DESTRUCTOR
Ventana::Ventana(/* args */)
{
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &this->mainVentana, &this->mainSuperficie);
    SDL_SetWindowTitle(this->mainVentana, "Fear and Hunger");
}

Ventana::~Ventana()
{
    SDL_DestroyWindow(this->mainVentana);
}

SDL_Surface *Ventana ::cargarImagen(const string &path)
{
    if (this->_sprites.count(path) == 0)
    {
        this->_sprites[path] = IMG_Load(path.c_str());
    }
    return this->_sprites[path];
}

void Ventana ::blitSuperficie(SDL_Texture *textura, SDL_Rect *rectFuente, SDL_Rect *rectDestino)
{
    SDL_RenderCopy(this->mainSuperficie, textura, rectFuente, rectDestino);
}

void Ventana ::flip()
{
    SDL_RenderPresent(this->mainSuperficie);
}

void Ventana::clear()
{
    SDL_RenderClear(this->mainSuperficie);
}

SDL_Renderer *Ventana ::GetRenderer() const
{

    return this->mainSuperficie;
}