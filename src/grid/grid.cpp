#include "grid.h"


Grid::Grid(int numX, int numY) : x_grid(numX), y_grid(numY)
{
    cells.resize(numY);
    for (int y = 0; y < numY; ++y) {
        cells[y].resize(numX);
    }
}

bool Grid::isCellEmpty(int x, int y)
{
    if (x >= 0 && x < x_grid && y >= 0 && y < y_grid) {
        return cells[x][y] == nullptr;
    }
    return false;
}

Element& Grid::getElementAtCell(int x, int y)
{
    return *cells[x][y];
}

void Grid::addElement(ElementPtr element, int to_x, int to_y)
{
    if (to_x >= 0 && to_x < x_grid && to_y >= 0 && to_y < y_grid)
    {
        if (isCellEmpty(to_x, to_y) == true)
        {
            element->setPos(to_x, to_y);
            cells[to_x][to_y] = std::move(element);
        }
    }
}

bool Grid::isInBoundary(int x, int y)
{
    if (x < 0 || x >= x_grid || y < 0 || y >= y_grid){
        std::cout << x << ", " << y << "\n";
        return false;
    }
    else
    {
        return true;
    }
}

Grid::~Grid(){

}