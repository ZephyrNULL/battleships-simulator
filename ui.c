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