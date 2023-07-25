#include "GambleEngine.h"

// Payout combinations constants:
PayoutCombination payOutsConstants[PAYOUT_TYPES_AMOUNT] = {
    {'A', {1,1,4}, 1},
    {'B', {1,1,3}, 1},
    {'C', {1,1,1}, 3},
    {'D', {2,2,4}, 2},
    {'E', {2,2,2}, 2},
    {'F', {2,2,1}, 2},
    {'J', {3,3,3}, 12},
    {'K', {4,4,4}, 30}
};

int gambleResult(int betAmount) {
    int* reelsCombination = gambleCombination();
    int factor = determinePayout(reelsCombination, sizeof(reelsCombination));
    betAmount *= factor;
    return betAmount;
}

int* gambleCombination() {
    static int reelsArray[REELS_AMOUNT]; // static so the function can return the int array

    // Random index numbers generated within the range of the reels
    int randomnumber = generateIndexNumber(REEL_ONE_INDEXES);
    int randomnumber2 = generateIndexNumber(REEL_TWO_INDEXES);
    int randomnumber3 = generateIndexNumber(REEL_THREE_INDEXES);

    // Index of the gamble combination assignment from random reels indexes
    reelsArray[0] = reelOne[randomnumber];
    reelsArray[1] = reelTwo[randomnumber2];
    reelsArray[2] = reelThree[randomnumber3];

    return reelsArray;
}

int generateIndexNumber(int limit) {
    int randomIndex = 0;
    srand(time(NULL));
    randomIndex = (rand() % limit);
    return randomIndex;
}

int determinePayout(int combo[], int length) {
    int payoutFactor = 0;

    for(int i = 0; i < PAYOUT_TYPES_AMOUNT; i++) {
        if(memcmp(combo, payOutsConstants[i].arrayCombination, length+1) == 0) {
            payoutFactor = payOutsConstants[i].payOutFactor;
        }
    }

    return payoutFactor;
}

//void payOutTable() {
//    for(int i = 0; i < AMOUNT_PAYOUT; i++) {
//        printf("\n ID: %c\t", payOutsConstants[i].letterId);
//        printf("Array: ");

//        for(int j = 0; j < COMBI_LENGTH; j++) {
//            printf("%d", payOutsConstants[i].arrayCombination[j]);
//        }

//        printf("\t");
//        printf("Payout Factor: %d", payOutsConstants[i].payOutFactor);
//    }
//    printf("\n");
//}
