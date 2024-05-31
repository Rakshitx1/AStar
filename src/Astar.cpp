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

void Astar::doMagic(Grid *grid, Coordinate *start, Coordinate *end, std::vector<Coordinate *> blockedList) {
    findPath(grid, start, end, std::move(blockedList));
    printPath(end);
}

// Find path
void Astar::findPath(Grid* grid, Coordinate* start, Coordinate* end, std::vector<Coordinate*> blockedList){
    start->setF(0);
    start->setG(start->distanceTo(end));
    start->setH(start->getG());
    start->setParent(nullptr);

    end->setF(start->getG());
    end->setG(0);
    end->setH(end->getF());

    openList.push_back(start);

    while(!openList.empty()){
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

        std::vector<Coordinate*> neighbors = grid->getNeighbors(current);
        for(Coordinate* neighbor : neighbors){
            if(std::find(blockedList.begin(), blockedList.end(), neighbor) != blockedList.end()){
                continue;
            }

            if(std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end()){
                continue;
            }

            if((neighbor->getF() > current->getF() + current->distanceTo(neighbor)) || 
               (std::find(openList.begin(), openList.end(), neighbor) == openList.end())){
                neighbor->setF(current->getF() + current->distanceTo(neighbor));
                neighbor->setG(neighbor->distanceTo(end));
                neighbor->setH(neighbor->getG() + neighbor->getF());
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
    int i = 0;
    while(current != nullptr){
        path.push_back(current);
        current = current->getParent();
        i++;
    }

    std::cout << "Path: " << std::endl;
//    for(int i = path.size() - 1; i >= 0; i--){
    for(i--; i >= 0; i--){
        std::cout << path[i]->getX() << ", " << path[i]->getY() << std::endl;
    }
}

