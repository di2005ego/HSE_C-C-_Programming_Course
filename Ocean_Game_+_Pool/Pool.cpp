#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <thread>
#include <vector>
using namespace std;

template<typename ElementTemplate>
class MemoryPool {
private:
    vector<ElementTemplate*> pool;
    size_t capacity;
    size_t freeIndex;

public:
    MemoryPool() : capacity(0), freeIndex(0) {}
    MemoryPool(size_t capacityInput) : capacity(capacityInput), freeIndex(0) {
        pool.resize(capacity, nullptr);
        for (auto poolElem : pool) {
            poolElem = reinterpret_cast<ElementTemplate*>(operator new(sizeof(ElementTemplate)));
        }
    }
    ~MemoryPool() {
        for (auto poolElem : pool) {
            operator delete(poolElem);
        }
    }
    void resize(size_t newCapacity) {
        if (newCapacity <= capacity) {
            return;
        }
        for (size_t i = capacity; i < newCapacity; i++) {
            pool.push_back(reinterpret_cast<ElementTemplate*>(operator new(sizeof(ElementTemplate))));
        }
        capacity = newCapacity;
    }
    template<class... Args>
    ElementTemplate* get(Args&&... args) {
        if (freeIndex >= capacity) {
            return nullptr;
        }
        ElementTemplate* element = new(pool[freeIndex++]) ElementTemplate(forward<Args>(args)...);
        return element;
    }
    bool put(ElementTemplate* element) {
        if (freeIndex == 0) {
            return false;
        }
        element->~ElementTemplate();
        pool[--freeIndex] = element;
        return true;
    }
    template<class... Args>
    unique_ptr<ElementTemplate, function<void(ElementTemplate*)>> unique(Args&&... args) {
        return unique_ptr<ElementTemplate, function<void(ElementTemplate*)>>(get(forward<Args>(args)...), [this](ElementTemplate* ptr) { 
            this->put(ptr); });
    }
    template<class... Args>
    shared_ptr<ElementTemplate> shared(Args&&... args) {
        return shared_ptr<ElementTemplate>(get(forward<Args>(args)...), [this](ElementTemplate* ptr) { 
            this->put(ptr); });
    }
};

template<typename Received>
class PoolMix {
public:
    static void* operator new(size_t size) {
        return pool.get();
    }
    static void operator delete(void* ptr, size_t size) {
        pool.put(static_cast<Received*>(ptr));
    }
    static void* operator new(size_t size, void* ptr) {
        return ::operator new(size, ptr);
    }
    static void operator delete(void* ptr, void* place) {
        ::operator delete(ptr, place);
    }

protected:
    static MemoryPool<Received> pool;
};

template<typename Received>
MemoryPool<Received> PoolMix<Received>::pool(100);

class Reef;

class Object {
private:
	virtual void Die() = 0;

protected:
	char symbol;
	size_t age;
	size_t speed;
	size_t timeToDie;
	bool is_Alive;
	bool isAdult;

public:
	explicit Object(char symbol = ' ', size_t speed = 0, size_t timeToDie = 0) : symbol(symbol), age(0),
		speed(speed), timeToDie(timeToDie), is_Alive(true), isAdult(false) {}
	virtual void tick(const vector<Object*>& neighbours) = 0;
	virtual bool canReproduce(const vector<Object*>& neighbours) = 0;
	virtual bool dangerEnvironment(const vector<Object*>& neighbours) = 0;
	bool isAlive() const {
		return is_Alive;
	}
	char getSymbol() const {
		return symbol;
	}
	size_t getAge() const {
		return age;
	}
	size_t getSpeed() const {
		return speed;
	}
	size_t getTimeToDie() const {
		return timeToDie;
	}
	virtual ~Object() = default;
};

class Stone : public Object {
private:
	void turnToCorall();
	virtual void Die() override;

public:
	Stone(char symbol, size_t speed, size_t timeToDie);
	virtual void tick(const vector<Object*>& neighbours) override;
	virtual bool canReproduce(const vector<Object*>& neighbours) override {
		return false;
	}
	virtual bool dangerEnvironment(const vector<Object*>& neighbours) override {
		return false;
	}
	Stone& operator=(const Reef& other);
};

template<>
MemoryPool<Stone> PoolMix<Stone>::pool(100);

class Reef : public Object {
private:
	void turnToStone();
	virtual void Die() override;

public:
	Reef(char symbol, size_t timeToDie);
	virtual bool canReproduce(const vector<Object*>& neighbours) override {
		return false;
	}
	virtual bool dangerEnvironment(const vector<Object*>& neighbours) override {
		return false;
	}
	virtual void tick(const vector<Object*>& neighbours) override;
	Reef& operator=(const Stone& other);
};

template<>
MemoryPool<Reef> PoolMix<Reef>::pool(100);

class Prey : public Object {
private:
	bool canBeEaten = false;
	size_t timeToAdult;

public:
	Prey(char symbol, size_t speed, size_t timeToDie);
	virtual void Die() override;
	virtual void tick(const vector<Object*>& neighbours) override;
	virtual bool canReproduce(const vector<Object*>& neighbours) override;
	virtual bool dangerEnvironment(const vector<Object*>& neighbours) override;
	bool canNotBeEaten(const vector<Object*>& neighbours);
	void setCanBeEaten(bool condition) {
		canBeEaten = condition;
	}
	bool getCanBeEaten() const {
		return canBeEaten;
	}
};

template<>
MemoryPool<Prey> PoolMix<Prey>::pool(100);

class Predator : public Object
{
private:
	bool isFull = true;
	size_t timeWithoutFood = 0;
	virtual void Die() override;
	size_t timeToAdult;

public:
	Predator(char symbol, size_t speed, size_t timeToDie);
	bool getIsFull() {
		return isFull;
	}
	virtual void tick(const vector<Object*>& neighbours) override;
	virtual bool canReproduce(const vector<Object*>& neighbours) override;
	virtual bool dangerEnvironment(const vector<Object*>& neighbours) override;
};

template<>
MemoryPool<Predator> PoolMix<Predator>::pool(100);

class ApexPredator : public Object
{
private:
	bool isFull = true;
	size_t timeWithoutFood = 0;
	virtual void Die() override {
		is_Alive = false;
	};
	size_t timeToAdult;

public:
	ApexPredator(char symbol, size_t speed, size_t timeToDie);
	bool getIsFull() {
		return isFull;
	}
	virtual void tick(const vector<Object*>& neighbours) override;
	virtual bool canReproduce(const vector<Object*>& neighbours) override;
	virtual bool dangerEnvironment(const vector<Object*>& neighbours) override {
		return false;
	}
};

template<>
MemoryPool<ApexPredator> PoolMix<ApexPredator>::pool(100);

class None : public Object
{
private:
	virtual void Die() override {
		is_Alive = false;
	};
public:
	None() : Object(' ') {
		is_Alive = false;
	}
	explicit None(char symbol, size_t age, size_t speed) : Object(' ', 0) {
		is_Alive = false;
	}
	virtual void tick(const vector<Object*>& neighbours) override;
	virtual bool canReproduce(const vector<Object*>& neighbours) override {
		return false;
	}
	virtual bool dangerEnvironment(const vector<Object*>& neighbours) override {
		return false;
	}
};

template<>
MemoryPool<None> PoolMix<None>::pool(100);

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

int main(int argc, char** argv) {
    int n, m;
    if (argc < 3) {
        cout << "Since argc is less than 3, enter two numbers that will be the size of the ocean (for example, 30 30)" << endl;
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
    while (true) {
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