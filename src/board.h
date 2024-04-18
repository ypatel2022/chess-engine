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

    sf::Texture whitePawnTexture = loadTextureFromFile("../resources/whitePawn.png");
    sf::Texture whiteRookTexture = loadTextureFromFile("../resources/whiteRook.png");
    sf::Texture whiteKnightTexture = loadTextureFromFile("../resources/whiteKnight.png");
    sf::Texture whiteBishopTexture = loadTextureFromFile("../resources/whiteBishop.png");
    sf::Texture whiteQueenTexture = loadTextureFromFile("../resources/whiteQueen.png");
    sf::Texture whiteKingTexture = loadTextureFromFile("../resources/whiteKing.png");

    sf::Texture blackPawnTexture = loadTextureFromFile("../resources/blackPawn.png");
    sf::Texture blackRookTexture = loadTextureFromFile("../resources/blackRook.png");
    sf::Texture blackKnightTexture = loadTextureFromFile("../resources/blackKnight.png");
    sf::Texture blackBishopTexture = loadTextureFromFile("../resources/blackBishop.png");
    sf::Texture blackQueenTexture = loadTextureFromFile("../resources/blackQueen.png");
    sf::Texture blackKingTexture = loadTextureFromFile("../resources/blackKing.png");

    void initializePieces();
    sf::Texture loadTextureFromFile(std::string path);

    sf::Vector2i getPositionFromIndex(int index);
    void drawPiece(int64_t piecePositions, sf::Texture& pieceTexture);

public:
    Board(sf::RenderWindow& window);
    ~Board();

    void drawBoard();
    void drawPieces();
};