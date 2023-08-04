#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "../grid/grid.h"

class Renderer
{
    public:
        Renderer(sf::RenderWindow& window_r, Grid& g, float const width, float const height);
        void drawGrid();
        void setMargin(float s_margin);
        float getCellSize();
        sf::RenderWindow& window;

    private:
        Grid& grid;
        float const window_width;
        float const window_height;
        float margin;
        float cellSize;
};

#endif