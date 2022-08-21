#ifndef ADS1292R_MAINAPP_H
#define ADS1292R_MAINAPP_H

#endif //ADS1292R_MAINAPP_H

#include "lmt70.h"
#include "stdio.h"
#include "gui.h"
#include "ads1292.h"
#include "usart.h"
#include "mpu6050.h"
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h"
#include "delay.h"

void updateTemp();
void updateHeartRate();
void updateSteps();
void drawBackground();
void getDataFromADS1292R();
void mainApp();

