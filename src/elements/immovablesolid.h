#ifndef IMMOVABLESOLID_H
#define IMMOVABLESOLID_H

#include "solid.h"

class ImmovableSolid : public Solid
{
    protected:
    //TODO
    public:
        ImmovableSolid(Grid &g);
        void update() override;

};


#endif