//////////////////////////////////////////////////////////////////////////////////	 

/******************************************************************************
//              PINS CONNECTION
//              GND
//              VCC         3.3v
//              DI(SDA)     PB15
//              SC(SCL)     PB13
//              CS          PB12
//              RST         PA11
//              RS(DC)      PA12
//				BLK         PA15
*******************************************************************************/

#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        128
#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	    //灰色0  3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1  00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111

//液晶控制口置1操作语句宏定义
#define	LCD_CS_SET  	HAL_GPIO_WritePin(GPIOB,LCD_CS_Pin,GPIO_PIN_SET)
#define	LCD_LED_SET  	HAL_GPIO_WritePin(GPIOA,LCD_BLK_Pin,GPIO_PIN_SET)
#define	LCD_RS_SET  	HAL_GPIO_WritePin(GPIOA,LCD_RS_Pin,GPIO_PIN_SET)
#define	LCD_RST_SET  	HAL_GPIO_WritePin(GPIOA,LCD_RST_Pin,GPIO_PIN_SET)

//液晶控制口置0操作语句宏定义
#define	LCD_CS_RESET  	HAL_GPIO_WritePin(GPIOB,LCD_CS_Pin,GPIO_PIN_RESET)
#define	LCD_LED_RESET  	HAL_GPIO_WritePin(GPIOA,LCD_BLK_Pin,GPIO_PIN_RESET)
#define	LCD_RS_RESET  	HAL_GPIO_WritePin(GPIOA,LCD_RS_Pin,GPIO_PIN_RESET)
#define	LCD_RST_RESET  	HAL_GPIO_WritePin(GPIOA,LCD_RST_Pin,GPIO_PIN_RESET)

void Lcd_WriteIndex(uint8_t Index);
void Lcd_WriteData(uint8_t Data);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(uint16_t Color);
void Lcd_SetXY(uint16_t x,uint16_t y);
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data);
void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end);
void LCD_WriteData_16Bit(uint16_t Data);

