#include "object.h"

using namespace std;

void Stone::turnToCorall() {
    Reef* reef = new Reef('R', timeToDie);
    *this = *reef;
    delete reef;
}

void Stone::Die() {
    turnToCorall();
}

Stone::Stone(char symbol, size_t speed, size_t timeToDie) : Object(symbol, speed, timeToDie) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(-2, 2);
    int randTime = distr(gen);
    timeToDie += randTime;
}

void Stone::tick(const vector<Object*>& neighbours) {
    age++;
    if (timeToDie <= age) {
        Die();
    }
}

Stone& Stone::operator=(const Reef& other) {
    symbol = other.getSymbol();
    age = other.getAge();
    speed = other.getSpeed();
    timeToDie = other.getTimeToDie();
    is_Alive = true;
    isAdult = false;
    return *this;
}

Reef::Reef(char symbol, size_t timeToDie) : Object(symbol, 0, timeToDie) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(-2, 2);
    int randTime = distr(gen);
    timeToDie += randTime;
}

void Reef::turnToStone() {
    Stone* stone = new Stone('S', 0, timeToDie);
    *this = *stone;
    delete stone;
}

void Reef::Die() {
    turnToStone();
}

void Reef::tick(const vector<Object*>& neighbours) {
    age++;
    if (timeToDie <= age) {
        Die();
    }
}

Reef& Reef::operator=(const Stone& other) {
    symbol = other.getSymbol();
    age = other.getAge();
    speed = other.getSpeed();
    timeToDie = other.getTimeToDie();
    is_Alive = true;
    isAdult = false;
    return *this;
}

Prey::Prey(char symbol, size_t speed, size_t timeToDie) : Object(symbol, speed, timeToDie) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(-2, 2);
    int randTime = distr(gen);
    timeToDie += randTime;
    timeToAdult += 10 + distr(gen);
}

void Prey::Die() {
    is_Alive = false;
}

void Prey::tick(const vector<Object*>& neighbours) {
    if (!is_Alive) {
        return;
    }
    age++;
    setCanBeEaten(!(canNotBeEaten(neighbours)));
    if (timeToDie <= age) {
        Die();
    }
    if (timeToAdult <= age) {
        isAdult = true;
    }
}

bool Prey::canReproduce(const vector<Object*>& neighbours) {
    return this->isAdult && any_of(neighbours.begin(), neighbours.end(), [](Object* obj) {
        auto prey = dynamic_cast<Prey*>(obj);
        return prey && prey->isAdult;
    });
}

bool Prey::dangerEnvironment(const vector<Object*>& neighbours) {
    return any_of(neighbours.begin(), neighbours.end(), [](Object* obj) -> bool {
        return dynamic_cast<Predator*>(obj) != nullptr || dynamic_cast<ApexPredator*>(obj) != nullptr;
    });
}

bool Prey::canNotBeEaten(const vector<Object*>& neighbours) {
    return any_of(neighbours.begin(), neighbours.end(), [](Object* obj) {
        auto reef = dynamic_cast<Reef*>(obj);
        return reef;
    });
}

Predator::Predator(char symbol, size_t speed, size_t timeToDie) : Object(symbol, speed, timeToDie) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(-2, 2);
    int randTime = distr(gen);
    timeToDie += randTime;
    timeToAdult += 10 + distr(gen);
}

void Predator::Die() {
    is_Alive = false;
}

void Predator::tick(const vector<Object*>& neighbours) {
    if (!is_Alive) {
        return;
    }
    age++;
    timeWithoutFood++;
    for (auto it : neighbours) {
        auto object = dynamic_cast<Prey*>(it);
        if (object && object->getCanBeEaten()) {
            object->Die();
            timeWithoutFood = 0;
            speed = 1;
        }
    }
    if (timeToDie <= age) {
        Die();
    }
    if (timeWithoutFood == 2) {
        speed = 2;
    }
    else if (timeWithoutFood == 4) {
        Die();
    }
    if (timeToAdult <= age) {
        isAdult = true;
    }
}

bool Predator::canReproduce(const vector<Object*>& neighbours) {
    return this->isAdult && this->getIsFull() && any_of(neighbours.begin(), neighbours.end(), [](Object* obj) {
        auto predator = dynamic_cast<Predator*>(obj);
        return predator && predator->isAdult && predator->getIsFull();
    });
}

bool Predator::dangerEnvironment(const vector<Object*>& neighbours) {
    return any_of(neighbours.begin(), neighbours.end(), [](Object* obj) -> bool {
        return dynamic_cast<ApexPredator*>(obj) != nullptr;
    });
}

ApexPredator::ApexPredator(char symbol, size_t speed, size_t timeToDie) : Object(symbol, speed, timeToDie) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(-2, 2);
    int randTime = distr(gen);
    timeToDie += randTime;
    timeToAdult += 10 + distr(gen);
}

void ApexPredator::tick(const vector<Object*>& neighbours) {
    if (!is_Alive) {
        return;
    }
    age++;
    timeWithoutFood++;
    for (auto it : neighbours) {
        auto obj = dynamic_cast<Prey*>(it);
        if (obj && obj->getCanBeEaten()) {
            obj->Die();
            timeWithoutFood = 0;
            speed = 1;
        }
    }
    if (timeToDie <= age) {
        Die();
    }
    if (timeWithoutFood == 2) {
        speed = 2;
    }
    if (timeWithoutFood == 4) {
        Die();
    }
    if (timeToAdult <= age) {
        isAdult = true;
    }
}

bool ApexPredator::canReproduce(const vector<Object*>& neighbours) {
    return this->isAdult && this->getIsFull() && any_of(neighbours.begin(), neighbours.end(), [](Object* obj) {
        auto apexPredator = dynamic_cast<ApexPredator*>(obj);
        return apexPredator && apexPredator->isAdult && apexPredator->getIsFull();
    });
}

void None::tick(const vector<Object*>& neighbours) {}