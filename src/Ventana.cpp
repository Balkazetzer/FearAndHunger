#include "../include/Ventana.h"
#include "../include/Globales.h"

Ventana::Ventana(/* args */)
{
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &this->mainVentana, &this->mainSuperficie);
    SDL_SetWindowTitle(this->mainVentana, "Fear and Hunger");
}

Ventana::~Ventana()
{
    for(auto &sprite : _sprites) {
        SDL_FreeSurface(sprite.second);
    }
    if(this->mainSuperficie != nullptr) {
        SDL_DestroyRenderer(this->mainSuperficie);
        this->mainSuperficie = nullptr;
    }
    if(this->mainVentana != nullptr) {
        SDL_DestroyWindow(this->mainVentana);
        this->mainVentana = nullptr;
    }
}

SDL_Surface *Ventana ::cargarImagen(const string &path)
{
    if (this->_sprites.count(path) == 0)
    {
        this->_sprites[path] = IMG_Load(path.c_str());
        if (this->_sprites[path] == NULL)
        {
            printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
            return nullptr; // return nullptr if image loading fails
        }
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
