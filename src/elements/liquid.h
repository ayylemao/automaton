#ifndef LIQUID_H
#define LIQUID_H

#include "element.h"
#include "../common/utils.h"

class Liquid : public Element
{
public:
	Liquid(Grid& g);
	bool isMovable() const override;
	bool isLiquid() const override;
	void update() override;
};

#endif // !LIQUID_H

