#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SFML/Window/Event.hpp>
#include "../grid/grid.h"
#include "../renderer/renderer.h"
#include "../elements/stone.h"
#include "../elements/sand.h"
#include "../elements/water.h"

class InputHandler
{
    public:
        InputHandler(Grid &g, Renderer &r);
        void clickDrawEvent(sf::Event &event);
        void clickPullEvent(sf::Event& event);
    private:
        Grid &grid;
        Renderer &renderer;
        float cellSize;
};

#endif