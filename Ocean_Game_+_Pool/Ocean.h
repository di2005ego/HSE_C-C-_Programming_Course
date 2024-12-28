#pragma once

#include <iostream>
#include <random>
#include <vector>

#include "object.h"

using namespace std;

class Ocean final {
private:
    int row;
    int col;
    vector<vector<Object*>> data;
    bool isCageEmpty(size_t row, size_t col);

public:
    Ocean(size_t row = 15, size_t col = 15) : row(row), col(col) {
        data.resize(row, vector<Object*>(col));
    }
    void initOcean();
    vector<Object*> generateNeighbourhood(int row, int col) const;
    int tick();
    void print(int m);
    ~Ocean();
};