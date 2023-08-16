#ifndef MOVABLESOLID_H
#define MOVABLESOLID_H

#include "solid.h"
#include "../grid/grid.h"
#include "../common/utils.h"

class MovableSolid : public Solid
{
    protected:
    //TODO
    public:
        MovableSolid(Grid &g);

        bool isMovable() const override;
        void update() override;
        bool actOnNeighbouringElement(Element* neighbour, int currX, int currY, bool isFinal, bool isFirst, int lastValidX, int lastValidY, int depth) override;
        int getAdditional(float val);
        float getAverageVelOrGravity(float vel, float othervel);
};


#endif