#include "utils.h"


bool utils::coinToss()
{
    return std::rand()&1;
}


std::vector<int> utils::shuffleXOrder(int const grid_x)
{
    std::vector<int> xOrder(grid_x);
    for (int i = 0; i < grid_x; i++)
    {
        xOrder[i] = i;
    }
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(xOrder.begin(), xOrder.end(), gen);
    return xOrder;
}