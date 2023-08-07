#include "InputHandler.h"

InputHandler::InputHandler(Grid &g, Renderer &r) : grid(g), renderer(r)
{
    //pass
}

void InputHandler::clickDrawEvent(sf::Event &event)
{
    int markerRadius = 4;
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(renderer.window);
        int gridX = mousePosition.x / renderer.getCellSize();
        int gridY = mousePosition.y / renderer.getCellSize();

        for (int i = 0; i<markerRadius; i++)
        {
            for (int j = 0; j<markerRadius; j++)
            {
                if (grid.isInBoundary(gridX + i, gridY + j))
                {
                    std::unique_ptr<Stone> stone_ptr = std::make_unique<Stone>(grid);

                    grid.cells[gridX + i][gridY + j].reset();
                    grid.addElement(std::move(stone_ptr), gridX + i, gridY + j);
                }
            }
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(renderer.window);
        int gridX = mousePosition.x / renderer.getCellSize();
        int gridY = mousePosition.y / renderer.getCellSize();

        for (int i = 0; i<markerRadius; i++)
        {
            for (int j = 0; j<markerRadius; j++)
            {
                if (grid.isInBoundary(gridX + i, gridY + j))
                {
                    std::unique_ptr<Sand> sand_ptr = std::make_unique<Sand>(grid);

                    grid.cells[gridX + i][gridY + j].reset();
                    grid.addElement(std::move(sand_ptr), gridX + i, gridY + j);
                }
            }
        }
    }
}