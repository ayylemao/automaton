#include "movablesolid.h"


MovableSolid::MovableSolid(Grid &g) : Solid(g)
{

};

bool MovableSolid::isMovable() const { return true; }

void MovableSolid::update() 
{
    int target_x = x;
    int target_y = y + 1;
    if (grid.isInBoundary(target_x, target_y))
    {

    }
    if (grid.isCellEmpty(target_x, target_y))
    {
        moveTo(target_x, target_y);
        return;
    }
    
    //if (grid.getElementAtCell(target_x, target_y).isLiquid())
    //{
    //    swapWith(target_x, target_y);
    //}



}