#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <memory>
#include "../elements/element.h"
#include "../common/types.h"
#include "../common/utils.h"



class Grid
{
private:

public:
    int const x_grid;
    int const y_grid;
    int step_counter;
    float gravity;
    float dt;
    float dtVel;
    std::vector<ElementPtr> cells;
    size_t index(int x, int y) const;
    Grid(int x, int y, float dt);
    void init();
    bool isCellEmpty(int x, int y);
    void initElement(ElementPtr element, int x, int y);
    void replaceElement(ElementPtr element, int x, int y);
    void replaceWithEmpty(int x, int y);
    Element* getElementAtCell(int x, int y);
    bool isInBoundary(int x, int y);
    Element* getLinearElement(int i);
    static void printTuple(std::tuple<int, int> tup);
    void step();
    ~Grid();
};

#endif
