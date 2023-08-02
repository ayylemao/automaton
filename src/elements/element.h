#ifndef ELEMENT_H
#define ELEMENT_H

#include <tuple>
#include <vector>

//Forward declaration
class Grid;

class Element
{
protected:
    int position[2];
    Grid &grid;

public:
    Element(Grid &g);

    std::tuple<int, int> getPos() const;
    void setPos(int row, int col);

    virtual bool isSolid() const; 
    virtual bool isGas() const;
    virtual bool isLiquid() const;
    virtual bool isMovable() const;

    virtual void update() = 0;
    virtual ~Element();
};


#endif