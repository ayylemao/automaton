#include "element.h"


Element::Element(Grid &g) : grid(g)
{
    x = 0;
    y = 0;
    hasMoved = false;
    dispersionRate = 1;
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

int Element::getDispersionRate() const
{
    return 0;
}

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

std::tuple<bool, bool> Element::lookDiagonal()
{
    bool left = false;
    bool right = false;
    int target_y = y + 1;

    //left
    int target_x = x - 1;
    if (grid.isInBoundary(target_x, target_x))
    {
        Element* targetCellLeft = grid.getElementAtCell(target_x, target_y);
        if (targetCellLeft->isEmpty() || targetCellLeft->isLiquid())
        {
            left = true;
        }
    }

    //right
    target_x = x + 1;
    if (grid.isInBoundary(target_x, target_x))
    {
        Element* targetCellRight = grid.getElementAtCell(target_x, target_y);
        if (targetCellRight->isEmpty() || targetCellRight->isLiquid())
        {
            right = true;
        }
    }
    return std::make_tuple(left, right);
}

std::tuple<int, int> Element::lookLeftRight()
{
    int left = 0;
    int right = 0;
    bool left_stopped = false;
    bool right_stopped = false;
    int target_y = y;
    int target_x;
      
    for (int offset = 1; offset <= getDispersionRate(); offset++)
    {
        target_x = x - offset;
		if (grid.isInBoundary(target_x, target_y) && !left_stopped)
		{
			if (grid.getElementAtCell(target_x, target_y)->isEmpty())
			{
				left += 1;
			}
            else
            {
                left_stopped = true;
            }
		}

        target_x = x + offset;
		if (grid.isInBoundary(target_x, target_y) && !right_stopped)
		{
			if (grid.getElementAtCell(target_x, target_y)->isEmpty())
			{
				right += 1;
			}
            else
            {
                right_stopped = true;
            }
		}
    }

    return std::make_tuple(left, right);
}


void Element::swapWith(int swap_x, int swap_y)
{
    grid.getElementAtCell(swap_x, swap_y)->setPos(x, y);
    std::swap(grid.cells[grid.index(x, y)], grid.cells[grid.index(swap_x, swap_y)]);
    x = swap_x;
    y = swap_y;
}

Element::~Element()
{

}
