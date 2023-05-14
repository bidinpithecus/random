#include "helpers.hpp"

int randomInt(int min, int max) {
    unsigned int randomValue;
    FILE* fptr;
    fptr = fopen("/dev/random", "r");
    fread(&randomValue, sizeof(randomValue), 1, fptr);
    fclose(fptr);

    randomValue %= (max - min) + 1;
    randomValue += min;

    return randomValue;
}
