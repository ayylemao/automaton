#include "solid.h"


Solid::Solid(Grid &g) : Element(g)
{

}

bool Solid::isSolid() const { return true; }
bool Solid::isMovable() const { return false; }