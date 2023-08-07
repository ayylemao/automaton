#include <iostream>
#include <chrono>
#include <thread>
#include "grid/grid.h"
#include "common/types.h"
#include "elements/sand.h"
#include "elements/stone.h"
#include "elements/water.h"
#include "renderer/renderer.h"
#include "events/InputHandler.h"


int main(){
    float frame_cap = 60.0;
    auto grid = Grid(100, 100);
    float windowWidth = 500;
    float windowHeight = 500;
    float updateInterval = 1.0/frame_cap;
    float elapsed = 0.0;
    grid.init();
    sf::Clock clock;  

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Automaton");
    auto renderer = Renderer(window, grid, windowWidth, windowHeight);
    auto inputhandler = InputHandler(grid, renderer);
    renderer.setMargin(0);

    for (int j = 0; j<50; j++)
    {
        std::unique_ptr<Stone> stone_ptr = std::make_unique<Stone>(grid);
        grid.replaceElement(std::move(stone_ptr), 25+j, 70);
    }
    
    std::cout << grid.getElementAtCell(25, 70).isEmpty() << '\n';

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window.close();}
            inputhandler.clickDrawEvent(event);

        }

        elapsed += clock.restart().asSeconds();

        if (elapsed >= updateInterval)
        {
            std::cout << 1.0/elapsed << '\n';
            elapsed = 0;
            window.clear(); 
            renderer.drawGrid();
            window.display();
            std::unique_ptr<Water> water_ptr = std::make_unique<Water>(grid);
            grid.replaceElement(std::move(water_ptr), 50, 1);
            grid.step();
        }
    }

    return 0;

}
