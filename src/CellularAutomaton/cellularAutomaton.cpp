#include "cellularAutomaton.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

void CellularAutomaton::printMap()
{
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            std::cout << (map[x][y] == 1 ? '#' : '.');
        }
        std::cout << "\n";
    }
}

CellularAutomaton::CellularAutomaton(unsigned int width, unsigned int height)
    : width{width}, height{height}
{
    srand(static_cast<unsigned int>(time(nullptr))); // Initialisation RNG
}

int CellularAutomaton::getValue(unsigned int x, unsigned int y)
{
    return map[x][y];
}

vector<vector<int>> *CellularAutomaton::getMap()
{
    return &map;
}

void CellularAutomaton::setWidth(unsigned int width)
{
    this->width = width;
}

unsigned int CellularAutomaton::getWidth()
{
    return width;
}

void CellularAutomaton::setHeight(unsigned int height)
{
    this->height = height;
}

unsigned int CellularAutomaton::getHeight()
{
    return height;
}

/*
    chanceToStartAlive sets how dense the initial grid is with living cells.
    starvationLimit is the lower neighbour limit at which cells start dying.
    overpopLimit is the upper neighbour limit at which cells start dying.
    birthNumber is the number of neighbours that cause a dead cell to become alive.
    numberOfSteps is the number of times we perform the simulation step.
*/
void CellularAutomaton::generate(int chanceToStartAlive, unsigned int numberOfSteps, unsigned int starvationLimit, unsigned int overpopLimit, unsigned int birthNumber)
{
    srand(static_cast<unsigned>(time(0)));

    // Initialisation aléatoire
    map = vector<vector<int>>(width, vector<int>(height, 0));
    for (unsigned int x = 0; x < width; ++x)
    {
        for (unsigned int y = 0; y < height; ++y)
        {
            map[x][y] = (rand() % 100 < chanceToStartAlive) ? 1 : (rand() % 100 < 70) ? 0
                                                                                      : 3;
        }
    }

    for (size_t i = 0; i < numberOfSteps; i++)
    {
        step();
    }
}

void CellularAutomaton::step()
{
    vector<vector<int>> newMap = map;

    for (unsigned int x = 0; x < width; ++x)
    {
        for (unsigned int y = 0; y < height; ++y)
        {
            int filled = countNeighbors(x, y, 1, {1,2});
            int distantFilled = countNeighbors(x, y, 3, {1, 2});
            int moutainCount = countNeighbors(x, y, 1, {3});

            // if (newMap[x][y] != -1)
            // {
                if (moutainCount >= 3)
                {
                    newMap[x][y] = 3; 
                } else if

                 (distantFilled >= 40)
                {
                    newMap[x][y] = 2;
                }
                else if (filled >= 5)
                {
                    newMap[x][y] = 1;
                }
                else
                {
                    newMap[x][y] = 0;
                }

                
            // }
        }
    }

    map = newMap;
}

int CellularAutomaton::countNeighbors(int x, int y, int dist, vector<int> valueToSearch)
{
    int count = 0;

    for (int dx = -dist; dx <= dist; ++dx)
    {
        for (int dy = -dist; dy <= dist; ++dy)
        {
            if (dx == 0 && dy == 0)
                continue;

            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < static_cast<int>(width) &&
                ny >= 0 && ny < static_cast<int>(height))
            {
                if (std::find(valueToSearch.begin(), valueToSearch.end(),  map[nx][ny]) != valueToSearch.end())
                {
                    ++count;
                }
            }
        }
    }

    return count;
}
