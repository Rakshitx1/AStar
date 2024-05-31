#include "Coordinate.hpp"

#include <vector>

class Grid {
private:
    int width;
    int height;
    std::vector<Coordinate*> coordinateGrid;
    
public:
    Grid(int width, int height);
    ~Grid();
    [[nodiscard]] bool isValidCoordinate(int x, int y) const;
    [[nodiscard]] Coordinate* getCoordinate(int x, int y) const;
    std::vector<Coordinate*> getNeighbors(Coordinate* coordinate) const;
    void printGrid() const;
    Coordinate* getPointer(Coordinate* coord) const;

};