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

    velocity.y += grid.gravity * grid.dt;
    
    int x_velMod = velocity.x >= 0 ? 1 : -1;
        
    int final_x = x + (velocity.x * grid.dt);
    int final_y = y + (velocity.y * grid.dt);
    //std::cout << final_y << std::endl;

    auto pathVec = utils::bresenhamLine(x, y, final_x, final_y);

    int step = 0;
    int currX;
    int currY;
    int lastValidX;
    int lastValidY;
    for (auto& tar_pos : pathVec)
    {
        if (step == 0)
        {
            step += 1;
            continue;
        }

        std::tie(currX, currY) = tar_pos;
        std::cout << currX << " " << currY << " ";
        std::tie(lastValidX, lastValidY) = pathVec[step - 1];

        Element* currElement = grid.getElementAtCell(currX, currX);
        std::cout << "is solid? " << currElement->isSolid() << '\n';


        if (!grid.isInBoundary(currX, currX)) {
            std::cout << "called out of bounds";
            grid.replaceWithEmpty(lastValidX, lastValidY);
            return;
        }
        if (!currElement->isEmpty())
        {
            step += 1;
            continue;
        }
        else
        {
            if (currElement->isSolid())
            {
                velocity.y = 0;
                swapWith(lastValidX, lastValidY);
                return;
            }
        }
        step += 1;
    }
    std::tie(lastValidX, lastValidY) = pathVec.back();
    //std::cout << lastValidX << " " << lastValidX << std::endl;
    std::cout << '\n';
    swapWith(lastValidX, lastValidY);

}