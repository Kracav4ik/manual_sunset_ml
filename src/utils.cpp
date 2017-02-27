#include "utils.h"

#include <QtGlobal>

void crashForDebug() {
    int i = 1 / 0;
}

float frand() {
    return qrand()/(float)RAND_MAX;
}

float frand(float a, float b) {
    return a + frand() * (b - a);
}
