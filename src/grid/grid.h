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
    std::vector<ElementPtr> cells;
    size_t index(int x, int y) const;
    Grid(int x, int y);
    void init();
    bool isCellEmpty(int x, int y);
    void initElement(ElementPtr element, int x, int y);
    void replaceElement(ElementPtr element, int x, int y);
    void replaceWithEmpty(int x, int y);
    Element& getElementAtCell(int x, int y);
    bool isInBoundary(int x, int y);
    Element& getLinearElement(int i);
    void step();
    ~Grid();
};

#endif
