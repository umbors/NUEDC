#include <mainApp.h>
#include "tim.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

#define maxVolt 16679000
#define minVolt 16675000

uint8_t res;
uint8_t i=0;
uint8_t flag = 1;               //超过峰值后防止重复检测

uint8_t data_to_send[20];
uint32_t cannle[2000];

int8_t tick = 0;                //两次波形中间的采样次数
uint8_t time = 0;               //心率
uint8_t temp = 0;               //温度
uint16_t step = 0;              //步数
uint16_t distance = 0;          //距离
int32_t max;
int32_t min;
short x=0;
short y=0;
short z=0;

void updateSteps(){
    dmp_get_pedometer_step_count(&step);
    char temp1[4] = {0};
    sprintf(temp1, "%d", step);
    Gui_DrawFont_GBK(40,104,RED,BLACK,12,temp1);
}

void updateHeartRate(){
    max = 0;
    min = cannle[0];
    if(tick) {
        for(int j=0;j<=i;j++){
            if(cannle[j]>max) max = cannle[j];
            if(cannle[j]<min) min = cannle[j];
        }
        time = tick * 15;
        if(time<=300) {
            char temp1[4] = {0};
            sprintf(temp1, "%d", time);
            Gui_DrawFont_GBK(106, 116, RED, BLACK, 12, temp1);
            tick = 0;
            i = 0;
        }
    }
}

void updateTemp(){
    temp = LMT_GetTemp();
    char temp1[3] = {0};
    sprintf(temp1, "%d", temp);
    Gui_DrawFont_GBK(106,104,RED,BLACK,12,temp1);
}

void drawBackground(){
    Lcd_Clear(BLACK);
    Gui_DrawLine(0,100,127,100,RED);
    Gui_DrawFont_GBK(0,104,RED,BLACK,12,"Step:");
    Gui_DrawFont_GBK(0,116,RED,BLACK,12,"Dis:");
    Gui_DrawFont_GBK(75,104,RED,BLACK,12,"Temp:");
    Gui_DrawFont_GBK(75,116,RED,BLACK,12,"bpm:");
}

void getDataFromADS1292R(){
    if(ads1292_recive_flag) {
        cannle[i]=ads1292_Cache[6]<<16 | ads1292_Cache[7]<<8 | ads1292_Cache[8];

        if(cannle[i] > max-1000 && flag){
            tick++;
            flag = 0;
        }
        else if(cannle[i] <= min+1000){
            flag = 1;
        }
        i++;

        data_to_send[4]=ads1292_Cache[6];  	    //17-24
        data_to_send[5]=ads1292_Cache[7];	    //9-16
        data_to_send[6]=ads1292_Cache[8];		//1-8
        data_to_send[7]=temp;
        data_to_send[8]=time;
        data_to_send[9]=step;

        if(HAL_UART_GetState(&huart1) == HAL_UART_STATE_READY) {
            while (HAL_UART_Transmit(&huart1, data_to_send, 10,1000) != HAL_OK);
        }
        //HAL_DMA_Start()DMA_Enable(DMA1_Channel4,13);
        ads1292_recive_flag=0;
    }
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

void mainApp() {
    data_to_send[0] = 0xAA;
    data_to_send[1] = 0xAA;
    data_to_send[2] = 0xF1;
    data_to_send[3] = 8;
    drawBackground();
    dmp_set_pedometer_step_count(0);
    HAL_TIM_Base_Start_IT(&htim1);
    //while(mpu_dmp_init())//MPU DMP初始化
    //{
    //    printf("MPU6050 Error!!!\r\n");
    //    delay_ms(500);
    //}
    //printf("success");
    //HAL_GPIO_TogglePin(GPIOC,LED_Pin);
    while (1) {
        //dmp_get_pedometer_step_count(&step);
        getDataFromADS1292R();
        MPU_Get_Accelerometer(&x,&y,&z);
//        MPU_Get_Gyroscope(&x,&y,&z);
        delay_ms(1);
//        get_accdata();
    }
}

