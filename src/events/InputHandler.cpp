#include "InputHandler.h"

InputHandler::InputHandler(Grid &g, Renderer &r) : grid(g), renderer(r)
{
    cellSize = renderer.getCellSize();
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

                    grid.replaceElement(std::move(stone_ptr), gridX + i, gridY + j);
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

                    grid.replaceElement(std::move(sand_ptr), gridX + i, gridY + j);
                }
            }
        }
    }
}


// TODO: fix so one can actually drag
void InputHandler::clickPullEvent(sf::Event& event) {
    static bool isDrawing = false;
    static int startX;
    static int startY;
    int startGridX;
    int startGridY;
    static float elapsed = 0;

    if (isDrawing)
    {
		elapsed += renderer.renderClock.getElapsedTime().asSeconds() - elapsed;
    }
    
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        isDrawing = true;
        startX = event.mouseButton.x;
        startY = event.mouseButton.y;
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        isDrawing = false;
        elapsed = 0;
    }

	if (isDrawing) {
        int endX = sf::Mouse::getPosition(renderer.window).x;
        int endY = sf::Mouse::getPosition(renderer.window).y;
        std::cout << "StartX: " << startX << ' ' << startY << std::endl;
        startGridX = startX / cellSize;
        startGridY = startY / cellSize;
        endX = endX / cellSize;
        endY = endY / cellSize;
        std::vector<std::tuple<int, int>> linePixels = utils::bresenhamLine(startGridX, startGridY, endX, endY);


        for (const auto& pixel : linePixels) {
            int x = std::get<0>(pixel);
            int y = std::get<1>(pixel);
            if (grid.isInBoundary(x, y))
            {
                std::unique_ptr<Water> sand_ptr = std::make_unique<Water>(grid);
                grid.replaceElement(std::move(sand_ptr), x, y);
            }

        }
		if (elapsed > 0.01)
			{
				startX = sf::Mouse::getPosition(renderer.window).x;
				startY = sf::Mouse::getPosition(renderer.window).y;
				elapsed = 0;
			} 

        renderer.window.clear();
        renderer.drawGrid();
        renderer.window.display();
	}
}
