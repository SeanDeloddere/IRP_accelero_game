/**
 * @file dwenguinoPrints.h
 * @brief This file contains function declarations which allow you to print pre-coded messages to the LCD
 */
#ifndef DWENGUINO_PRINTS_H_
#define DWENGUINO_PRINTS_H_

#include "dwenguinoLCD.h"

/**
 * @brief Prints Start Message
 * This function will Print the start message "Press Button" to the LCD screen
 */
void StartMessage();

/**
 * @brief Prints Game Over
 * This function will Print the Game Over message, depending on the way you died, and the score
 * @param score the current score
 * @param tijd The time
 */
void GameOver(unsigned int score, int tijd);

/**
 * @brief Prints current starttime
 * This function will Print the current time the game will take in seconds
 * @param starttime the time in seconds the game should take
 */
void TimeMessage(unsigned int starttime);

/**
 * @brief Clears LCD in an interval
 * This function will clear the characters from the LCD on a specific line, at a given interval
 * @param line line on LCD
 * @param start first character to clears
 * @param amount of characters to clear including start
 */
void ClearPartLCD(BYTE line, BYTE start, BYTE length);

#endif /* DWENGUINO_PRINTS_H_ */
