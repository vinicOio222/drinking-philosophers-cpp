#include "bottle.hpp"

Bottle::Bottle(
    int id, int philosopherA, int philosopherB
) : id(id), philosopherA(philosopherA), philosopherB(philosopherB) {}


int Bottle::getId() const {
    return id;
};

int Bottle::getPhilosopherA() const {
    return philosopherA;
};

int Bottle::getPhilosopherB() const {
    return philosopherB;
};

std::mutex& Bottle::getMutex() {
    return mtx;
}
