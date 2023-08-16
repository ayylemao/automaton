#include "movablesolid.h"


MovableSolid::MovableSolid(Grid &g) : Solid(g)
{

};

bool MovableSolid::isMovable() const { return true; }

void MovableSolid::update() 
{
       // One cell below
    velocity.y += grid.gravity * grid.dt;
    
    float velXDeltaTimeFloat = velocity.x * grid.dt;
    float velYDeltaTimeFloat = velocity.y * grid.dt;
    int velXDeltaTime;
    int velYDeltaTime; 
	int xMod = (x < 0) ? -1 : 1;
	
    if (std::abs(velXDeltaTimeFloat) < 1.0)
    {
        carryOver.x += velXDeltaTimeFloat;
        velXDeltaTime = (int)carryOver.x;
        if (std::abs(velXDeltaTime) > 0)
        {
            carryOver.x = 0;
        }
    }
    else
    {
        carryOver.x = 0;
        velXDeltaTime = (int)velXDeltaTimeFloat;
    }

    if (std::abs(velYDeltaTimeFloat) < 1.0)
    {
        carryOver.y += velYDeltaTimeFloat;
        velYDeltaTime = (int)carryOver.y;
        if (std::abs(velYDeltaTime) > 0)
        {
            carryOver.y = 0;
        }
    }
    else
    {
        carryOver.y = 0;
        velYDeltaTime = (int)velYDeltaTimeFloat;
    }

    int final_x = x + velXDeltaTime;
    int final_y = y + velYDeltaTime;
    
	auto pathVec = utils::bresenhamLine(x, y, std::round(final_x), std::round(final_y));
	int pathLength = pathVec.size();
	int step = 0;
	int currX;
	int currY;
	int lastValidX;
	int lastValidY;

	for (int i = 0; i < pathLength; i++)
	{
		if (i == 0)
		{
			continue;
		}

		std::tie(currX, currY) = pathVec[i];
		std::tie(lastValidX, lastValidY) = pathVec[i - 1];

		Element* currElement = grid.getElementAtCell(currX, currY);

		if (!grid.isInBoundary(currX, currY)) {
			grid.replaceWithEmpty(x, y);
			return;
		}
		if (currElement->isEmpty())
		{
			continue;
		}
		else
		{
			if (currElement->isSolid())
			{
				velocity.x = (currElement->velocity.x + velocity.x) / 2;
				velocity.y = (currElement->velocity.y + velocity.y) / 2;
				if (currX == lastValidX && currY != lastValidY)
				{
					if (velocity.x == 0 && velocity.y != 0)
					{
						velocity.x = (utils::coinToss()) ? 0.7 * velocity.y : -0.7 * velocity.y;
						velocity.y = 0;
					}
				}
				velocity.x -= 0.9 * velocity.x * grid.dt * xMod;
				swapWith(lastValidX, lastValidY);
				return;
			}
		}
	}

		std::tie(lastValidX, lastValidY) = pathVec.back();
		swapWith(lastValidX, lastValidY);
		
	//grid.replaceWithEmpty(x, y);
}