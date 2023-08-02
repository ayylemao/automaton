#ifndef SOLID_H
#define SOLID_H

#include "element.h"

class Solid : public Element
{
    protected:
    //TODO
    public:
        Solid(Grid &g);
    
        virtual bool isMovable() const;

        bool isSolid() const override;
};


#endif