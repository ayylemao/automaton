#ifndef MOVABLESOLID_H
#define MOVABLESOLID_H

#include "solid.h"
#include "../grid/grid.h"

class MovableSolid : public Solid
{
    protected:
    //TODO
    public:
        MovableSolid(Grid &g);

        bool isMovable() const override;
        void update() override;
};


#endif