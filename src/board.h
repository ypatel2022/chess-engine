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

    uint64_t allWhitePieces;
    uint64_t allBlackPieces;
    uint64_t allPieces;

    bool whiteTurn;

    sf::RenderWindow& window;
    sf::VertexArray vertexArray;

    sf::Color dark = sf::Color(26, 30, 35);
    sf::Color light = sf::Color(140, 143, 188);

    const sf::Texture whitePawnTexture = loadTextureFromFile("../resources/whitePawn.png");
    const sf::Texture whiteRookTexture = loadTextureFromFile("../resources/whiteRook.png");
    const sf::Texture whiteKnightTexture = loadTextureFromFile("../resources/whiteKnight.png");
    const sf::Texture whiteBishopTexture = loadTextureFromFile("../resources/whiteBishop.png");
    const sf::Texture whiteQueenTexture = loadTextureFromFile("../resources/whiteQueen.png");
    const sf::Texture whiteKingTexture = loadTextureFromFile("../resources/whiteKing.png");

    const sf::Texture blackPawnTexture = loadTextureFromFile("../resources/blackPawn.png");
    const sf::Texture blackRookTexture = loadTextureFromFile("../resources/blackRook.png");
    const sf::Texture blackKnightTexture = loadTextureFromFile("../resources/blackKnight.png");
    const sf::Texture blackBishopTexture = loadTextureFromFile("../resources/blackBishop.png");
    const sf::Texture blackQueenTexture = loadTextureFromFile("../resources/blackQueen.png");
    const sf::Texture blackKingTexture = loadTextureFromFile("../resources/blackKing.png");

    void initializePieces();
    sf::Texture loadTextureFromFile(std::string path);

public:
    Board(unsigned int width, unsigned int height, sf::RenderWindow& window);
    ~Board();

    void drawBoard();
    void drawPieces();
};