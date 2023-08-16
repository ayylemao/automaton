#include "grid.h"
#include "../elements/emptycell.h"



Grid::Grid(int numX, int numY, float dt_) : x_grid(numX), y_grid(numY), dt(dt_)
{
    cells.resize(numX*numY);
    step_counter = 0;
    gravity = 5;
    dtVel = 1.0 / dt;
}



size_t Grid::index(int x, int y) const
{
    return y + x_grid * x;
}

bool Grid::isCellEmpty(int x, int y)
{
    if (isInBoundary(x, y)) {
        if (cells[index(x, y)] == nullptr) { return true; }
        else { return false; }
    }
    else { return true; }
}

Element* Grid::getElementAtCell(int x, int y)
{
    if (isInBoundary(x, y))
    {
        return cells[index(x, y)].get();
    }
    else
    {
        return nullptr;
    }
}

void Grid::initElement(ElementPtr element, int to_x, int to_y)
{
    if (to_x >= 0 && to_x < x_grid && to_y >= 0 && to_y < y_grid)
    {
        if (isCellEmpty(to_x, to_y) == true)
        {
            element->setPos(to_x, to_y);
            cells[index(to_x, to_y)] = std::move(element);
        }
    }
}

void Grid::init()
{
    for (int i = 0; i < x_grid; i++)
    {
        for (int j = 0; j < y_grid; j++)
        {
            std::unique_ptr<EmptyCell> empty = std::make_unique<EmptyCell>(*this);
            this->initElement(std::move(empty), i, j); 
        }
    }
}

void Grid::replaceElement(ElementPtr element, int to_x, int to_y)
{
    if (to_x >= 0 && to_x < x_grid && to_y >= 0 && to_y < y_grid)
    {
            element->setPos(to_x, to_y);
            cells[index(to_x, to_y)].reset();
            cells[index(to_x, to_y)] = std::move(element);
    }
}

void Grid::replaceWithEmpty(int to_x, int to_y)
{
    if (to_x >= 0 && to_x < x_grid && to_y >= 0 && to_y < y_grid)
    {
        std::unique_ptr<EmptyCell> empty = std::make_unique<EmptyCell>(*this);
        empty->setPos(to_x, to_y);
        cells[index(to_x, to_y)].reset();
        cells[index(to_x, to_y)] = std::move(empty);
    }
    
}

bool Grid::isInBoundary(int x, int y)
{
    if (x >= 0 && x < x_grid && y >= 0 && y < y_grid)
    {
        return true; 
    }
    else 
    {
        return false;
    }
}

Element* Grid::getLinearElement(int i)
{
    return cells[i].get();
}

void Grid::printTuple(std::tuple<int, int> tup)
{
    int x;
    int y;
    std::tie(x, y) = tup;
    std::cout << "(" << x << ", " << y << ")\n";
}

void Grid::step()
{
    std::vector<int> xOrder = utils::shuffleXOrder(x_grid);
    for (int y = y_grid - 1 ; y >= 0; --y)
		for (int x : xOrder)
		{
		    Element *element = getElementAtCell(x, y);
            step_counter += 1;
			if (!element->isEmpty() && !element->hasMoved)
			{
				element->update();
                element->hasMoved = true;
			}
		}
    for (int i = 0; i < x_grid * y_grid; i++)
    {
        Element* element = getLinearElement(i);
        if (element->hasMoved)
        {
			element->hasMoved = false;
        }
    }
    step_counter = 0;
}

Grid::~Grid(){

}