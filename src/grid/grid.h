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
    int rows;
    int cols;

public:
    std::vector<std::vector<ElementPtr>> cells;
    Grid(int rows, int cols);
    bool isCellEmpty(int row, int col);
    void addElement(ElementPtr element, int row, int col);
    const Element& getElementAtCell(int row, int col);
    ~Grid();
};

#endif
