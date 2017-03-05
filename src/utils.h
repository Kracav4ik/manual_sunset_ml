#pragma once

#define CHECK(condition, code) if (condition) { code }
//#define CHECK(condition, code)

float frand();
float frand(float from, float to);

void crashForDebug();

class range {
public:
    range(int val) : val(val) {}

    class range_iter {
    public:
        range_iter(int i) : i(i) {}
        int operator*() const { return i; }
        bool operator !=(const range_iter& other) { return i != other.i; }
        void operator++() { ++i; }
    private:
        int i;
    };

    range_iter begin() const { return 0; }
    range_iter end() const { return val; }
private:
    int val;
};

