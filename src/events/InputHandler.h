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
        void drawStaticElement(sf::Event &event);
        void spawnDynamicElement();
        void getLastKeyPressed(sf::Event &event);
        void drawCircle(int x, int y, int r);
        void changeRadius(sf::Event &event);
        void drawMouseRadius();
    private:
        Grid &grid;
        Renderer &renderer;
        float cellSize;
        int markerRadius;
        sf::Keyboard::Key lastKeyPressed;

};

#endif