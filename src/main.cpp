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
    auto grid = Grid(100, 100);
    float windowWidth = 500;
    float windowHeight = 500;
    float updateInterval = 0.025;
    float elapsed = 0.0;
    sf::Clock clock;  

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Automaton");
    auto renderer = Renderer(window, grid, windowWidth, windowHeight);
    auto inputhandler = InputHandler(grid, renderer);
    renderer.setMargin(0);

    for (int j = 0; j<50; j++)
    {
        std::unique_ptr<Stone> stone_ptr = std::make_unique<Stone>(grid);
        grid.addElement(std::move(stone_ptr), j+25, 70);
    }


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
            elapsed -= updateInterval;

            window.clear(); 
            renderer.drawGrid();
            window.display();
            std::unique_ptr<Water> water_ptr = std::make_unique<Water>(grid);
            grid.addElement(std::move(water_ptr), 50, 1);
            grid.step();
        }
    }

    return 0;






    //for (int n = 0; n < 1000; n++)
    //{
    //    std::unique_ptr<Sand> sand_ptr = std::make_unique<Sand>(grid);
    //    grid.addElement(std::move(sand_ptr), 15, 0);
    //    grid.step();
    //    printGrid(grid);
    //    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //    printGrid(grid);
    //}

    return 0;
}
