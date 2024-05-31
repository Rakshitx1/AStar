#include "Astar.hpp"

#include <iostream>
#include <vector>

#define WIDTH 8
#define HEIGHT 8

int main(int argc, char* argv[]) {
    // Create a grid
    Grid* grid = new Grid(WIDTH, HEIGHT);

    // Create start and end coordinates
    Coordinate* start = grid->getCoordinate(0, 0);
    Coordinate* end = grid->getCoordinate(7, 0);

    // Create a list of blocked coordinates
    std::vector<Coordinate*> blockedList;
    blockedList.push_back(grid->getCoordinate(1, 0));
    blockedList.push_back(grid->getCoordinate(2, 0));
    blockedList.push_back(grid->getCoordinate(3, 0));
    blockedList.push_back(grid->getCoordinate(4, 0));
    blockedList.push_back(grid->getCoordinate(5, 0));
    blockedList.push_back(grid->getCoordinate(6, 0));

    // Create an Astar object
    auto* astar = new Astar();
    astar->doMagic(grid, start, end, blockedList);
    
    return EXIT_SUCCESS;

}
