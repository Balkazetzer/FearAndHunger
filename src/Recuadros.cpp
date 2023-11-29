#include "../include/Recuadros.h"
#include "../include/Globales.h"
#include "../include/Ventana.h"
#include "../include/Rectangulo.h"

void Recuadros::Actualizar(float lapso)
{

}

Recuadros::Recuadros(/* args */)
{
}

Recuadros::Recuadros(SDL_Texture *recSet, Vector2 tamanyoRecuadro, Vector2 posicionRecuadro, Vector2 posicion) : recSet(recSet),
                                                                                                                 _tamanyoRecuadro(tamanyoRecuadro),
                                                                                                                 _posicionRecuadro(posicionRecuadro),
                                                                                                                 _posicion(Vector2(posicion.x * globales::ESCALA_SPRITE, posicion.y * globales::ESCALA_SPRITE))
{
}

void Recuadros::Dibujar(Ventana &ventana)
{
    if(this->recSet != nullptr) {
        SDL_Rect rectfuente = {0, 0, static_cast<int>(this->_tamanyoRecuadro.x), static_cast<int>(this->_tamanyoRecuadro.y)};
        SDL_Rect destRect = {this->_posicion.x, this->_posicion.y, static_cast<int>(this->_tamanyoRecuadro.x * globales::ESCALA_SPRITE), static_cast<int>(this->_tamanyoRecuadro.y * globales::ESCALA_SPRITE)};
        ventana.blitSuperficie(this->recSet, &rectfuente, &destRect);
    } else {
        // handle error, for example, by logging and returning or throwing an exception
        std::cerr << "Failed to draw because texture is null" << std::endl;
        return; // or throw an exception
    }
}