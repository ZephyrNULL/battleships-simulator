#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "part1_ui.h"
#include "part2_ui.h"
#include "structures.h"

#define MAX_ESCORTS 50

//randomly generate the escort ship settings
static void generateEscortProperties(EscortShip *e, int typeIdx, double gridSize, double bVMax);

//draw the canvas for game
int board_draw_input(void){
    int grid_value;
    printf("Enter the grid value: ");

    if (scanf("%d", &grid_value) != 1) return 1000;
    return grid_value;
}

//drawing the board
void draw_board(int Grid_Value){
    for(int i = 0; i < Grid_Value; i++) {
        for(int j = 0; j < Grid_Value; j++) {
            printf("|");
        }
        printf(" ");
    }
    printf("\n");
}

//reads a number and keeps asking until it is inside the allowed range
double readInRange(const char *prompt, double min, double max){
    double value;
    int c;

    do{
        printf("%s (%.2f - %.2f): ", prompt, min, max);

        if(scanf("%lf", &value) != 1){
            do{ 
                c = getchar(); 
            } while (c != '\n' && c != EOF); //clear the invalid input
            printf("Invalid input. Please enter a number.\n");


            value = min - 1.0;
        }else if(value < min || value > max) {
            printf("Out of range. Allowed range is %.2f to %.2f.\n", min, max);
        }
     }while(value < min || value > max); 

    return value;
}

void initial_settingsForBS(Battleship *b, double gridSize){


    printf("\n--- BATTLESHIP SETUP ---\n");
    printf("Available battleship types:\n");
    printf("  Notation | Name                | Gun\n");
    printf("  -------- | --------------------|------------------------\n");
    printf("       U  | USS Iowa BB-61      | 50-caliber Mark 7 gun\n");
    printf("      M  | MS King George V    | (356 mm) Mark VII gun\n");
    printf("       R  | Richelieu           | (15 inch) Mle 1935 gun\n");
    printf("        S  | Sovetsky Soyuz-class| (16 inch) B-37 gun\n");
    printf("Enter Battleship Name: ");
    scanf(" %[^\n]", b->typeName);
    printf("Enter Battleship Notation (e.g., U): ");
    scanf("%4s", b->typeNotation);


    //getting the battleship starting position
    b->pos.x = readInRange("Enter Battleship starting position X", 0.0, gridSize);
    b->pos.y = readInRange("Enter Battleship starting position Y", 0.0, gridSize);


    //geting the battleship min velocity
    b->vMin = readInRange("Enter Min Velocity", 0.0, 5000.0);
    do {
        b->vMax = readInRange("Enter Max Velocity", 0.0, 5000.0);
        if (b->vMax <= b->vMin) {
            printf("Out of range. Max Velocity must be greater than Min Velocity (%.2f).\n", b->vMin);
        }
    } while (b->vMax <= b->vMin);

    b->angleMin = readInRange("Enter Min Angle (degrees)", 0.0, 90.0);
    do{

        b->angleMax = readInRange("Enter Max Angle (degrees)", 0.0, 90.0);
        if (b->angleMax <= b->angleMin){

            printf("Out of range. Max Angle must be greater than Min Angle (%.2f).\n", b->angleMin);
        }
    } while (b->angleMax <= b->angleMin);

    b->impactPower = readInRange("Enter Base Impact Power (e.g., 0.5)", 0.0, 1.0);
    b->gamma = readInRange("Enter Gamma (degradation factor)", 0.0, 1.0);
    b->reloadTime = readInRange("Enter Reload Time (seconds between shots)", 0.1, 60.0);

    b->shotsFired = 0;
    b->health = 1.0;
    b->destroyed = false;
}



//function to initializing escortships

void initial_settingsForES(EscortShip escorts[], int *numEscorts, double gridSize, double bVMax){
    printf("\n--- ESCORT SHIPS SETUP ---\n");

    printf("Enter the number of Escort Ships (1-%d): ", MAX_ESCORTS);
    scanf("%d", numEscorts);

    //validate the number of escort ships
    while (*numEscorts < 1 || *numEscorts > MAX_ESCORTS) {
        //print this erro if not in the range
        printf("Invalid number. Please enter a value between 1 and %d: ", MAX_ESCORTS);

        scanf("%d", numEscorts);
    }

    for (int i = 0; i < *numEscorts; i++) {
        escorts[i].id = i + 1;
        int typeIdx = rand() % 5;
        generateEscortProperties(&escorts[i], typeIdx, gridSize, bVMax);
    }

    printf("Generated %d escort ships successfully.\n", *numEscorts);



}