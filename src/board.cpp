#include "board.h"
#include <SFML/Graphics.hpp>

#include <iostream>

void Board::initializePieces()
{
    whitePawns = 0b0000000000000000000000000000000000000000000000001111111100000000;
    whiteRooks = 0b0000000000000000000000000000000000000000000000000000000010000001;
    whiteKnights = 0b0000000000000000000000000000000000000000000000000000000001000010;
    whiteBishops = 0b0000000000000000000000000000000000000000000000000000000000100100;
    whiteQueens = 0b0000000000000000000000000000000000000000000000000000000000001000;
    whiteKing = 0b0000000000000000000000000000000000000000000000000000000000010000;

    blackPawns = 0b0000000011111111000000000000000000000000000000000000000000000000;
    blackRooks = 0b1000000100000000000000000000000000000000000000000000000000000000;
    blackKnights = 0b0100001000000000000000000000000000000000000000000000000000000000;
    blackBishops = 0b0010010000000000000000000000000000000000000000000000000000000000;
    blackQueens = 0b0000100000000000000000000000000000000000000000000000000000000000;
    blackKing = 0b0001000000000000000000000000000000000000000000000000000000000000;

    allWhitePieces = 0b0000000000000000000000000000000000000000000000001111111111111111;
    allBlackPieces = 0b1111111111111111000000000000000000000000000000000000000000000000;
    allPieces = 0b1111111111111111000000000000000000000000000000001111111111111111;
}

sf::Texture Board::loadTextureFromFile(std::string path)
{
    sf::Texture temp;
    if (!temp.loadFromFile(path)) {
        std::cout << "Error loading file\n";
        throw std::exception("Error loading file");
    }
    return temp;
}

Board::Board(unsigned int width, unsigned int height, sf::RenderWindow& window)
    : window(window)
{
    initializePieces();

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

#include <bitset>

sf::Vector2i getPositionFromIndex(int index)
{
    return { index % 8, index / 8 };
}

void Board::drawPieces()
{
    // loop over black pawns example
    sf::Sprite sprite;
    sprite.setTexture(blackPawnTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, 125, 125));

    int64_t temp = blackPawns;
    for (int i = 0; i < 64; i++) {
        if ((temp & 1) == 1) {
            sf::Vector2i pos = getPositionFromIndex(i);
            sprite.setPosition(pos.x * 125, pos.y * 125);
            window.draw(sprite);
        }

        temp >>= 1;
    }

    // try for rooks
    sprite.setTexture(blackRookTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, 125, 125));

    temp = blackRooks;
    for (int i = 0; i < 64; i++) {
        if ((temp & 1) == 1) {
            sf::Vector2i pos = getPositionFromIndex(i);
            sprite.setPosition(pos.x * 125, pos.y * 125);
            window.draw(sprite);
        }

        temp >>= 1;
    }
}