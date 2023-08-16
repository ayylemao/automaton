#include "sand.h"


Sand::Sand(Grid &g) : MovableSolid(g)
{
    color = sf::Color(
        sf::Uint8(255),                       // Red channel
        sf::Uint8(200 + rand() % 56),          // Green channel with random variation
        sf::Uint8(100 + rand() % 56),          // Blue channel with random variation
        sf::Uint8(255)                        // Alpha channel
    );
    frictionFactor = 0.9;
};

