#pragma once

// useful macros
#define getBit(num, i) ((num >> i) & 1)
#define setBit(num, i) ((num) |= (1ULL << i))
#define clearBit(num, i) ((num) &= ~(1ULL << i))

#define DEBUG_ON 1

#if DEBUG_ON
#include <bitset>
#include <iostream>
#endif

void debugPrintBitBoard(uint64_t bitBoard)
{
#if DEBUG_ON

    for (size_t i = 0; i < 64; i++) {
        std::cout << ((bitBoard >> i) & 1);

        if ((i + 1) % 8 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;

#endif
}

bool outOfRange(int n, int min, int max)
{
    return n < min || n > max;
}