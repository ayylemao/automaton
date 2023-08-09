#include "renderer.h"

Renderer::Renderer(sf::RenderWindow& window_r, Grid& g, float const width, float const height) 
: window(window_r), grid(g), window_width(width), window_height(height)
{
    margin = 0;
    cellSize = (std::min(width, height) - 2 * margin) / std::min(grid.x_grid, grid.y_grid);
}

void Renderer::setMargin(float s_margin)
{
    margin = s_margin;
    cellSize = (std::min(window_width, window_height) - 2 * margin) / std::min(grid.x_grid, grid.y_grid);
}

float Renderer::getCellSize()
{
    return cellSize;
}

void Renderer::drawGrid()
{
    sf::RectangleShape cellShape;
    for (int x = 0; x < grid.x_grid; x++)
    {
        for (int y = 0; y < grid.y_grid; y++)
        {
            if (!grid.getElementAtCell(x, y)->isEmpty())
            {
                cellShape.setPosition(static_cast<float>(x * cellSize), static_cast<float>(y * cellSize));
                cellShape.setSize(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
                cellShape.setFillColor(grid.getElementAtCell(x, y)->color);

                window.draw(cellShape);
            }
        }
    }
}