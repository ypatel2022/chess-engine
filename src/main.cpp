#include "board.h"
#include <SFML/Graphics.hpp>

int main()
{
    uint32_t width = 1000u;
    uint32_t height = 1000u;

    sf::RenderWindow window = sf::RenderWindow { { width, height }, "Chess Engine" };
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(144);

    Board board = Board(width, height, window);

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
            }
        }

        window.clear();

        board.drawBoard();

        window.display();
    }
}