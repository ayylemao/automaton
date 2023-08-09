#ifndef ELEMENT_H
#define ELEMENT_H


#include <tuple>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../grid/grid.h"

//Forward declaration
class Grid;

class Element
{
protected:
    int x;
    int y;
    Grid &grid;
    int dispersionRate;

public:

    bool hasMoved;
    sf::Color color;

    Element(Grid &g);

    std::tuple<int, int> getPos() const;
    void setPos(int row, int col);

    void moveTo(int row, int col);
    std::tuple<bool, bool> lookDiagonal();
    std::tuple<bool, bool> lookLeftRight();
    void swapWith(int row, int col);
    
    virtual int getDispersionRate() const;
    virtual bool isSolid() const; 
    virtual bool isGas() const;
    virtual bool isLiquid() const;
    virtual bool isMovable() const;
    virtual bool isEmpty() const;

    virtual void update() = 0;
    virtual ~Element();
};


#endif