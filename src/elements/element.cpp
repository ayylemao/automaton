#include "element.h"


Element::Element(Grid &g) : grid(g)
{
    x = 0;
    y = 0;
};

void Element::setPos(int row, int col){
    x = row;
    y = col;
}

std::tuple<int, int> Element::getPos() const {
    return std::make_tuple(x, y);
}

bool Element::isSolid() const { return false; }
bool Element::isGas() const { return false; }
bool Element::isLiquid() const { return false; }
bool Element::isMovable() const { return false; }

void Element::moveTo(int to_x, int to_y)
{
    if (grid.isInBoundary(to_x, to_y))
    {
        grid.cells[to_x][to_y] = std::move(grid.cells[x][y]);
        x = to_x;
        y = to_y;
    }
    else
    {
        grid.cells[x][y].reset();
    }
}

std::tuple<bool, bool> Element::lookDiagonal()
{
    bool left = false;
    bool right = false;
    int target_y = y + 1;
    //left
    int target_x = x - 1;
    // TODO: Currently can't fall diagonally out of scope (aka left/right)
    if (grid.isInBoundary(target_x, target_y) && grid.isCellEmpty(target_x, target_y))
    {
        left = true;
    }
    //right
    target_x = x + 1;
    if (grid.isInBoundary(target_x, target_y) && grid.isCellEmpty(target_x, target_y))
    {
        right = true;
    }
    return std::make_tuple(left, right);
}

std::tuple<bool, bool> Element::lookLeftRight()
{
    bool left = false;
    bool right = false;
    int target_y = y;
    //left
    int target_x = x - 1;

    if (grid.isInBoundary(target_x, target_y) && grid.isCellEmpty(target_x, target_y))
    {
        left = true;
    }
    //right
    target_x = x + 1;
    if (grid.isInBoundary(target_x, target_y) && grid.isCellEmpty(target_x, target_y))
    {
        right = true;
    }
    return std::make_tuple(left, right);
}


void Element::swapWith(int swap_x, int swap_y)
{
    grid.getElementAtCell(swap_x, swap_y).setPos(x, y);
    std::swap(grid.cells[x][y], grid.cells[swap_x][swap_y]);
    x = swap_x;
    y = swap_y;
}

Element::~Element()
{

}
