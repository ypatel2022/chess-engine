#include "board.h"
#include "utils.h"
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

    allWhitePieces = whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteQueens | whiteKing;
    allBlackPieces = blackPawns | blackRooks | blackKnights | blackBishops | blackQueens | blackKing;

    allPieces = allBlackPieces | allWhitePieces;

    highlightedPossibleMoves = 0b0000000000000000000000000000000000000000000000000000000000000000;
}

sf::Texture Board::loadTextureFromFile(std::string path)
{
    sf::Texture temp;
    if (!temp.loadFromFile(path)) {
        std::cout << "Error loading file\n";
        throw std::runtime_error("Error loading file");
    }
    return temp;
}

Board::Board(sf::RenderWindow& window)
    : window(window)
{
    initializePieces();

    sf::VertexArray gridCellVA(sf::Quads);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            float s = 125;
            int x = j * s;
            int y = i * s;

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
    vertexArray = gridCellVA;
}

Board::~Board()
{
}

void Board::drawBoard()
{
    sf::VertexArray highlightedCellVA(sf::Quads);

    if (selectedPieceIndex != -1) {
        // draw the highlighted square

        sf::Vector2i pos = getPositionFromIndex(selectedPieceIndex);

        int s = 125;
        int x = pos.x * s;
        int y = pos.y * s;

        sf::Vertex tl(sf::Vector2f(x, y));
        sf::Vertex bl(sf::Vector2f(x, y + s));
        sf::Vertex br(sf::Vector2f(x + s, y + s));
        sf::Vertex tr(sf::Vector2f(x + s, y));

        tl.color = bl.color = br.color = tr.color = highlighted;

        // add to vertex array
        highlightedCellVA.append(tl);
        highlightedCellVA.append(bl);
        highlightedCellVA.append(br);
        highlightedCellVA.append(tr);
    }

    // update vertex array with highlighted squares
    for (size_t i = 0; i < 64; i++) {
        if (((highlightedPossibleMoves >> i) & 1) == 1) {
            // get vertex indexes

            sf::Vector2i pos = getPositionFromIndex(i);

            int s = 125;
            int x = pos.x * s;
            int y = pos.y * s;

            sf::Vertex tl(sf::Vector2f(x, y));
            sf::Vertex bl(sf::Vector2f(x, y + s));
            sf::Vertex br(sf::Vector2f(x + s, y + s));
            sf::Vertex tr(sf::Vector2f(x + s, y));

            tl.color = bl.color = br.color = tr.color = highlighted;

            // add to vertex array
            highlightedCellVA.append(tl);
            highlightedCellVA.append(bl);
            highlightedCellVA.append(br);
            highlightedCellVA.append(tr);
        }
    }

    window.draw(vertexArray);
    window.draw(highlightedCellVA);
}

sf::Vector2i Board::getPositionFromIndex(int index)
{
    return { index % 8, index / 8 };
}

int Board::getIndexFromPosition(sf::Vector2i pos)
{
    return 8 * (int)pos.y + (int)pos.x;
}

int64_t Board::removePiece(int64_t piecePositions, int index, PieceColor color)
{
    // set index bit to zero
    if (((piecePositions >> index) & 1) == 1) {
        piecePositions &= ~((int64_t)1 << index);
        allPieces &= ~((int64_t)1 << index);

        if (color == PieceColor::White) {
            allWhitePieces &= ~((int64_t)1 << index);
        } else if (color == PieceColor::Black) {
            allBlackPieces &= ~((int64_t)1 << index);
        }
    }
    return piecePositions;
}

int64_t Board::removePiece(int64_t piecePositions, sf::Vector2i boardPos, PieceColor color)
{
    int index = getIndexFromPosition({ (int)boardPos.x / 125, (int)boardPos.y / 125 });
    return removePiece(piecePositions, index, color);
}

int64_t Board::addPiece(int64_t piecePositions, int index, PieceColor color)
{
    // set index bit to one
    if (((allPieces >> index) & 1) == 0) {
        piecePositions |= ((int64_t)1 << index);
        allPieces |= ((int64_t)1 << index);

        if (color == PieceColor::White) {
            allWhitePieces |= ((int64_t)1 << index);
        } else if (color == PieceColor::Black) {
            allBlackPieces |= ((int64_t)1 << index);
        }
    }
    return piecePositions;
}

