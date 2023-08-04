#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SFML/Window/Event.hpp>
#include "../grid/grid.h"
#include "../renderer/renderer.h"
#include "../elements/stone.h"

class InputHandler
{
    public:
        InputHandler(Grid &g, Renderer &r);
        void clickDrawEvent(sf::Event &event);
    private:
        Grid &grid;
        Renderer &renderer;
};

#endif