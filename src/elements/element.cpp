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
    grid.cells[to_x][to_y] = std::move(grid.cells[x][y]);
    x = to_x;
    y = to_y;
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
