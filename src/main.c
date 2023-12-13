#include <stdio.h>
#include <stdlib.h>

#include "uninominale.h"
#include "condorcet.h"
#include "condorcet_minimax.h"

int main() {
    methodeUninominales();
    methodeCondorcet();
    methodeCondorcetMinimax();
    return 0;
}