int64_t Board::addPiece(int64_t piecePositions, sf::Vector2i boardPos, PieceColor color)
{
    int index = getIndexFromPosition({ (int)boardPos.x / 125, (int)boardPos.y / 125 });
    return addPiece(piecePositions, index, color);
}

void Board::drawPiece(int64_t piecePositions, sf::Texture& pieceTexture)
{
    sf::Sprite sprite;
    sprite.setTexture(pieceTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, 125, 125));

    for (int i = 0; i < 64; i++) {
        if ((piecePositions & 1) == 1) {
            sf::Vector2i pos = getPositionFromIndex(i);
            sprite.setPosition(pos.x * 125, pos.y * 125);
            window.draw(sprite);
        }

        piecePositions >>= 1;
    }
}

bool Board::hasCollided(int index, PieceColor color, bool& addPiece)
{
    // check collision
    if (((allPieces >> index) & 1) == 1) {
        // check if it was white
        if (((allWhitePieces >> index) & 1) == 1) {
            if (color == Black) {
                // add
                addPiece = true;
            }
            return true;
        }
        // check if it was black
        if (((allBlackPieces >> index) & 1) == 1) {
            if (color == White) {
                // add
                addPiece = true;
            }
            return true;
        }
    }

    return false;
}

void Board::generatePseudoPawnMoves(int index, PieceColor color)
{
    // check if in home row
    // home row if row is 1 (white) or 6 (black)
    int row = index / 8;
    int i;

    if (color == Black && row != 0) {

        i = index - 8;
        if (((allPieces >> i) & 1) == 0) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        }

        // add home row double move
        if (row == 6) {
            if (((allPieces >> i) & 1) == 0) {
                i = index - 16;
                if (((allPieces >> i) & 1) == 0) {
                    highlightedPossibleMoves |= ((int64_t)1 << i);
                }
            }
        }

        // now add any kills
        // top left is -9
        // top right is -7
        i = index - 9;
        if (((allWhitePieces >> i) & 1) == 1 && index % 8 != 0) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        }
        i = index - 7;
        if (((allWhitePieces >> i) & 1) == 1 && index % 8 != 7) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        }
    }

    else if (color == White && row != 7) {

        i = index + 8;
        if (((allPieces >> i) & 1) == 0) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        }

        // add home row double move
        if (row == 6) {
            if (((allPieces >> i) & 1) == 0) {
                i = index + 16;
                if (((allPieces >> i) & 1) == 0) {
                    highlightedPossibleMoves |= ((int64_t)1 << i);
                }
            }
        }

        // now add any kills
        // top left is -9
        // top right is -7
        i = index + 9;
        if (((allWhitePieces >> i) & 1) == 1 && index % 8 != 0) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        }
        i = index + 7;
        if (((allWhitePieces >> i) & 1) == 1 && index % 8 != 7) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        }
    }
}

void Board::generatePseudoKnightMoves(int index, PieceColor turnColor)
{
    // 17, 15, 10, 6, -6, -10, -15, -17
    const int moves[] = { 17, 15, 10, 6, -6, -10, -15, -17 };

    int pos;
    for (size_t i = 0; i < 8; i++) {
        int pos = index + moves[i];

        // first check that pos exists within [0,63]
        if (outOfRange(pos, 0, 63)) {
            continue;
        }

        // double check no teleport is happening
        if (moves[i] == 6 || moves[i] == -10) {
            // make sure pos.x is greater than >= 2
            if (index % 8 < 2) {
                continue;
            }
        } else if (moves[i] == -6 || moves[i] == 10) {
            if (index % 8 > 5) {
                continue;
            }
        } else if (moves[i] == 15 || moves[i] == -17) {
            if (index % 8 < 1) {
                continue;
            }
        } else if (moves[i] == -15 || moves[i] == 17) {
            if (index % 8 > 6) {
                continue;
            }
        }

        // check if pos is not current color
        if (turnColor == PieceColor::White) {
            if (((allWhitePieces >> pos) & 1) == 0) {
                // make highlightedPossibleMoves a 1 then at pos
                highlightedPossibleMoves |= ((int64_t)1 << pos);
            }

        } else if (turnColor == PieceColor::Black) {
            if (((allBlackPieces >> pos) & 1) == 0) {
                // make highlightedPossibleMoves a 1 then at pos
                highlightedPossibleMoves |= ((int64_t)1 << pos);
            }
        }
    }
}

