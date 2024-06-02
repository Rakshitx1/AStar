#include "Astar.hpp"

#include <algorithm>
#include <iostream>
#include <utility>


// Constructor
Astar::Astar(){
    // Do nothing
}

// Destructor
Astar::~Astar(){
    for(Coordinate* coord : openList){
        delete coord;
    }

    for(Coordinate* coord : closedList){
        delete coord;
    }

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
        for(int i = 1; i < openList.size(); i++){
            if(openList[i]->getF() < current->getF() || (openList[i]->getF() == current->getF() && openList[i]->getH() < current->getH())){
                current = openList[i];
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
    for(int i = path.size() - 1; i >= 0; i--){
        std::cout << path[i]->getX() << ", " << path[i]->getY() << std::endl;
    }
}

