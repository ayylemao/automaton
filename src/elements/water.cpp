#include "water.h"


Water::Water(Grid& g) : Liquid(g)
{
    color = sf::Color(
        sf::Uint8(0),                       // Red channel
        sf::Uint8(150 + rand() % 56),          // Green channel with random variation
        sf::Uint8(200 + rand() % 46),          // Blue channel with random variation
        sf::Uint8(255)                        // Alpha channel
    );
}

void Water::updateColor() 
{
    color = sf::Color(
        sf::Uint8(0),                       // Red channel
        sf::Uint8(150 + rand() % 56),          // Green channel with random variation
        sf::Uint8(200 + rand() % 56),          // Blue channel with random variation
        sf::Uint8(255)                        // Alpha channel
    );
}