void Board::generatePseudoRookMoves(int index, PieceColor color)
{
    // look in all directions (max of 8 spaces to move)

    bool addPiece = false;

    // down
    for (int i = index + 8; i < 64; i += 8) {
        if (!hasCollided(i, color, addPiece)) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        } else {
            if (addPiece) {
                highlightedPossibleMoves |= ((int64_t)1 << i);
                addPiece = false;
            }
            break;
        }
    }

    // up
    for (int i = index - 8; i >= 0; i -= 8) {
        if (!hasCollided(i, color, addPiece)) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        } else {
            if (addPiece) {
                highlightedPossibleMoves |= ((int64_t)1 << i);
                addPiece = false;
            }
            break;
        }
    }

    // left
    for (int i = index - 1; i >= 8 * (index / 8); i--) {
        if (!hasCollided(i, color, addPiece)) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        } else {
            if (addPiece) {
                highlightedPossibleMoves |= ((int64_t)1 << i);
                addPiece = false;
            }
            break;
        }
    }

    // right
    for (int i = index + 1; i < 8 * (index / 8 + 1); i++) {
        if (!hasCollided(i, color, addPiece)) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        } else {
            if (addPiece) {
                highlightedPossibleMoves |= ((int64_t)1 << i);
                addPiece = false;
            }
            break;
        }
    }
}

void Board::generatePseudoBishopMoves(int index, PieceColor color)
{
    bool addPiece = false;

    // look down+right
    // when encountering an 8 in the "x" pos, break out of loop to avoid teleportation
    for (int i = index + 9; i < 64; i += 9) {

        if (index % 8 == 7) {
            break;
        }

        if (!hasCollided(i, color, addPiece)) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        } else {
            if (addPiece) {
                highlightedPossibleMoves |= ((int64_t)1 << i);
                addPiece = false;
            }
            break;
        }

        if (i % 8 == 7) {
            break;
        }
    }

    // look down+left
    for (int i = index + 7; i < 64; i += 7) {

        // skip if index is on the edge
        if (index % 8 == 0) {
            break;
        }

        if (!hasCollided(i, color, addPiece)) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        } else {
            if (addPiece) {
                highlightedPossibleMoves |= ((int64_t)1 << i);
                addPiece = false;
            }
            break;
        }

        if (i % 8 == 0) {
            break;
        }
    }

    // look up+right
    for (int i = index - 7; i >= 0; i -= 7) {

        if (index % 8 == 7) {
            break;
        }

        if (!hasCollided(i, color, addPiece)) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        } else {
            if (addPiece) {
                highlightedPossibleMoves |= ((int64_t)1 << i);
                addPiece = false;
            }
            break;
        }

        if (i % 8 == 7) {
            break;
        }
    }

    // look up+left
    for (int i = index - 9; i >= 0; i -= 9) {

        if (index % 8 == 0) {
            break;
        }

        if (!hasCollided(i, color, addPiece)) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        } else {
            if (addPiece) {
                highlightedPossibleMoves |= ((int64_t)1 << i);
                addPiece = false;
            }
            break;
        }

        if (i % 8 == 0) {
            break;
        }
    }
}

void Board::generatePseudoQueenMoves(int index, PieceColor color)
{
    generatePseudoBishopMoves(index, color);
    generatePseudoRookMoves(index, color);
}

