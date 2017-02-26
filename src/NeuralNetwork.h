#pragma once

#include <QVector>
#include "Layer.h"

const unsigned int IMG_SIZE = 28;
const unsigned int IMG_PIXELS = IMG_SIZE*IMG_SIZE;

// sadly we don't have renderer for Qt types, but they are nicer .___.
#define NeuroVector std::vector
// don't know why, but it not works(. _. )
//#define NeuroVector QVector

class NeuralNetwork {
public:
    NeuroVector<Layer> layers;

    NeuroVector<vector<float>> deltas;

    void process(NeuroVector<float> inputData);

    NeuroVector<float> output();

    NeuralNetwork(unsigned int inputSize, const NeuroVector<unsigned int>& sizesVec);

    void train(int expect, vector<float> x, float alpha);
};


