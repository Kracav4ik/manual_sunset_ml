#pragma once

#include <QVector>
#include "Layer.h"

const int IMG_SIZE = 28;
const int IMG_PIXELS = IMG_SIZE*IMG_SIZE;

// sadly we don't have renderer for Qt types, but they are nicer .___.
#define NeuroVector std::vector
// don't know why, but it not works(. _. )
//#define NeuroVector QVector

class NeuralNetwork {
public:
    NeuroVector<Layer> layers;

    NeuroVector<vector<float>> deltas;

    NeuroVector<float> output();

    Layer getLast();

    NeuralNetwork(const NeuroVector<int>& countLayers, const NeuroVector<float>& img);

    void process(int expect);
};


