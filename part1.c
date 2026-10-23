#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "physics.h"
#include "part1.h"
#include "structures.h"

//core battle for Part 1-A and Part 1-C.
int runPart1A(Battleship *b, EscortShip escorts[], int numEscorts, FILE *logFile, bool escortsDealPartialDamage, int *destroyerOut){
    int escortsRemaining = numEscorts;
    //store the id of the ship that destroyed the target
    int destroyerId = -1;
    double shotTime = 0.0;

    if (destroyerOut) *destroyerOut = -1;

    //battleship fires at every escort it can hit, a single hit destroys an E ship
    for(int i = 0; i < numEscorts; i++){
        if (escorts[i].destroyed) continue;

        double tof;
        bool bCanHitE = canHitTarget(b->pos, escorts[i].pos, b->vMin, b->vMax, b->angleMin, b->angleMax, &tof);
        if (!bCanHitE) continue;