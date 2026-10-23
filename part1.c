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
        b->shotsFired++;
        shotTime += tof; //time of flight is the time to hit this escort
        escorts[i].destroyed = true;
        escortsRemaining--;

        if (logFile){
            fprintf(logFile, "[t=%.2fs] Battleship hit Escort E%d with a single shot "
                             "(Index=%d, Time-to-hit=%.2fs).\n", shotTime, escorts[i].id, escorts[i].id, tof);

        }
    }

    //surviving escorts attack the battleship
    if (escortsRemaining > 0 && !b->destroyed) {
        for(int i = 0; i < numEscorts; i++) {
            if (escorts[i].destroyed) continue;

            double tof;
            bool eCanHitB = canHitTarget(escorts[i].pos, b->pos, escorts[i].vMin, escorts[i].vMax, escorts[i].angleMin, escorts[i].angleMax, &tof);
            
            if (!eCanHitB) continue;

            escorts[i].shotsFired++;
            shotTime += tof;

            if (escortsDealPartialDamage) {

                b->health -= escorts[i].impactPower;
                if (logFile) {
                    fprintf(logFile, "[t=%.2fs] Escort E%d hit the Battleship "
                                     "(Impact=%.3f, B-Health=%.2f%%).\n",
                            shotTime, escorts[i].id, escorts[i].impactPower,
                            b->health > 0 ? b->health * 100.0 : 0.0);
                }
                if (b->health <= 0.0) {
                    b->health = 0.0;
                    b->destroyed = true;
                    destroyerId = escorts[i].id;
                    if (logFile) {

                        fprintf(logFile, "[t=%.2fs] BATTLESHIP DESTROYED by cumulative impact.\n", shotTime);
                    }
                    break;
                }
            } else {
                //a single hit destroys B
                b->health = 0.0;
                b->destroyed = true;
                destroyerId = escorts[i].id;
                if (logFile) {
                    fprintf(logFile, "[t=%.2fs] Escort E%d hit the Battleship (single shot). "
                                     "B is DESTROYED.\n", shotTime, escorts[i].id);
                }
                break;
            }
        }
    }

    if (logFile) {
        fprintf(logFile, "--- PART 1 RESULT ---\n");
        if(b->destroyed) {
            fprintf(logFile, "Battleship sank. Sunk by Escort E%d. Duration=%.2fs.\n",
                    destroyerId, shotTime);
        } else{
            fprintf(logFile, "Battleship survived. Escorts destroyed: %d/%d. Duration=%.2fs.\n", numEscorts - escortsRemaining, numEscorts, shotTime);
            if (escortsDealPartialDamage) {
                fprintf(logFile, "Cumulative impact on B: %.2f%%.\n", (1.0 - b->health) * 100.0);
            }
        }
    }

    if (destroyerOut) *destroyerOut = destroyerId;

    return b->destroyed ? 1 : 0;
}