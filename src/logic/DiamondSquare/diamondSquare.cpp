#include "diamondSquare.h"
#include <iostream>
#include <algorithm>
#include <complex>
#include <random>

DiamondSquareMap::DiamondSquareMap(int loop) : loop{loop}, initialDisplacement{1}, displacementDivision{2} {}
DiamondSquareMap::DiamondSquareMap(int loop, float initialDisplacement, float displacementDivision) : loop{loop}, initialDisplacement{initialDisplacement}, displacementDivision{displacementDivision} {}

float random_float(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

float clampW(float val, float minActu, float maxActu, float minCible, float maxCible)
{
    if (minActu > maxActu)
        std::swap(minActu, maxActu);
    if (minCible > maxCible)
        std::swap(minCible, maxCible);

    val = std::clamp(val, minActu, maxActu);

    float scale = (maxCible - minCible) / (maxActu - minActu);
    return minCible + (val - minActu) * scale;
}

void DiamondSquareMap::crop()
{
    for (size_t columnIndex = 0; columnIndex < size; columnIndex++)
    {
        for (size_t rowIndex = 0; rowIndex < size; rowIndex++)
        {
            value[columnIndex][rowIndex] = std::max(.0f, std::min(1.f, value[columnIndex][rowIndex]));
        }
    }
}

void DiamondSquareMap::clamp()
{
    float minValue = getMinValue();
    float maxValue = getMaxValue();

    for (size_t columnIndex = 0; columnIndex < size; columnIndex++)
    {
        for (size_t rowIndex = 0; rowIndex < size; rowIndex++)
        {
            value[columnIndex][rowIndex] = clampW(value[columnIndex][rowIndex], minValue, maxValue, 0, 1);
        }
    }
}

float DiamondSquareMap::getMaxValue()
{
    float maxValue = 0;
    for (size_t x = 0; x < value.size(); x++)
    {
        for (size_t y = 0; y < value[0].size(); y++)
        {
            if (value[x][y] > maxValue)
            {
                maxValue = value[x][y];
            }
        }
    }

    return maxValue;
}

float DiamondSquareMap::getMinValue()
{
    float minValue = 1;
    for (size_t x = 0; x < value.size(); x++)
    {
        for (size_t y = 0; y < value[0].size(); y++)
        {
            if (value[x][y] < minValue)
            {
                minValue = value[x][y];
            }
        }
    }

    return minValue;
}

void DiamondSquareMap::generate()
{
    (*this).size = std::pow(2, (loop - 1)) * 2 - (std::pow(2, (loop - 1)) - 1);

    // INIT TO 0
    for (size_t columnIndex = 0; columnIndex < (*this).size; columnIndex++)
    {
        value.push_back({});
        for (size_t rowIndex = 0; rowIndex < (*this).size; rowIndex++)
        {
            value[columnIndex].push_back(0);
        }
    }

    // PUT INITIAL VALUE
    float initialValue{random_float(0, 1)};
    value[0][0] = initialValue;
    value[0][(*this).size - 1] = initialValue;
    value[(*this).size - 1][0] = initialValue;
    value[(*this).size - 1][(*this).size - 1] = initialValue;

    int gap = ((*this).size - 1) / 2;

    float displacement = initialDisplacement;

    for (size_t subdIndex = 1; subdIndex < loop; subdIndex++)
    {

        // DIAMOND
        for (size_t columnIndex = gap; columnIndex < (*this).size - 1; columnIndex += gap * 2)
        {
            for (size_t rowIndex = gap; rowIndex < (*this).size - 1; rowIndex += gap * 2)
            {

                // AVERAGE + DISPLACEMENT
                value[columnIndex][rowIndex] =
                    ((value[columnIndex - gap][rowIndex - gap] +
                      value[columnIndex - gap][rowIndex + gap] +
                      value[columnIndex + gap][rowIndex - gap] +
                      value[columnIndex + gap][rowIndex + gap]) /
                     4) +
                    random_float(-displacement, displacement);
            }
        }

        // SQUARE HORIZONTAL

        for (long long columnIndex = gap; columnIndex <= (*this).size - 1; columnIndex += gap * 2)
        {
            for (long long rowIndex = 0; rowIndex <= (*this).size - 1; rowIndex += gap * 2)
            {

                float total = 0;
                int count = 0;
                if (columnIndex - gap >= 0)
                {
                    count++;
                    total += value[columnIndex - gap][rowIndex];
                }
                if (rowIndex + gap <= (*this).size - 1)
                {
                    count++;
                    total += value[columnIndex][rowIndex + gap];
                }
                if (rowIndex - gap >= 0)
                {
                    count++;
                    total += value[columnIndex][rowIndex - gap];
                }
                if (columnIndex + gap <= (*this).size - 1)
                {
                    count++;
                    total += value[columnIndex + gap][rowIndex];
                }

                value[columnIndex][rowIndex] = total / count + random_float(-displacement, displacement);
            }
        }

        // SQUARE VERTICAL
        for (long long columnIndex = 0; columnIndex <= (*this).size - 1; columnIndex += gap * 2)
        {
            for (long long rowIndex = gap; rowIndex <= (*this).size - 1; rowIndex += gap * 2)
            {

                float total = 0;
                int count = 0;
                if (columnIndex - gap >= 0)
                {
                    count++;
                    total += value[columnIndex - gap][rowIndex];
                }
                if (rowIndex + gap <= (*this).size - 1)
                {
                    count++;
                    total += value[columnIndex][rowIndex + gap];
                }
                if (rowIndex - gap >= 0)
                {
                    count++;
                    total += value[columnIndex][rowIndex - gap];
                }
                if (columnIndex + gap <= (*this).size - 1)
                {
                    count++;
                    total += value[columnIndex + gap][rowIndex];
                }

                value[columnIndex][rowIndex] = total / count + random_float(-displacement, displacement);
            }
        }

        displacement /= displacementDivision;
        gap = gap / 2;
    }
}

void DiamondSquareMap::setInitialDisplacement(float value)
{
    (*this).initialDisplacement = value;
}

void DiamondSquareMap::setDisplacementDivision(float value)
{
    (*this).displacementDivision = value;
}

void DiamondSquareMap::setLoop(int value)
{
    (*this).loop = value;
}

float DiamondSquareMap::getInitialDisplacement()
{
    return (*this).initialDisplacement;
}

float DiamondSquareMap::getDisplacementDivision()
{
    return (*this).displacementDivision;
}

int DiamondSquareMap::getLoop()
{
    return (*this).loop;
}