#include "Grid.hpp"

#include "iostream"

// Constructor
Grid::Grid(int width, int height) : width(width), height(height) {
    coordinateGrid.resize(width * height);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            coordinateGrid[i * height + j] = new Coordinate(i, j);
        }
    }
}

// Destructor
Grid::~Grid() {
    // Clean up
    for (Coordinate* coordinate : coordinateGrid) {
        delete coordinate;
    }
    coordinateGrid.clear();
}

// Check if a coordinate is valid
bool Grid::isValidCoordinate(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

// Get a coordinate object
Coordinate* Grid::getCoordinate(int x, int y) const {
    if (isValidCoordinate(x, y)) {
        return coordinateGrid[x * height + y];
    }
    return nullptr;
}

// Get neighbors of a coordinate
std::vector<Coordinate*> Grid::getNeighbors(Coordinate* coordinate) const {
    std::vector<Coordinate*> neighbors;
    int x = coordinate->getX();
    int y = coordinate->getY();

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (isValidCoordinate(x + i, y + j)) {
                neighbors.push_back(coordinateGrid[(x + i) * height + (y + j)]);
            }
        }
    }

    return neighbors;
}

// Print the grid
void Grid::printGrid() const{
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            std::cout << this->getCoordinate(i, j)->getH() << ", ";
        }
        std::cout << std::endl;
    }
}
