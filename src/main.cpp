#include <iostream>
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
            std::cout << grid.isCellEmpty(y, x) << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}


int main(){
    auto grid = Grid(10, 10);
    printGrid(grid);

    //for (int j = 0; j<10; j++)
    //{
    //    std::unique_ptr<Stone> stone_ptr = std::make_unique<Stone>(grid);
    //    grid.addElement(std::move(stone_ptr), j, 9);
    //}

    for (int n = 0; n < 10; n++)
    {
        std::unique_ptr<Sand> sand_ptr = std::make_unique<Sand>(grid);
        grid.addElement(std::move(sand_ptr), 0, 0);
        for (int i = 0; i<10; i++)
        {
            for (int j = 0; j<10; j++)
            {
                if (grid.isCellEmpty(i, j) == false)
                {
                    grid.getElementAtCell(i, j).update();
                }
            }
        }
        printGrid(grid);
    }
    //grid.isCellEmpty(1, 2);
    //std::cout << "Sand is:\n";
    //std::cout << "Liquid: " << grid.cells[5][5]->isLiquid() << '\n';
    //std::cout << "Gas: " << grid.cells[5][5]->isGas() << '\n';
    //std::cout << "Solid: " << grid.cells[5][5]->isSolid() << '\n';
    //std::cout << "Movable Solid: " << grid.cells[5][5]->isMovable() << '\n';







    return 0;
}
