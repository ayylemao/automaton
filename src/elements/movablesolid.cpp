#include "movablesolid.h"


MovableSolid::MovableSolid(Grid &g) : Solid(g)
{

};

bool MovableSolid::isMovable() const { return true; }

void MovableSolid::update() 
{
       // One cell below
    velocity.y += grid.gravity;
    if (isFreeFalling) { velocity.x *= 0.9; }
    
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
	int lastValidX = x;
	int lastValidY = y;
	for (int i = 0; i < pathLength; i++)
	{
		std::tie(currX, currY) = pathVec[i];
        if (grid.isInBoundary(currX, currY))
        {
            Element* neighbour = grid.getElementAtCell(currX, currY);
            if (this == neighbour)
            {
                continue;
            }
            bool stopped = actOnNeighbouringElement
            (
                neighbour,
                currX,
                currY,
                i == pathLength - 1, i == 1, lastValidX, lastValidY, 0
            );
            if (stopped)
            {
                break;
            }
            lastValidX = currX;
            lastValidY = currY;
        }
        else
        {
            grid.replaceWithEmpty(x, y);
        }


        

	}
}

bool MovableSolid::actOnNeighbouringElement(Element* neighbour, int currX, int currY, bool isFinal, bool isFirst, int lastValidX, int lastValidY, int depth)
{
    if (neighbour->isEmpty())
    {
        if (isFinal)
        {
            isFreeFalling = true;
            swapWith(currX, currY);
        }
        else
        {
            return false;
        }
    }
    else if (neighbour->isSolid())
    {
        if (depth > 0) { return true; }
        if (isFinal)
        {
            swapWith(lastValidX, lastValidY);
            return true;
        }
        if (isFreeFalling)
        {
            float absY = std::max(std::abs(velocity.y), 105.f);
            velocity.x = velocity.x < 0 ? -absY : absY;
        }
        float vel_norm = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        float normX = velocity.x / vel_norm;
        float normY = velocity.y / vel_norm;
        int additionalX = getAdditional(normX);
        int additionalY = getAdditional(normY);

        Element* diagonalNeighbour = grid.getElementAtCell(x + additionalX, y + additionalY);
        if (isFirst)
        {
            velocity.y = getAverageVelOrGravity(velocity.y, neighbour->velocity.y);
        }
        //else
        //{
        //    velocity.y = -124;
        //}

        neighbour->velocity.y = velocity.y;
        velocity.x *= frictionFactor * neighbour->frictionFactor;
        if (diagonalNeighbour != nullptr)
        {
            bool stoppedDiagonally = actOnNeighbouringElement(
                diagonalNeighbour,
                x + additionalX,
                y + additionalY,
                true,
                false,
                lastValidX,
                lastValidY,
                depth + 1
            );
            if (!stoppedDiagonally)
            {
                isFreeFalling = true;
                return true;
            }
        }

        Element* adjacentNeighbour = grid.getElementAtCell(x + additionalX, y);

        if (adjacentNeighbour != nullptr && adjacentNeighbour != diagonalNeighbour)
        {
            bool stoppedAdjacently = actOnNeighbouringElement
            (
                adjacentNeighbour,
                x + additionalX,
                y,
                true,
                false,
                lastValidX,
                lastValidY,
                depth + 1
            );
            if (stoppedAdjacently) { velocity.x *= -1; }
            if (!stoppedAdjacently)
            {
                isFreeFalling = false;
                return true;
            }
        }
        isFreeFalling = false;

        swapWith(lastValidX, lastValidY);
        return true;
    }
    else if (neighbour->isGas())
    {
        if (isFinal)
        {
            swapWith(currX, currY);
            return true;
        }
        return false;
    }
    return false;
}

int MovableSolid::getAdditional(float val)
{
    if (val < -.1f)
    {
        return (int)std::floor(val);
    }
    else if (val > .1f)
    {
        return (int)std::ceil(val);
    }
    else
    {
        return 0;
    }
}

float MovableSolid::getAverageVelOrGravity(float vel, float otherVel)
{
    float avg = (vel + otherVel) / 2;
    if (avg > 0)
    {
        return avg;
    }
    else
    {
        return std::min(avg, 124.f);
    }
}


