#pragma once

#include <SDL2/SDL.h>
using namespace std;

namespace globales{

    const int ALTURA_VENTANA = 480;
    const int ANCHO_VENTANA = 640;

    const float ESCALA_SPRIDE = 2.0f;
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