#ifndef MOVABLESOLID_H
#define MOVABLESOLID_H

#include "solid.h"

class MovableSolid : public Solid
{
    protected:
    //TODO
    public:
    MovableSolid(Grid &g);

    bool isMovable() const override;
};


#endif