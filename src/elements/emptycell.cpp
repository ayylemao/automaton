#include "emptycell.h"

EmptyCell::EmptyCell(Grid& g) : Element(g)
{

}

bool EmptyCell::isEmpty() const { return true; }
void EmptyCell::update() 
{
	//pass
}
