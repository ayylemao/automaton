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
    float frame_cap = 60;
    float windowWidth = 800;
    float windowHeight = 800;
    float dt = 1.0/frame_cap;
    float elapsed = 0.0;
    bool mousePressLeft = false;
    bool mousePressRight = false;

    auto grid = Grid(200, 200, dt);
    grid.init();
    sf::Clock clock;  

    for (int i = 0; i < 200; i++)
    {
        std::unique_ptr<Stone> stone = std::make_unique<Stone>(grid);
        grid.replaceElement(std::move(stone), i, 100);
    }

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Automaton");
    auto renderer = Renderer(window, grid, windowWidth, windowHeight);
    auto inputhandler = InputHandler(grid, renderer);
    renderer.setMargin(0);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window.close();}
                inputhandler.drawStaticElement(event);
                inputhandler.getLastKeyPressed(event);
                inputhandler.changeRadius(event);


                if (event.type == sf::Event::MouseButtonPressed &&  event.mouseButton.button == sf::Mouse::Left)
                {
                    mousePressLeft = true;
                }
                else if (event.type == sf::Event::MouseButtonReleased)
                {
                    mousePressLeft = false;
                }

                if (event.type == sf::Event::MouseButtonPressed &&  event.mouseButton.button == sf::Mouse::Right)
                {
                    mousePressRight = true;
                }
                else if (event.type == sf::Event::MouseButtonReleased)
                {
                    mousePressRight = false;
                }
                

        }

        elapsed += clock.restart().asSeconds();

        if (elapsed >= dt && !mousePressLeft)
        {
            //std::cout << 1.0/elapsed << '\n';
            elapsed = 0;
            window.clear(); 
            renderer.drawGrid();
            inputhandler.drawMouseRadius();
            window.display();
            if (mousePressRight) { inputhandler.spawnDynamicElement(); }
            grid.step();
        }
    }

    return 0;

}
