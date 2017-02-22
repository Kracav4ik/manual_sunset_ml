#include "NeuralNetwork.h"

float frand() {
    return qrand()/(float)RAND_MAX;
}

float frand(float a, float b) {
    return a + frand() * (b - a);
}

NeuralNetwork::NeuralNetwork(int hiddenSize, int outputSize) {
    Layer hidden;
    for (int _ = 0; _ < hiddenSize; ++_) {
        hidden.push_back(Neuron(IMG_PIXELS));
    }
    Layer output;
    for (int _ = 0; _ < outputSize; ++_) {
        output.push_back(Neuron(hiddenSize));
    }
    layers.push_back(hidden);
    layers.push_back(output);
}

NeuroVector<float> NeuralNetwork::input(const NeuroVector<float>& img) {
    NeuroVector<float> inputData = img;
    NeuroVector<float> outputData;
    for (const Layer& layer : layers) {
        for (const Neuron& neuron : layer) {
            outputData.push_back(neuron.f(inputData));
        }
        inputData = outputData;
        outputData.clear();
    }
    return inputData;
}

float Neuron::f(const NeuroVector<float>& t) const {
    float sum = bias;
    Q_ASSERT(t.size() == coeff.size());
    for (int i = 0; i < t.size(); ++i) {
        sum += t[i]*coeff[i];
    }
    return 1/(1 + expf(-sum));
}


Neuron::Neuron(int inputs)
        : coeff(NeuroVector<float>(inputs)), bias(frand(-1, 1)) {
    for (float& c : coeff) {
        c = frand(-1, 1);
    }
}

Neuron::Neuron() {
}

