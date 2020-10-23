/**
 * @file dwenguinoPrints.h
 * @brief This file contains function declarations which allow you to print pre-coded messages to the LCD
 */
#ifndef DWENGUINO_DRAW_H_
#define DWENGUINO_DRAW_H_

#include "dwenguinoDraw.h"

//length of platform arrays
#define B_LENGTH 200
//ball states
#define BALL_LEFT 0
#define BALL_LEFT_AIR 1
#define BALL_RIGHT_AIR 2
#define BALL_RIGHT 3

#define BYTE unsigned char
/**
 * @brief Draws the board on LCD
 * This function will print the characters of the board on the LCD
 * It handles all the logic to print the correct characters
 * @param bord the filled board of size 2x32
 */
void DrawBoard(BYTE** bord);

/**
 * @brief Draws the ball in the board
 * This function will print the characters of the ball on the bottom of the LCD screen
 * It handles the logic to print the correct character when ball is left, right or flying
 * @param ball current state ball
 * @param delayt current tick
 * @param bord the filled board of size 2x32
 * @param direction the direction the ball is heading
 */
void DrawBal(BYTE ball, int delayt, BYTE** bord, BYTE direction);

/**
 * @brief Adds Empty Part to platform arrays
 * This function will add 0,1 pr 2 empty spots to the platform array and return the index after these are added.
 * @param r3 random number {0,1,2}
 * @param i start index to fill in empty parts
 * @param balkl left platform array
 * @param balkr right platform array
 */
int EmptyPart(BYTE r3, int i,BYTE* balkl, BYTE* balkr);

/**
 * @brief Fills platform arrays with given interval
 * This function will fill the given platform arrays with 1's, only left, only right or both sides, for a given length
 * i start index interval to fill in
 * side 0 for left, 1 for right, 2 for both sides
 * size size of interval to fill in
 * @param balkl the left side array of platforms
 * @param balkr the right side array of platforms
 */
void fillBalken(unsigned int i, BYTE side, unsigned int size, BYTE* balkl,BYTE* balkr);

/**
 * @brief initializes the platforms that will be used
 * This function will initialize both arrays of platforms with a random level
 * @param balkl the left side array of platforms
 * @param balkr the right side array of platforms
 */
void initBalken(BYTE* balkl, BYTE* balkr);

/**
 * @brief initializes the custom LCD characters
 * This function will initialize six custom LCD characters, two sides with each three different platforms:
 * full, only top, only bottom
 */
void initCustomCharacters();

#endif /* DWENGUINO_DRAW_H_ */
