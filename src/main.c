#include <stdio.h>
#include <stdlib.h>

#include "uninominale.h"
#include "condorcet_minimax.h"
#include "jugement_majoritaire.h"

int main() {
    methodeUninominales();
    methodeCondorcetMinimax();
    jugementMajoritaire();
    return 0;
}
