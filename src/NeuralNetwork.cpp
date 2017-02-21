#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork() {}

QVector<float> NeuralNetwork::input(QVector<float> img) {
    QVector<float> last1;
    QVector<float> last2;
    for (int j = 0; j < 1; ++j) {
        int i1 = 10;
        if (j == 0){
            i1 = 1000;
            last1 = img;
        }
        QVector<Neuron> layer;
        for (int i = 0; i < i1; ++i) {
            Neuron neuron;
            layer.append(neuron);
            last2.append(neuron.f(last1));
        }
        layers.append(layer);
        last1 = last2;
        last2.clear();
    }
    return last1;

}

float Neuron::f(QVector<float> t) {
    float sum = 0;
    for (int i = 0; i < 784; ++i) {
        sum += t[i]*coeff[i];
    }
    return 1/(1 + expf(bias-sum));
}


Neuron::Neuron()
        : coeff(QVector<float>(784)), bias(qrand() / 66000.f) {}

