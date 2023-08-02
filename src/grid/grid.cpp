#include "../elements/element.h"
#include "grid.h"
#include "../common/types.h"
#include <memory>
#include <vector>


Grid::Grid(int numRows, int numCols) : rows(numRows), cols(numCols)
{
    cells.resize(numRows);
    for (int i = 0; i < numRows; ++i) {
        cells[i].resize(numCols);
    }
}

bool Grid::isCellEmpty(int row, int col)
{
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return cells[row][col] == nullptr;
    }
    return false;
}


void Grid::addElement(ElementPtr element, int row, int col)
{
    if (row >= 0 && row < rows && col >= 0 && col < cols)
    {
        if (isCellEmpty(row, col) == true)
        {
            element->setPos(row, col);
            cells[row][col] = std::move(element);
        }
    }
}

Grid::~Grid(){

}