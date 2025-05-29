#include <iostream>
#include "./CellularAutomaton/cellularAutomaton.h"
#include "./DiamondSquare/diamondSquare.h"
#include <iomanip>
#include <glm/vec2.hpp>
#include <glm/gtc/noise.hpp>

using namespace std;

void printMap(CellularAutomaton &automaton)
{
    vector<vector<int>> *map = automaton.getMap();
    unsigned int width = automaton.getWidth();
    unsigned int height = automaton.getHeight();

    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            switch ((*map)[x][y])
            {
            case 0:
                cout << '.';
                break;
            case 1:
                cout << '#';
                break;
            default:
                cout << (*map)[x][y] ;
                break;
            }
        }
        cout << '\n';
    }
}

void print_matrix(const std::vector<std::vector<float>>& matrix) {
    for (const auto& row : matrix) {
        for (float value : row) {
            std::cout << std::setw(8) << std::fixed << std::setprecision(2) << value << " ";
        }
        std::cout << '\n';
    }
}

int main()
{
    // DiamondSquareMap e(12);
    // cout << "EEEEEE" << endl;
    // e.generate();
    // print_matrix(e.value);

    // std::cout << std::endl << std::endl << e.size << std::endl;
    unsigned int width = 100;
    unsigned int height = 50;

    CellularAutomaton automaton(width, height);
    automaton.generate(60, 6, 2, 4, 4);
    printMap(automaton);

    return 0;
}