void Board::generatePseudoKingMoves(int index, PieceColor color)
{
    bool addPiece = false;
    int i;

    // checking top, make sure valid position
    if (index / 8 != 0) {

        // check top left, -9
        i = index - 9;
        if (index % 8 != 0) {
            if (((allBlackPieces >> i) & 1) == 0) {
                highlightedPossibleMoves |= ((int64_t)1 << i);
            }
        }

        // check top, -8
        i = index - 8;
        if (((allBlackPieces >> i) & 1) == 0) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        }

        // check top left, -7
        i = index - 7;
        if (index % 8 != 7) {
            if (((allBlackPieces >> i) & 1) == 0) {
                highlightedPossibleMoves |= ((int64_t)1 << i);
            }
        }
    }

    // check right, +1
    i = index + 1;
    if (index % 8 != 7) {
        if (((allBlackPieces >> i) & 1) == 0) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        }
    }

    // check left, -1
    i = index - 1;
    if (index % 8 != 0) {
        if (((allBlackPieces >> i) & 1) == 0) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        }
    }

    // check bottom
    if (index / 8 != 7) {
        // check top left, 9
        i = index + 9;
        if (index % 8 != 7) {
            if (((allBlackPieces >> i) & 1) == 0) {
                highlightedPossibleMoves |= ((int64_t)1 << i);
            }
        }

        // check top, 8
        i = index + 8;
        if (((allBlackPieces >> i) & 1) == 0) {
            highlightedPossibleMoves |= ((int64_t)1 << i);
        }

        // check top left, 7
        i = index + 7;
        if (index % 8 != 0) {
            if (((allBlackPieces >> i) & 1) == 0) {
                highlightedPossibleMoves |= ((int64_t)1 << i);
            }
        }
    }
}

void Board::drawPieces()
{
    // draw the black pieces
    drawPiece(blackBishops, blackBishopTexture);
    drawPiece(blackKing, blackKingTexture);
    drawPiece(blackKnights, blackKnightTexture);
    drawPiece(blackQueens, blackQueenTexture);
    drawPiece(blackPawns, blackPawnTexture);
    drawPiece(blackRooks, blackRookTexture);

    // draw the white pieces
    drawPiece(whiteBishops, whiteBishopTexture);
    drawPiece(whiteKing, whiteKingTexture);
    drawPiece(whiteKnights, whiteKnightTexture);
    drawPiece(whiteQueens, whiteQueenTexture);
    drawPiece(whitePawns, whitePawnTexture);
    drawPiece(whiteRooks, whiteRookTexture);

    // debugPrintBitBoard(allPieces);
    // debugPrintBitBoard(allBlackPieces);
}

void Board::highlightUserPosition(int index)
{
    // debugPrintBitBoard(allPieces);

    if (selectedPieceIndex != -1 && ((allPieces >> index) & 1) == 0) {
        return;
    }

    // reset highlighted possible moves
    highlightedPossibleMoves = 0;

    // only highlight if black piece
    if (selectedPieceIndex == index) {
        // turn off highlighted piece
        selectedPieceIndex = -1;

        return;
    }

    if (((allBlackPieces >> index) & 1) == 1) {
        // selectedPieceIndex ^= ((int64_t)1 << index);
        selectedPieceIndex = index;

        if (((blackKnights >> index) & 1) == 1) {
            generatePseudoKnightMoves(index, Black);
        }

        if (((blackRooks >> index) & 1) == 1) {
            generatePseudoRookMoves(index, Black);
        }

        if (((blackBishops >> index) & 1) == 1) {
            generatePseudoBishopMoves(index, Black);
        }

        if (((blackQueens >> index) & 1) == 1) {
            generatePseudoQueenMoves(index, Black);
        }

        if (((blackPawns >> index) & 1) == 1) {
            generatePseudoPawnMoves(index, Black);
        }

        if (((blackKing >> index) & 1) == 1) {
            generatePseudoKingMoves(index, Black);
        }
    }
}

void Board::processInput(sf::Event& event)
{
    // test to check if setting / clearing the correct bit
    // get mouse position

    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    if (outOfRange(pixelPos.x, 0, 1000) || outOfRange(pixelPos.y, 0, 1000)) {
        return;
    }

    int index = getIndexFromPosition({ (int)pixelPos.x / 125, (int)pixelPos.y / 125 });

    {
        // Create a bool variable for locking the click.
        static bool lock_click;

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left && lock_click != true) {
                // std::cout << "lmb-pressed" << std::endl;
                lock_click = true;

                // highlightedPossibleMoves = addPiece(highlightedPossibleMoves, index, PieceColor::White);
                highlightUserPosition(index);
            }
        }

        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // unlock when the button has been released.
                lock_click = false;
            }
        }

        // Released Scope
    }

    // std::cout << index << '\n';

    // example usage
    // whitePawns = removePiece(whitePawns, index, PieceColor::White);
    // blackPawns = addPiece(blackPawns, index, PieceColor::Black);
}