#include "./map.h"

Map::Map() : width(100), height(100), generator(width, height)
{
    this->generator.generate(60, 6, 2, 4, 4);
    map = this->generator.getMap();
}

vector<vector<float>> Map::getSpeedMap() const
{
    vector<vector<float>> speedMap(width, vector<float>(height, 1.0f));

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            speedMap[x][y] = getSpeed(map[x][y]);
        }
    }

    return speedMap;
}

float Map::getSpeed(MapType type) const
{
    switch (type)
    {
    case MapType::GRASS:
        return 1.0f;
    case MapType::WALL:
        return 0.0f;
    case MapType::WATER:
        return 0.0f;
    case MapType::SAND:
        return 0.75f;
    default:
        return 1.0f; // valeur par défaut sûre
    }
}
