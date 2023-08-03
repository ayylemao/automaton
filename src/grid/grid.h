#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <memory>
#include "../elements/element.h"
#include "../common/types.h"



class Grid
{
private:

public:
    int const x_grid;
    int const y_grid;
    std::vector<std::vector<ElementPtr>> cells;
    Grid(int x, int y);
    std::vector<ElementPtr>& operator[](int x);
    bool isCellEmpty(int x, int y);
    void addElement(ElementPtr element, int x, int y);
    Element& getElementAtCell(int x, int y);
    bool isInBoundary(int x, int y);
    void step();
    ~Grid();
};

#endif
