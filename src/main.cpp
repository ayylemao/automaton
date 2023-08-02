#include <iostream>

#include "grid/grid.h"
#include "common/types.h"
#include "elements/sand.h"


int main(){
    auto grid = Grid(10, 10);

    std::unique_ptr<Sand> sand_ptr = std::make_unique<Sand>(grid);
    grid.addElement(std::move(sand_ptr), 5, 5);
    std::cout << "Sand is:\n";
    std::cout << "Liquid: " << grid.cells[5][5]->isLiquid() << '\n';
    std::cout << "Gas: " << grid.cells[5][5]->isGas() << '\n';
    std::cout << "Solid: " << grid.cells[5][5]->isSolid() << '\n';
    std::cout << "Movable Solid: " << grid.cells[5][5]->isMovable() << '\n';
    return 0;
}
