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
    
	if (grid.isInBoundary(x, y + 1))
	{
		if (grid.getElementAtCell(x, y + 1)->isEmpty())
		{
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
				std::tie(lastValidX, lastValidY) = pathVec[step - 1];

				Element* currElement = grid.getElementAtCell(currX, currY);


				if (!grid.isInBoundary(currX, currY)) {
					std::cout << currX << " " << currY << " " << lastValidX << " " << lastValidY << std::endl;
					grid.replaceWithEmpty(x, y);
					return;
				}
				if (currElement->isEmpty())
				{
					step += 1;
					continue;
				}
				else
				{
					if (currElement->isSolid())
					{
						velocity.y = 1/grid.dt;
						swapWith(lastValidX, lastValidY);
						return;
					}
				}
				step += 1;
			}
			std::tie(lastValidX, lastValidY) = pathVec.back();
			swapWith(lastValidX, lastValidY);
		}
		else
		{
			int target_x = x;
			int target_y = y + 1;

			Element* target_cell = grid.getElementAtCell(target_x, target_y);

			if (target_cell->isSolid())
			{
				bool left;
				bool right;
				std::tie(left, right) = lookDiagonal();
				if (left && right)
				{
					if (grid.step_counter % 2 == 0)
					{
						swapWith(target_x - 1, target_y);
						velocity.y = 1/grid.dt;
						return;
					}
					else
					{
						swapWith(target_x + 1, target_y);
						velocity.y = 1/grid.dt;
						return;
					}
				}
				else if (left)
				{
					swapWith(target_x - 1, target_y);
					velocity.y = 1/grid.dt;
					return;
				}
				else if (right)
				{
					swapWith(target_x + 1, target_y);
					velocity.y = 1/grid.dt;
					return;
				}
				else
				{
					velocity.y = 1/grid.dt;
					return;
				}
			}
		}
	}
	else
	{
		grid.replaceWithEmpty(x, y);
	}
}