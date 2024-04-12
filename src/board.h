#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Board {
private:
    uint64_t whitePawns;
    uint64_t whiteKnights;
    uint64_t whiteBishops;
    uint64_t whiteRooks;
    uint64_t whiteQueens;
    uint64_t whiteKing;

    uint64_t blackPawns;
    uint64_t blackKnights;
    uint64_t blackBishops;
    uint64_t blackRooks;
    uint64_t blackQueens;
    uint64_t blackKing;

    bool whiteTurn;

    sf::RenderWindow& window;
    sf::VertexArray vertexArray;

    sf::Color dark = sf::Color(26, 30, 35);
    sf::Color light = sf::Color(140, 143, 188);

public:
    Board(unsigned int width, unsigned int height, sf::RenderWindow& window);
    ~Board();

    void drawBoard();
};