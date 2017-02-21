#pragma once

#include <QVector>

class Neuron{
    QVector<float> coeff;
    float bias;
public:
    float f(QVector<float> t);
    Neuron();
};

class NeuralNetwork {
    QVector<QVector<Neuron>> layers;
public:
    NeuralNetwork();
    QVector<float> input(QVector<float> img);
};


