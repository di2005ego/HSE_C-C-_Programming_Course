#pragma once

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

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

class Prey : public Object
{
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