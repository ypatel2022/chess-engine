#include "board.h"
#include <SFML/Graphics.hpp>

#include <iostream>

Board::Board(unsigned int width, unsigned int height, sf::RenderWindow& window)
    : window(window)
{

    sf::VertexArray cellVertexArray(sf::Quads);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            float s = 125;
            int x = i * 125;
            int y = j * 125;

            sf::Vertex v1(sf::Vector2f(x, y));
            sf::Vertex v2(sf::Vector2f(x, y + s));
            sf::Vertex v3(sf::Vector2f(x + s, y + s));
            sf::Vertex v4(sf::Vector2f(x + s, y));

            // is board piece odd or even?
            if ((x + y) % 2 == 1) {
                v1.color = v2.color = v3.color = v4.color = dark;

            } else {
                v1.color = v2.color = v3.color = v4.color = light;
            }

            // add to vertex array
            cellVertexArray.append(v1);
            cellVertexArray.append(v2);
            cellVertexArray.append(v3);
            cellVertexArray.append(v4);
        }
    }

    // set vertex array
    this->vertexArray = cellVertexArray;
}

Board::~Board()
{
}

void Board::drawBoard()
{
    window.draw(this->vertexArray);
}
