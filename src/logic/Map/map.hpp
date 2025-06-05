#pragma once

#include <iostream>
#include <vector>
#include "../MapGeneration/mapGeneration.hpp"
#include "utils/map.hpp"
using namespace std;

class Map
{
public:
    Map();

    // Retourne une copie de la carte des vitesses
    vector<vector<float>> getSpeedMap() const;

    // Donne la vitesse correspondant au type de case
    float getSpeed(MapType type) const;

    // Accesseurs pour la taille
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    // Accès à la map (en lecture seule)
    const vector<vector<MapType>>& getMap() const { return map; }

private:
    vector<vector<MapType>> map;
    int width;
    int height;

public:
    MapGeneration generator; // Tu peux envisager de mettre ce membre en privé et ajouter un getter si besoin
};
