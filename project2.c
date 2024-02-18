/* ENGGEN131 C Project 2023 - Battleships */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 6
#define HIT 1000

// Prototype declarations of required functions
void PrintArray(int values[MAP_SIZE][MAP_SIZE]);
void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]);
void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]);
int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]);
int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE]);
int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]);
void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]);
void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col);
int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]);


/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go below
*******************************************************************************
*******************************************************************************
******************************************************************************/

void PrintArray(int values[MAP_SIZE][MAP_SIZE]) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            printf("%d ", values[i][j]);
        }
        printf("\n");
    }
   
}

void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]) {
    
    for (int col = 0; col < 2; col++) {
        map[0][col] = 2;
    }
    
    for (int col = 1; col < 4; col++ ) {
        map[2][col] = 3;
    }
    
    for (int col = 0; col < 4; col++) {
        map[MAP_SIZE-1][col] = 4;
    }
    
    for (int row = 0; row < 5; row++) {
        map[row][MAP_SIZE-1] = 5;
    }
}

void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]) {
    int bool = 0;
    int start_row, start_col, end_row, end_col, direction = 0;
   
    while (bool == 0) {
       
        direction = rand() % 4;
        start_row = rand() % (MAP_SIZE);
        start_col = rand() % (MAP_SIZE);
       
       
        if (direction == 0) {
            end_row = start_row - size;
            end_col = start_col;
           
            if (end_row < 0) {
                bool = 0;
            } else {
               
                for (int row = start_row; row > end_row; row--) {
                    map[row][start_col] = size;
                }
                bool = 1;
            }
        } else if (direction == 1) {
            end_col = start_col + size;
            end_row = start_row;
           
            if (end_col > MAP_SIZE-1) {
                bool = 0;
            } else {
               
                for (int col = start_col; col < end_col; col++) {
                    map[start_row][col] = size;
                }
                bool = 1;
            }
        } else if (direction == 2) {
            end_row = start_row + size;
            end_col = start_col;
           
            if (end_row > MAP_SIZE-1) {
                bool = 0;
            } else {
               
                for (int row = start_row; row < end_row; row++) {
                    map[row][start_col] = size;
                }
                bool = 1;
            }
        } else if (direction == 3) {
            end_col = start_col - size;
            end_row = start_row;
           
            if (end_col < 0) {
                bool = 0;
            } else {
               
                for (int col = start_col; col > end_col; col--) {
                    map[start_row][col] = size;
                }
                bool = 1;
            }
        }
       
    }    
   
}

int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]) {
    int count = 0;
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j] == value) {
                count = count + 1;
            }
        }
    }
   
    return count;
}

int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE]) {
    int direction = 0;
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j] == size) {
                *row = i;
                *col = j;
                if (map[i][j+1] == size || map[i][j-1] == size) {
                    direction = 1;
                } else {
                    direction = 2;
                }
                return direction;
            }
        }
    }
}

int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]) {
    int count = 0; // Initialize the ship count
    
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j] == size) {
                count++; // Increment the ship count
                
                if (i == 0 && j == 0) {  // Top left corner
                    if ((map[i][j + 1] != size && map[i][j + 1] != 0) || (map[i + 1][j] != size && map[i + 1][j] != 0)) {
                        return 0;
                    }
                } else if (i == 0 && j == MAP_SIZE - 1) { // Top right corner
                    if ((map[i][j - 1] != size && map[i][j - 1] != 0) || (map[i + 1][j] != size && map[i + 1][j] != 0)) {
                        return 0;
                    }
                } else if (i == MAP_SIZE - 1 && j == 0) { // Bottom left corner
                    if ((map[i - 1][j] != size && map[i - 1][j] != 0) || (map[i][j + 1] != size && map[i][j + 1] != 0)) {
                        return 0;
                    }
                } else if (i == MAP_SIZE - 1 && j == MAP_SIZE - 1) { // Bottom right corner
                    if ((map[i][j - 1] != size && map[i][j - 1] != 0) || (map[i - 1][j] != size && map[i - 1][j] != 0)) {
                        return 0;
                    }
                } else if (i == 0) { // First row
                    if ((map[i][j + 1] != size && map[i][j + 1] != 0) || (map[i + 1][j] != size && map[i + 1][j] != 0) || (map[i][j - 1] != size && map[i][j - 1] != 0)) {
                        return 0;
                    }
                } else if (j == 0) { // First column
                    if ((map[i][j + 1] != size && map[i][j + 1] != 0) || (map[i + 1][j] != size && map[i + 1][j] != 0) || (map[i - 1][j] != size && map[i - 1][j] != 0)) {
                        return 0;
                    }
                } else if (i == MAP_SIZE - 1) { // Last row
                    if ((map[i][j - 1] != size && map[i][j - 1] != 0) || (map[i][j + 1] != size && map[i][j + 1] != 0) || (map[i - 1][j] != size && map[i - 1][j] != 0)) {
                        return 0;
                    }
                } else if (j == MAP_SIZE - 1) { // Last column
                    if ((map[i][j - 1] != size && map[i][j - 1] != 0) || (map[i + 1][j] != size && map[i + 1][j] != 0) || (map[i - 1][j] != size && map[i - 1][j] != 0)) {
                        return 0;
                    }
                } else { // Tiles with four adjacent tiles
                    if ((map[i][j + 1] != size && map[i][j + 1] != 0) || (map[i + 1][j] != size && map[i + 1][j] != 0) || (map[i][j - 1] != size && map[i][j - 1] != 0) || (map[i - 1][j] != size && map[i - 1][j] != 0)) {
                        return 0;
                    }
                }
            }
        }
    }
    
    if (count == size) {
        return 1; // if all conditions are satisfied
    }
}

