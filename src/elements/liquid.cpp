#include "liquid.h"


Liquid::Liquid(Grid& g) : Element(g)
{

}

bool Liquid::isLiquid() const { return true; }
bool Liquid::isMovable() const { return true; }


void Liquid::update()
{
    updateColor();
    // One cell below
    int target_x = x;
    int target_y = y + 1;
    if (grid.isCellEmpty(target_x, target_y))
    {
        moveTo(target_x, target_y);
        return;
    }

    // Left and right since below is filled
    target_x = x;
    target_y = y;

    if (grid.isInBoundary(target_x, target_y) && !grid.isCellEmpty(target_x, target_y))
    {
        if (grid.getElementAtCell(target_x, target_y).isSolid() || grid.getElementAtCell(target_x, target_y).isLiquid())
        {
            bool left;
            bool right;
            std::tie(left, right) = lookLeftRight();	

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
            else if (right)
            {
                moveTo(target_x+1, target_y);
                return;
            }
        }
    }


}
