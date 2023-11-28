#ifndef GLOBALES_HPP
#define GLOBALES_HPP

#pragma once

#include <SDL2/SDL.h>
using namespace std;

namespace globales{

    const int ALTURA_VENTANA = 480;
    const int ANCHO_VENTANA = 640;

    const float ESCALA_SPRITE = 2.0f;
}

enum Direccion
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

namespace lados{
    enum Lado{
        ARRIBA,
        ABAJO,
        IZQUIERDO,
        DERECHO,
        NINGUNO
    };

    const inline Lado ladoOpuesto (Lado lado) {
        return
            lado == ARRIBA ? ABAJO :
            lado == ABAJO ? ARRIBA :
            lado == IZQUIERDO ? DERECHO :
            lado == DERECHO ? IZQUIERDO :
            ARRIBA;
    }

}

struct Vector2{
    int x, y;
    Vector2():
    x(0), y(0)
    {}
    Vector2(int x, int y):
    x(x), y(y)
    {}
    static Vector2 zero(){
        return Vector2(0, 0);
    }

};

#endif