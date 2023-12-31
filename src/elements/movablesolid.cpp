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
    
	Element *target_cell = grid.getElementAtCell(target_x, target_y);

    if (target_cell->isEmpty() || target_cell->isLiquid())
    {
        swapWith(target_x, target_y);
        return;
    }

	if (target_cell->isSolid())
		{
		bool left;
		bool right;
		std::tie(left, right) = lookDiagonal();
		if (left && right)
		{
			if(grid.step_counter % 2 == 0)
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
		else if (left)
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