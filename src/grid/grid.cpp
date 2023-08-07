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
    if (isInBoundary(x, y)) {
        if (cells[x][y] == nullptr) { return true; }
        else { return false; }
    }
    else { return true; }
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
    if (x < 0 || x >= x_grid || y < 0 || y >= y_grid)
    {   //std::cout << "is not in boundary! \n";
        return false; 
    }
    else 
    {   //std::cout << "is in boundary! \n";
        return true;
    }
}

void Grid::step()
{
    std::vector<int> xOrder = utils::shuffleXOrder(x_grid);

    for (int y = y_grid; y >= 0; --y)
    {
        for (int x : xOrder)
        {
            if (isCellEmpty(x, y) == false)
            {
                getElementAtCell(x, y).update();
            }
        }
    }
}

Grid::~Grid(){

}