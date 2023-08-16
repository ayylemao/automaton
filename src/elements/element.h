#ifndef ELEMENT_H
#define ELEMENT_H


#include <tuple>
#include <vector>
#include <cmath>
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
    sf::Vector2f carryOver;
    float dtVel;
    bool isFreeFalling;

public:

    bool hasMoved;
    float frictionFactor;
    sf::Color color;
    sf::Vector2f velocity;

    Element(Grid &g);

    std::tuple<int, int> getPos() const;
    void setPos(int row, int col);

    void moveTo(int row, int col);
    std::tuple<bool, bool> lookDiagonal();
    std::tuple<int, int> lookLeftRight();
    void swapWith(int row, int col);
    
    virtual bool actOnNeighbouringElement(Element* neighbour, int currX, int currY, bool isFinal, bool isFirst, int lastValidX, int lastValidY, int depth);
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