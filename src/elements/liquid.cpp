#include "liquid.h"


Liquid::Liquid(Grid& g) : Element(g)
{
    
}

bool Liquid::isLiquid() const { return true; }
bool Liquid::isMovable() const { return true; }


void Liquid::update()
{
    updateColor();

    int target_x = x;
    int target_y = y + 1;

    // check if would move out of bounds and replace with empty cell

    if (!grid.isInBoundary(target_x, target_y))
    {
        grid.replaceWithEmpty(x, y);
        return;
    }
    
	Element *target_cell = grid.getElementAtCell(target_x, target_y);

    if (target_cell->isEmpty())
    {
        swapWith(target_x, target_y);
        return;
    }


	    // check left and right since below is filled
    target_x = x;
    target_y = y;


	if (target_cell->isSolid() || target_cell->isLiquid())
	{
		int left;
		int right;
		std::tie(left, right) = lookLeftRight();
		if (left == right)
		{
			if(grid.step_counter % 2 == 0)
			{
				swapWith(target_x-left, target_y);
				return;
			}
			else
			{
				swapWith(target_x+right, target_y);
				return;
			}
		} 
		else if (left>right)
		{
			swapWith(target_x-left, target_y);
			return;
		}
		else
		{
			swapWith(target_x+right, target_y);
			return;
		}
    }
}
