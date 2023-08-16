#include "stone.h"


Stone::Stone(Grid &g) : ImmovableSolid(g)
{
    color = sf::Color(
        sf::Uint8(105),
        sf::Uint8(105),
        sf::Uint8(105),
        sf::Uint8(199) + rand() % 56
    );
    frictionFactor = 0.5;
};
