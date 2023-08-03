#include "movablesolid.h"
#include "../common/utils.h"


MovableSolid::MovableSolid(Grid &g) : Solid(g)
{

};

bool MovableSolid::isMovable() const { return true; }

void MovableSolid::update() 
{
    // One cell below
    int target_x = x;
    int target_y = y + 1;


    if (grid.isCellEmpty(target_x, target_y))
    {
        moveTo(target_x, target_y);
        return;
    }

    if (grid.isInBoundary(target_x, target_y) && !grid.isCellEmpty(target_x, target_y))
    {
        if (grid.getElementAtCell(target_x, target_y).isLiquid())
        {
            swapWith(target_x, target_y);
            return;
        }

        if (grid.getElementAtCell(target_x, target_y).isSolid())
        {
            bool left;
            bool right;
            std::tie(left, right) = lookDiagonal();
            if (left && right)
            {
                if(utils::coinToss())
                {
                    moveTo(target_x-1, target_y);
                    return;
                }
                else
                {
                    moveTo(target_x+1, target_y);
                    return;
                }
            } 
            if (left)
            {
                moveTo(target_x-1, target_y);
                return;
            }
            if (right)
            {
                moveTo(target_x+1, target_y);
                return;
            }
        }
    }
    



}