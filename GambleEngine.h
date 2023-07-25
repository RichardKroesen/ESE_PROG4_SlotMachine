#ifndef GAMBLEENGINE_H
#define GAMBLEENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Constants to prevent magic numbers:
#define REELS_AMOUNT            3
#define REEL_ONE_INDEXES        4
#define REEL_TWO_INDEXES        5
#define REEL_THREE_INDEXES      3
#define PAYOUT_TYPES_AMOUNT     8

// Reels index configuration constants:
const int reelOne[REEL_ONE_INDEXES] = {1, 2, 3, 4};
const int reelTwo[REEL_TWO_INDEXES] = {2, 2, 1, 3, 4};
const int reelThree[REEL_THREE_INDEXES] = {4, 3, 1};

// Struct for gamble payout combination:
typedef struct PayoutCombination {
    const char letterId;
    const int arrayCombination[REELS_AMOUNT];
    const int payOutFactor;
} PayoutCombination_t;

/// Function Prototypes

// Generate Random number
int generateIndexNumber(int limit);

// Get the payout factor dependent on the reels combination
int determinePayout(int combo[], int length);

// Returns a array of the reels gamble combination
int* gambleCombination();

// calculates the gamble credit result
int gambleResult(int betAmount);

void payOutTable();

#endif // GAMBLEENGINE_H
