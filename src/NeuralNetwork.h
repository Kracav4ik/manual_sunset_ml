#pragma once

#include <QVector>
#include "Layer.h"

const unsigned int IMG_SIZE = 28;
const unsigned int IMG_PIXELS = IMG_SIZE*IMG_SIZE;


class NeuralNetwork {
public:
    std::vector<Layer> layers;

    std::vector<Vector> deltas;

    void process(Vector inputData);

    Vector output();

    NeuralNetwork(unsigned int inputSize, const std::vector<unsigned int>& sizesVec);

    void train(int expect, Vector x, float alpha);
};


