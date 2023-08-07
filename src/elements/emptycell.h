#ifndef EMPTYCELL_H
#define EMPTYCELL_H

#include "element.h"

class EmptyCell : public Element
{
	public:
		EmptyCell(Grid& g);
		bool isEmpty() const override;
		void update() override;
		
};
#endif