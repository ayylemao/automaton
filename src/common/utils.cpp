#include "utils.h"


bool utils::coinToss()
{
    return std::rand()&1;
}