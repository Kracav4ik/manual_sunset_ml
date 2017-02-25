#pragma once

#include <QVector>
#include "Layer.h"

const int IMG_SIZE = 28;
const int IMG_PIXELS = IMG_SIZE*IMG_SIZE;

// sadly we don't have renderer for Qt types, but they are nicer .___.
//#define NeuroVector std::vector
#define NeuroVector QVector

class Neuron{
    NeuroVector<float> coeff;
    float bias;
public:
    float f(const NeuroVector<float>& t) const;
    Neuron(int inputs);
    Neuron();
    Matrix m;
};

class NeuralNetwork {
    typedef NeuroVector<Neuron> Layer;
    NeuroVector<Layer> layers;
public:
    NeuralNetwork(int hiddenSize, int outputSize);
    NeuroVector<float> input(const NeuroVector<float>& img);
};


