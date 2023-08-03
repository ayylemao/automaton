#include "grid.h"


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

const Element& Grid::getElementAtCell(int row, int col)
{
    return *cells[row][col];
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