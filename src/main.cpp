#include <iostream>
#include <chrono>
#include <thread>
#include "grid/grid.h"
#include "common/types.h"
#include "elements/sand.h"
#include "elements/stone.h"

void printGrid(Grid& grid)
{
    for (int x = 0; x<grid.x_grid; x++)
    {
        for (int y = 0; y<grid.y_grid; y++)
        {
            if (grid.isCellEmpty(y, x))
            {
                std::cout << '0' << ' ';
            }
            else if (!grid.getElementAtCell(y, x).isMovable())
            {
                std::cout << '_' << ' ';
            }
            else
            {
                std::cout << 'S' << ' ';
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}


int main(){
    auto grid = Grid(10, 10);
    printGrid(grid);

    for (int j = 0; j<10; j++)
    {
        std::unique_ptr<Stone> stone_ptr = std::make_unique<Stone>(grid);
        grid.addElement(std::move(stone_ptr), j, 9);
    }
    for (int n = 0; n < 30; n++)
    {
        std::unique_ptr<Sand> sand_ptr = std::make_unique<Sand>(grid);
        grid.addElement(std::move(sand_ptr), 5, 0);
        grid.step();
        printGrid(grid);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        printGrid(grid);
    }

    return 0;
}
