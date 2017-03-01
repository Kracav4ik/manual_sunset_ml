#pragma once

#define CHECK(condition, code) if (condition) { code }
//#define CHECK(condition, code)

float frand();
float frand(float from, float to);

void crashForDebug();
