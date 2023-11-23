#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "Ventana.hpp"

using namespace std;

class Nivel
{
private:
    /* data */
public:
    Nivel(string Mapname, Ventana &Ventana);
    ~Nivel();
};

