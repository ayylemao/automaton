#ifndef SAND_H
#define SAND_H

#include "movablesolid.h"


class Sand : public MovableSolid
{
    protected:
    // TODO
    public:
    Sand(Grid &g);
    
    void update() override;

};



#endif