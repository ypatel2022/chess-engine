#include "board.h"
#include <SFML/Graphics.hpp>

#include <iostream>

Board::Board(unsigned int width, unsigned int height, sf::RenderWindow& window)
    : window(window)
{

    sf::VertexArray gridCellVA(sf::Quads);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            float s = 125;
            int x = i * 125;
            int y = j * 125;

            sf::Vertex tl(sf::Vector2f(x, y));
            sf::Vertex bl(sf::Vector2f(x, y + s));
            sf::Vertex br(sf::Vector2f(x + s, y + s));
            sf::Vertex tr(sf::Vector2f(x + s, y));

            // is board piece odd or even?
            if ((x + y) % 2 == 1) {
                tl.color = bl.color = br.color = tr.color = dark;

            } else {
                tl.color = bl.color = br.color = tr.color = light;
            }

            // add to vertex array
            gridCellVA.append(tl);
            gridCellVA.append(bl);
            gridCellVA.append(br);
            gridCellVA.append(tr);
        }
    }

    // set vertex array
    this->vertexArray = gridCellVA;
}

Board::~Board()
{
}

void Board::drawBoard()
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    // convert it to world coordinates
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    // std::cout << worldPos.x << ", " << worldPos.y << std::endl;
    window.draw(this->vertexArray);
}
