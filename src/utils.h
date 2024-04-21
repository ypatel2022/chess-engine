#pragma once

#define DEBUG_ON 0

#if DEBUG_ON
#include <bitset>
#include <iostream>
#endif

void debugPrintBitBoard(int64_t bitBoard)
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