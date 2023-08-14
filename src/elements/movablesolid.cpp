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
	bool xMod = (x < 0) ? true : false;
	
    if (std::abs(velXDeltaTimeFloat) < 1)
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

    if (std::abs(velYDeltaTimeFloat) < 1)
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

    int final_x = x + velXDeltaTimeFloat;
    int final_y = y + velYDeltaTimeFloat;
    
	auto pathVec = utils::bresenhamLine(x, y, final_x, final_y);
	int step = 0;
	int currX;
	int currY;
	int lastValidX;
	int lastValidY;
	//bool xDiffLarger = std::abs(x - final_x) - std::abs(y - final_y) >= 0 ? true : false;

	for (auto& tar_pos : pathVec)
	{
		if (step == 0)
		{
			step += 1;
			continue;
		}

		std::tie(currX, currY) = tar_pos;
		std::tie(lastValidX, lastValidY) = pathVec[step - 1];

		Element* currElement = grid.getElementAtCell(currX, currY);

		if (!grid.isInBoundary(currX, currY)) {
			grid.replaceWithEmpty(x, y);
			return;
		}
		if (currElement->isEmpty())
		{
			step += 1;
			if (grid.getElementAtCell(currX, currY + 1)->isSolid())
			{
				velocity.x *= 0.01;
			}
			continue;
		}
		else
		{
			if (currElement->isSolid())
			{
				//velocity.x = (currElement->velocity.x + velocity.x) / 2;
				velocity.y = (currElement->velocity.y + velocity.y) / 2;

				if (currY != lastValidY && lastValidX == currX)
				{
					if (velocity.x != 0)
					{
						velocity.x += 0.707 * velocity.y * xMod;
						velocity.y = 0;
						velocity.x *= 0.01;
					}
					else
					{
						velocity.x = (grid.step_counter % 2 == 0) ? 0.707 * velocity.y : -0.707 * velocity.y;
						velocity.y = 0;
					}
				}
				std::cout << "called " << velocity.x << std::endl;

				swapWith(lastValidX, lastValidY);
				return;
			}
		}
		step += 1;
	}

		std::tie(lastValidX, lastValidY) = pathVec.back();
		swapWith(lastValidX, lastValidY);
		
	//grid.replaceWithEmpty(x, y);
}