#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Board {

    enum PieceColor {
        Black = 0,
        White = 1
    };

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

    uint64_t highlightedPossibleMoves;
    int selectedPieceIndex = -1;

    bool whiteTurn;

    sf::RenderWindow& window;
    sf::VertexArray vertexArray;

    sf::Color dark = sf::Color(26, 30, 35);
    sf::Color light = sf::Color(140, 143, 188);
    sf::Color highlighted = sf::Color(252, 186, 3, 150);

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
    int getIndexFromPosition(sf::Vector2i pos);

    int64_t removePiece(int64_t piecePositions, int index, PieceColor color);
    int64_t removePiece(int64_t piecePositions, sf::Vector2i boardPos, PieceColor color);

    // if adding a piece, there must not be anything there currently
    int64_t addPiece(int64_t piecePositions, int index, PieceColor color);
    int64_t addPiece(int64_t piecePositions, sf::Vector2i boardPos, PieceColor color);

    void highlightUserPosition(int index);

    void drawPiece(int64_t piecePositions, sf::Texture& pieceTexture);

    // move generation
    bool hasCollided(int index, PieceColor color, bool& addPiece);

    void generatePseudoPawnMoves(int index, PieceColor color);
    void generatePseudoKnightMoves(int index, PieceColor color);
    void generatePseudoRookMoves(int index, PieceColor color);
    void generatePseudoBishopMoves(int index, PieceColor color);
    void generatePseudoQueenMoves(int index, PieceColor color);
    void generatePseudoKingMoves(int index, PieceColor color);

public:
    Board(sf::RenderWindow& window);
    ~Board();

    void drawBoard();
    void drawPieces();
    void processInput(sf::Event& event);
};