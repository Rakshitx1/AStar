#include "Coordinate.hpp"

#include <cmath>
#include <climits>

Coordinate::Coordinate(int x, int y) {
    this->x = x;
    this->y = y;

    // set G to infinity
    this->g = INT_MAX;

    // set Parent to nullptr
    this->parent = nullptr;
}

Coordinate::~Coordinate() {
    // Clean up
    this->x = 0;
    this->y = 0;

    this->f = 0;
    this->g = 0;
    this->h = 0;

    this->parent = nullptr;
}

void Coordinate::setF(int f) {
    this->f = f;
}

void Coordinate::setG(int g) {
    this->g = g;
}

void Coordinate::setH(int h) {
    this->h = h;
}

int Coordinate::getF() const {
    return this->f;
}

int Coordinate::getG() const {
    return this->g;
}

int Coordinate::getH() const {
    return this->h;
}

int Coordinate::getX() const {
    return this->x;
}

int Coordinate::getY() const {
    return this->y;
}

Coordinate* Coordinate::getParent() const {
    return this->parent;
}

void Coordinate::setParent(Coordinate* parent) {
    this->parent = parent;
}

int Coordinate::distanceTo(Coordinate* other) const {
    float distance = pow(pow(other->getX() - this->x, 2) + pow(other->getY() - this->y, 2), 0.5);
    return static_cast<int>(round(distance * 10));
}