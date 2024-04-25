#include <SFML/Graphics.hpp>
#include <iostream>

#include "board.h"

int main()
{
    uint32_t width = 1000u;
    uint32_t height = 1000u;
    bool userTurn = true;

    sf::RenderWindow window = sf::RenderWindow { { width, height }, "Chess Engine", sf::Style::Titlebar | sf::Style::Close };
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(144);

    Board board = Board(window);

    while (window.isOpen()) {
        for (auto event = sf::Event {}; window.pollEvent(event);) {

            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            case sf::Event::Resized:
                // set screen size
                // get the resized size
                sf::Vector2u size = window.getSize();
                // setup my wanted aspect ratio
                float heightRatio = height / width;
                float widthRatio = width / height;
                // adapt the resized window to my wanted aspect ratio
                if (size.y * widthRatio <= size.x) {
                    size.x = size.y * widthRatio;
                } else if (size.x * heightRatio <= size.y) {
                    size.y = size.x * heightRatio;
                }
                // set the new size
                window.setSize(size);
                break;
            }

            if (userTurn) {
                board.processInput(event);
            }
        }

        window.clear();

        board.drawBoard();
        board.drawPieces();

        window.display();
    }
}