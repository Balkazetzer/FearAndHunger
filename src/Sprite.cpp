#include "../include/Rectangulo.h"
#include "../include/Globales.h"
#include "../include/Ventana.h"
#include "../include/Sprite.h"
#include <iostream>
#include <cmath>

Sprite::Sprite() {}
Sprite::Sprite(Ventana &ventana, const string &path, int sourceX, int sourceY, int ancho, int altura, float posX, float posY) : _x(posX), _y(posY)
{
    this->_sourceRect.x = sourceX;
    this->_sourceRect.y = sourceY;
    this->_sourceRect.w = ancho;
    this->_sourceRect.h = altura;

    SDL_Surface *surface = ventana.cargarImagen(path);
    if (surface == nullptr)
    {
        // handle error, for example, by logging and returning or throwing an exception
        std::cerr << "Failed to load image: " << path << std::endl;
        return; // or throw an exception
    }
    this->_spriteSheet = SDL_CreateTextureFromSurface(ventana.GetRenderer(), surface);
    if (this->_spriteSheet == NULL)
    {
        printf("\nError: No se puede cargar la imagen\n");
    }

    this->_contornos = Rectangulo(this->_x, this->_y, ancho * globales::ESCALA_SPRITE, altura * globales::ESCALA_SPRITE);
}

void Sprite::dibujar(Ventana &ventana, int x, int y)
{
    if(this->_spriteSheet != nullptr) {
        SDL_Rect rectanguloDestinado = {
            x,
            y,
            static_cast<int>(this->_sourceRect.w * globales::ESCALA_SPRITE + 0.5),
            static_cast<int>(this->_sourceRect.h * globales::ESCALA_SPRITE + 0.5)};
        ventana.blitSuperficie(this->_spriteSheet, &this->_sourceRect, &rectanguloDestinado);
    } else {
        // handle error, for example, by logging and returning or throwing an exception
        std::cerr << "Failed to draw because texture is null" << std::endl;
        return; // or throw an exception
    }
}

void Sprite::actualizar()
{
    this->_contornos = Rectangulo(this->_x, this->_y, this->_sourceRect.w * globales::ESCALA_SPRITE, this->_sourceRect.h * globales::ESCALA_SPRITE);
}

const Rectangulo Sprite::obtenerContornos() const
{
    return this->_contornos;
}

const lados::Lado Sprite::obtenerLadoColision(const Rectangulo &otro) const
{
    int amtRight, amtLeft, amtTop, amtBottom;
    amtRight = this->_contornos.getDer() - otro.getIzq();
    amtLeft = otro.getDer() - this->_contornos.getIzq();
    amtTop = otro.getAbajo() - this->_contornos.getArriba();
    amtBottom = this->_contornos.getAbajo() - otro.getArriba();

    int vals[4] = {abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom)};
    int lowest = vals[0];
    for (int i = 0; i < 4; i++)
    {
        if (vals[i] < lowest)
        {
            lowest = vals[i];
        }
    }

    return lowest == abs(amtRight) ? lados::DERECHO : lowest == abs(amtLeft) ? lados::IZQUIERDO
                                                  : lowest == abs(amtTop)    ? lados::ARRIBA
                                                  : lowest == abs(amtBottom) ? lados::ABAJO
                                                                             : lados::NINGUNO;
}
