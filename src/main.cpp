#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>

#include "board.h"

int main()
{
    uint32_t width = 1000u;
    uint32_t height = 1000u;
    bool userTurn = true;

    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(width, height)),
        "Chess Engine",
        sf::State::Windowed);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    Board board = Board(window);

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                continue;
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
            }

            if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                // set screen size
                // get the resized size
                sf::Vector2u size = resized->size;
                // setup my wanted aspect ratio
                float heightRatio = static_cast<float>(height) / width;
                float widthRatio = static_cast<float>(width) / height;
                // adapt the resized window to my wanted aspect ratio
                if (size.y * widthRatio <= size.x) {
                    size.x = size.y * widthRatio;
                } else if (size.x * heightRatio <= size.y) {
                    size.y = size.x * heightRatio;
                }
                // set the new size
                window.setSize(size);
            }

            if (userTurn) {
                board.processInput(*event);
            }
        }

        window.clear();

        board.drawBoard();
        board.drawPieces();

        window.display();
    }
}