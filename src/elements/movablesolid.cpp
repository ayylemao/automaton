#include "movablesolid.h"


MovableSolid::MovableSolid(Grid &g) : Solid(g)
{

};

bool MovableSolid::isMovable() const { return true; }

void MovableSolid::update() 
{
    // One cell below
    int target_x = x;
    int target_y = y + 1;

    // check if would move out of bounds and replace with empty cell
    if (!grid.isInBoundary(target_x, target_y))
    {
        grid.replaceWithEmpty(x, y);
        return;
    }

    Element &target_cell = grid.getElementAtCell(target_x, target_y);

    if (target_cell.isEmpty())
    {
        swapWith(target_x, target_y);
        return;
    }

    if (!target_cell.isEmpty())
    {
        if (target_cell.isLiquid())
        {
            swapWith(target_x, target_y);
            return;
        }

        if (target_cell.isSolid() || target_cell.isLiquid())
        {
            bool left;
            bool right;
            bool destroyed;
            std::tie(left, right, destroyed) = lookDiagonal();
            if (!destroyed)
            {
				if (left && right)
				{
					if(utils::coinToss())
					{
						swapWith(target_x-1, target_y);
						return;
					}
					else
					{
						swapWith(target_x+1, target_y);
						return;
					}
				} 
				if (left)
				{
					swapWith(target_x-1, target_y);
					return;
				}
				else if (right)
				{
					swapWith(target_x+1, target_y);
					return;
				} 
            }
        } 
    }
}