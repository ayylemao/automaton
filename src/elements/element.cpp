#include "element.h"


Element::Element(Grid &g) : grid(g)
{
    position[0] = 0;
    position[1] = 0;
};

void Element::setPos(int row, int col){
    position[0] = row;
    position[1] = col;
}

std::tuple<int, int> Element::getPos() const {
    return std::make_tuple(position[0], position[1]);
}

bool Element::isSolid() const { return false; }
bool Element::isGas() const { return false; }
bool Element::isLiquid() const { return false; }
bool Element::isMovable() const { return false; }

Element::~Element()
{

}
