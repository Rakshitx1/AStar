#include "Astar.hpp"

#include <algorithm>
#include <iostream>

// Constructor
Astar::Astar() = default;

// Destructor
Astar::~Astar(){
    openList.clear();
    closedList.clear();

    openList.shrink_to_fit();
    closedList.shrink_to_fit();
}

void Astar::doMagic(Grid *grid, Coordinate *start, Coordinate *end, const std::vector<Coordinate*>& blockedList) {
    findPath(grid, start, end, blockedList);
    printPath(end);
}

// Find path
void Astar::findPath(Grid* grid, Coordinate* start, Coordinate* end, const std::vector<Coordinate*>& blockedList){
    start->setG(0);
    start->setH(start->distanceTo(end));
    start->setF(start->getH());
    start->setParent(nullptr);

    end->setG(end->distanceTo(start));
    end->setH(0);
    end->setF(end->getG());
    end->setParent(nullptr);

    this->openList.push_back(start);

    while(!openList.empty()){
        std::vector<Coordinate*> neighbors;
        neighbors.clear();
        Coordinate* current = openList[0];
        for(auto& coord : openList){
            if(coord->getF() < current->getF() || (coord->getF() == current->getF() && coord->getH() < current->getH())){
                current = coord;
            }
        }

        openList.erase(std::remove(openList.begin(), openList.end(), current), openList.end());
        closedList.push_back(current);

        if(current->getX() == end->getX() && current->getY() == end->getY()){
            break;
        }

        neighbors = grid->getNeighbors(current);
        for(Coordinate* neighbor : neighbors){
            if(std::find(blockedList.begin(), blockedList.end(), neighbor) != blockedList.end()){
                continue;
            }

            if(std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end()){
                continue;
            }

            if((neighbor->getG() > current->getG() + current->distanceTo(neighbor)) || 
               (std::find(openList.begin(), openList.end(), neighbor) == openList.end())){
                neighbor->setG(current->getG() + current->distanceTo(neighbor));
                neighbor->setH(neighbor->distanceTo(end));
                neighbor->setF(neighbor->getG() + neighbor->getH());
                neighbor->setParent(current);

                if(std::find(openList.begin(), openList.end(), neighbor) == openList.end()){
                    openList.push_back(neighbor);
                }
            }
        }
    }
}

void Astar::printPath(const Coordinate* end) {
    std::vector<const Coordinate*> path;
    const Coordinate* current = end;
    while(current != nullptr){
        path.push_back(current);
        current = current->getParent();
    }

    std::cout << "Path: " << std::endl;
    for(auto it = path.rbegin(); it != path.rend(); ++it){
        std::cout << "(" << (*it)->getX() << ", " << (*it)->getY() << ")" << std::endl;
    }
}

