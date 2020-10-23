/**
 * @file dwenguinoACC.h
 * @brief This file contains function declarations which allow you to communicate with the accelerometer
 */
 #ifndef DWENGUINO_ACC_H_
 #define DWENGUINO_ACC_H_

 #include "dwenguinoBoard.h"

 /**
  * @brief Initializes Accelerometer
  * This function will initalize the Accelerometer by putting it out of sleep mode
  */
void initAccelerometer();

/**
 * @brief read data from register
 * This function will read and return the data from a specific register on the accelerometer
 * @param registerwaarde register value
 */
int read(int registerwaarde);

/**
 * @brief read Big X
 * This function will read and return the data from the Big X data register
 */
int readX();

/**
 * @brief read Small x
 * This function will read and return the data from the small x data register
 */
int readx();

/**
 * @brief read Big Y
 * This function will read and return the data from the Big Y data register
 */
int readY();

/**
 * @brief read Small y
 * This function will read and return the data from the Small y data register
 */
int ready();

/**
 * @brief read Big Z
 * This function will read and return the data from the Big Z data register
 */
int readZ();

/**
 * @brief read Small z
 * This function will read and return the data from the Small z data register
 */
int readz();

/**
 * @brief returns the Roll
 * This function will read the neccesary data, calculate and return the Roll
 */
int leesRoll();

/**
 * @brief returns the Pitch
 * This function will read the neccesary data, calculate and return the Pitch
 */
int leesPitch();

#endif /* DWENGUINO_ACC_H_ */
