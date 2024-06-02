#include "Grid.hpp"

#include "iostream"

// Constructor
Grid::Grid(int width, int height) : width(width), height(height) {
    coordinateGrid.clear();
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
Coordinate* Grid::getCoordinate(int x, int y) {
    if (isValidCoordinate(x, y)) {
        for(Coordinate* coord : coordinateGrid){
            if(coord->getX() == x && coord->getY() == y){
                return coord;
            }
        }
        Coordinate* newCoord = new Coordinate(x, y);
        coordinateGrid.push_back(newCoord);
        return newCoord;
        // return coordinateGrid[x * height + y];
    }
    return nullptr;
}

// Get neighbors of a coordinate
std::vector<Coordinate*> Grid::getNeighbors(Coordinate* coordinate) {
    std::vector<Coordinate*> neighbors;
    int x = coordinate->getX();
    int y = coordinate->getY();

    for (int x2 = x - 1; x2 <= x + 1; x2++) {
        for (int y2 = y - 1; y2 <= y + 1; y2++) {
            if (isValidCoordinate(x2, y2) && (x2 != x || y2 != y)) {
                neighbors.push_back(getCoordinate(x2, y2));
            }
        }
    }

    return neighbors;
}

// Print the grid
void Grid::printGrid() {
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            std::cout << this->getCoordinate(i, j)->getH() << ", ";
        }
        std::cout << std::endl;
    }
}
