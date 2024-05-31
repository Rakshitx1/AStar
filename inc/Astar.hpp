#include "Grid.hpp"

#include <vector>

class Astar{
private:
    std::vector<Coordinate*> openList;
    std::vector<Coordinate*> closedList;

public:
    Astar();
    ~Astar();
    void doMagic(Grid* grid, Coordinate* start, Coordinate* end, const std::vector<Coordinate*>& blockedList);
    void findPath(Grid* grid, Coordinate* start, Coordinate* end, const std::vector<Coordinate*>& blockedList);
    static void printPath(const Coordinate* end) ;

};