void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]) {
    
    int bool;
    int size = 2;
    while (size < 6) {

        AddRandomShip(size, map);
        bool = IsShipValid(size, map);
            
        if (bool == 0) {
            size = 1;
            for (int row = 0; row < MAP_SIZE; row++) {
                for (int col = 0; col < MAP_SIZE; col++) {
                    map[row][col] = 0;
                }
            }
        } 
        
        size += 1;
    }
}

void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col)
{
	shots[0][0] = map[0][0] + row + col; // to prevent compiler warning (you must complete this function)
}

int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE])
{
	return shots[0][0] + map[0][0]; // to prevent compiler warning (you must complete this function)
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go above
*******************************************************************************
*******************************************************************************
******************************************************************************/

/*************************************************************************
** You should define your own test functions below
*************************************************************************/

// Example: a test function for Task One
void TestPrintArray(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = {0};
	printf("Map 1: \n");
	PrintArray(map1);

	int map2[MAP_SIZE][MAP_SIZE] = {0};
	for (int i = 0; i < MAP_SIZE; i++) {
		map2[MAP_SIZE-i-1][i] = i;
	}
	printf("\nMap 2:\n");
	PrintArray(map2);
}

// Example: a test function for Task Two
void TestInitialiseMap(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = {0};
	InitialiseMap(map1);
	printf("\nMap: \n");
	PrintArray(map1);
}

// Example: a test function for Task Three
void TestAddRandomShip(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = {0};
	int map2[MAP_SIZE][MAP_SIZE] = {0};

	AddRandomShip(5, map1);

	printf("\nMap: \n");
	PrintArray(map1);

	AddRandomShip(2, map2);
	AddRandomShip(3, map2);
	AddRandomShip(4, map2);
	AddRandomShip(5, map2);

	printf("\nMap: \n");
	PrintArray(map2);
}

void TestTopLeftPosition(void)
{
    int map[MAP_SIZE][MAP_SIZE] = { 0 };
    int row, col, direction, shipSize;
    InitialiseMap(map);
    PrintArray(map);
    for (shipSize = 2; shipSize <= 5; shipSize++) {
        direction = TopLeftPosition(shipSize, &row, &col, map);
        printf("Ship %d is at (%d, %d) facing %d\n", shipSize,
            row, col, direction);
    }
}

void TestIsShipValid(void) {
    
    int map[MAP_SIZE][MAP_SIZE] = {0};
    int valid, shipSize;
    InitialiseMap(map);
    PrintArray(map);
    for (shipSize = 2; shipSize <= 5; shipSize++) {
        valid = IsShipValid(shipSize, map);
        printf("Is ship %d valid? %d\n", shipSize, valid);
        }
    
    // Move Ship 4 to an invalid position
    map[5][0] = 0;
    map[5][1] = 0;
    map[5][2] = 0;
    map[5][3] = 0;
    map[4][3] = 4;
    map[4][4] = 4;
    map[4][5] = 4;
    map[4][5] = 4;
    PrintArray(map);
    for (shipSize = 2; shipSize <= 5; shipSize++) {
        valid = IsShipValid(shipSize, map);
        printf("Is ship %d valid? %d\n", shipSize, valid);
    }
}



void TestInitialiseRandomMap() {
    
    int map[MAP_SIZE][MAP_SIZE] = {0};
    InitialiseRandomMap(map);
    PrintArray(map);
}

int main(void)
{
	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	TestPrintArray();
	TestInitialiseMap();
	TestAddRandomShip();
	TestTopLeftPosition();
	TestIsShipValid();
	TestInitialiseRandomMap();

	return 0;
}


