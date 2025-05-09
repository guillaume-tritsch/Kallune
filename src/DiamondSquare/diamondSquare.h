#pragma once

#include <iostream>
#include <vector>

class DiamondSquareMap
{
public:
    std::vector<std::vector<float>> value;
    int size;

    void clamp();
    void crop();
    void generate();

    // constructor
    DiamondSquareMap(int);
    DiamondSquareMap(int, float, float);

    // get & set
    void setInitialDisplacement(float);
    void setDisplacementDivision(float);
    void setLoop(int);

    float getInitialDisplacement();
    float getDisplacementDivision();
    int getLoop();

    float getMinValue();
    float getMaxValue();

private:
    float initialDisplacement;
    float displacementDivision;
    int loop;
};