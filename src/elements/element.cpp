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
bool Element::isEmpty() const { return false; }

void Element::moveTo(int to_x, int to_y)
{
    if (grid.isInBoundary(to_x, to_y))
    {
        grid.cells[grid.index(to_x, to_y)] = std::move(grid.cells[grid.index(x, y)]);
        x = to_x;
        y = to_y;
    }
    else
    {
        grid.cells[grid.index(x, y)].reset();
    }
}

std::tuple<bool, bool, bool> Element::lookDiagonal()
{
    bool left = false;
    bool right = false;
    bool destroyed = false;
    int target_y = y + 1;
    //left
    int target_x = x - 1;
    

    if (!grid.isInBoundary(target_x, target_x))
    {
        destroyed = true;
        left = false;
        grid.replaceWithEmpty(x, y);
    }
    else
    {
		if (grid.getElementAtCell(target_x, target_y).isEmpty() || grid.getElementAtCell(target_x, target_y).isLiquid())
		{
			left = true;
		}
    }
    //right
    target_x = x + 1;
    if (!grid.isInBoundary(target_x, target_x))
    {
        destroyed = true;
        right = false;
        grid.replaceWithEmpty(x, y);
    }
    else
    {
		if (grid.getElementAtCell(target_x, target_y).isEmpty() || grid.getElementAtCell(target_x, target_y).isLiquid())
		{
			right = true;
		}
    }
    return std::make_tuple(left, right, destroyed);
}

std::tuple<bool, bool, bool> Element::lookLeftRight()
{
    bool left = false;
    bool right = false;
    bool destroyed = false;
    int target_y = y;
    //left
    int target_x = x - 1;

    if (!grid.isInBoundary(target_x, target_x))
    {
        destroyed = true;
        left = false;
        grid.replaceWithEmpty(x, y);
    }
    else
    {
        if (grid.getElementAtCell(target_x, target_y).isEmpty())
        {
            left = true;
        }
    }
    //right
    target_x = x + 1;
    if (!grid.isInBoundary(target_x, target_x))
    {
        destroyed = true;
        left = false;
        grid.replaceWithEmpty(x, y);
    }
    else
    {
        if (grid.getElementAtCell(target_x, target_y).isEmpty())
        {
            right = true;
        }
    }
    return std::make_tuple(left, right, destroyed);
}

void Element::swapWith(int swap_x, int swap_y)
{
    grid.getElementAtCell(swap_x, swap_y).setPos(x, y);
    std::swap(grid.cells[grid.index(x, y)], grid.cells[grid.index(swap_x, swap_y)]);
    x = swap_x;
    y = swap_y;
}

Element::~Element()
{

}
