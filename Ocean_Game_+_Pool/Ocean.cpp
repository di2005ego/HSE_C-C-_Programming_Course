#include <chrono>
#include <thread>

#include "object.h"
#include "ocean.h"

using namespace std;

void Ocean::initOcean() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 99);
    for (auto& objVector : data) {
        for (auto& object : objVector) {
            int randNumber = distr(gen);
            int randValue = uniform_int_distribution<>(-3, 3)(gen);
            if (randNumber < 70) {
                object = new None();
            }
            else if (randNumber > 70 && randNumber < 75) {
                object = new Stone('S', 0, 10 + randValue);
            }
            else if (randNumber > 75 && randNumber < 80) {
                object = new Reef('R', 10 + randValue);
            }
            else if (randNumber > 80 && randNumber < 85) {
                object = new Prey('p', 20 % this->row % this->col, 10 + randValue);
            }
            else if (randNumber > 85 && randNumber < 90) {
                object = new Predator('P', 15 % this->row % this->col, 10 + randValue);
            }
            else if (randNumber > 90 && randNumber < 95) {
                object = new ApexPredator('A', 30 % this->row % this->col, 10 + randValue);
            }
            else {
                object = new None();
            }
        }
    }
}

vector<Object*> Ocean::generateNeighbourhood(int row, int col) const {
    vector<Object*> neighbours;
    int neighbourRows[] = { row - 1, row, row + 1 };
    int neighbourCols[] = { col - 1, col, col + 1 };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int neighbourRow = (neighbourRows[i] + this->row) % this->row;
            int neighbourCol = (neighbourCols[j] + this->col) % this->col;
            if (!(neighbourRow == row && neighbourCol == col)) {
                neighbours.push_back(data[neighbourRow][neighbourCol]);
            }
        }
    }
    return neighbours;
}

bool Ocean::isCageEmpty(size_t i, size_t j) {
    if (data[i][j]) {
        Object* obj = data[i][j];
        return !obj->isAlive();
    }
    return true;
}

int Ocean::tick() {
    int changed = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (data[i][j]) {
                Object* obj = data[i][j];
                if (obj->isAlive()) {
                    data[i][j]->tick(generateNeighbourhood(i, j));
                    if (obj != data[i][j]) {
                        changed = true;
                    }
                }
                if (!data[i][j]->isAlive()) {
                    delete data[i][j];
                    data[i][j] = new None();
                }
            }
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (data[i][j]) {
                Object* obj = data[i][j];
                if (obj->isAlive() && obj->getSpeed() > 0) {
                    int shift = obj->getSpeed();
                    int targetRowUp;
                    if (i >= shift) {
                        targetRowUp = i - shift;
                    }
                    else {
                        targetRowUp = this->row - shift + i;
                    }
                    int targetRowDown = (i + shift) % this->row;
                    int targetColLeft;
                    if (i >= shift) {
                        targetColLeft = i - shift;
                    }
                    else {
                        targetColLeft = this->col - shift + i;
                    }
                    int targetColRight = (i + shift) % this->col;
                    if (isCageEmpty(targetRowUp, j)) {
                        if (data[targetRowUp][j]) {
                            delete data[targetRowUp][j];
                        }
                        data[targetRowUp][j] = data[i][j];
                        data[i][j] = new None();
                    }
                    else if (isCageEmpty(targetRowDown, j)) {
                        if (data[targetRowDown][j]) {
                            delete data[targetRowDown][j];
                        }
                        data[targetRowDown][j] = data[i][j];
                        data[i][j] = new None();
                    }
                    else if (isCageEmpty(i, targetColLeft)) {
                        if (data[i][targetColLeft]) {
                            delete data[i][targetColLeft];
                        }
                        data[i][targetColLeft] = data[i][j];
                        data[i][j] = new None();
                    }
                    else if (isCageEmpty(i, targetColRight)) {
                        if (data[i][targetColRight]) {
                            delete data[i][targetColRight];
                        }
                        data[i][targetColRight] = data[i][j];
                        data[i][j] = new None();
                    }
                }
            }
        }
    }
    return changed;
}

void Ocean::print(int m) {
    for (auto& objVector : data) {
        for (auto& object : objVector) {
            if (object->isAlive()) {
                cout << object->getSymbol();
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < m; i++) {
        cout << "_";
    }
}

Ocean::~Ocean() {
    for (auto& objVector : data) {
        for (auto& object : objVector) {
            delete object;
        }
    }
}

int main(int argc, char** argv)
{
    int n, m;
    if (argc < 3) {
        cout << "Since argc is less than 3, enter two numbers that will be the size of the ocean" << endl;
        cin >> n >> m;
        system("CLS");
    }
    else {
        n = atoi(argv[1]);
        m = atoi(argv[2]);
    }
    int noChanges = 0;
    Ocean ocean(n, m);
    ocean.initOcean();
    while (true)
    {
        int changed = ocean.tick();
        ocean.print(m);
        if (changed == 0) {
            noChanges++;
        }
        else {
            noChanges = 0;
        }
        if (noChanges > 99) {
            exit(0);
        }
        this_thread::sleep_for(chrono::seconds(1));
        system("CLS");
    }
    return 0;
}