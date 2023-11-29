#include "../include/Nivel.h"
#include "../include/Ventana.h"

Nivel::Nivel()
{
}
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
    ss << "assets/tilesets/" << nombreMapa << ".xml";
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

    SDL_Surface *surface = ventana.cargarImagen(ssFuente.str());
    if (surface == nullptr)
    {
        std::cerr << "Failed to load image: " << ssFuente.str() << std::endl;
        return;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ventana.GetRenderer(), surface);

    this->_recuadrosSet.push_back(cuadSet(tex, 1));

    XMLElement *nodoMapa = doc.FirstChildElement("map");

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
    for (size_t i = 0; i < this->_recuadrosLista.size(); i++)
    {
        this->_recuadrosLista.at(i).Dibujar(ventana);
    }
}

vector<Rectangulo> Nivel::checkColisiones(Rectangulo otro)
{
    vector<Rectangulo> otros;
    for (size_t i = 0; i < this->_colisiones.size(); i++)
    {
        if (this->_colisiones.at(i).intersectaCon(otro))
        {
            otros.push_back(this->_colisiones.at(i));
        }
    }
    return otros;
}
