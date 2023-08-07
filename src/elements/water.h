#ifndef WATER_H
#define WATER_H

#include "liquid.h"

class Water : public Liquid
{
public:
	Water(Grid& g);
	void updateColor() override;
};

#endif // !WATER_H
