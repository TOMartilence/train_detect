#include <htc.h>

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 20000000
#define I2C_BaudRate 100000

#define LCD_BACKLIGHT 0x08
#define LCD_COMMAND 0
#define LCD_DATA 1

unsigned char I2C_address = 0x4E;
unsigned char BackLight_State = LCD_BACKLIGHT;

// Function Prototypes
void I2C_Master_Init(void);
void I2C_Master_Start(void);
void I2C_Master_Stop(void);
void I2C_Master_Wait(void);
void I2C_Master_Write(unsigned char data);
void IO_Expander_Write(unsigned char data);
void LCD_Write_4Bit(unsigned char nibble);
void LCD_CMD(unsigned char cmd);
void LCD_Char(char data);
void LCD_Init(void);
void LCD_String(char *str);
void LCD_Set_Cursor(unsigned char row, unsigned char col);

void main() {
    I2C_Master_Init();
    LCD_Init();
    
    TRISD = 0x80;  // Set RD7 as input (bit 7 = 1), others as output
    __delay_ms(100);  // Allow LCD and I2C to stabilize

    while (1) {  // Continuous loop
        LCD_Set_Cursor(1, 1);
        LCD_String("                ");  // Clear previous text
        LCD_Set_Cursor(1, 1);

        if (RD7 == 1) {
            LCD_String("TRAIN IS HERE !");
        } else {
            LCD_String("SAFE TO PASS");
        }

        __delay_ms(500);  // Small delay before rechecking
    }
}

// I2C + LCD Functions
void I2C_Master_Init(void) {
    SSPCON = 0x28;
    SSPCON2 = 0x00;
    SSPADD = (_XTAL_FREQ / (4 * I2C_BaudRate)) - 1;
    SSPSTAT = 0x00;
    TRISC3 = 1;
    TRISC4 = 1;
}

void I2C_Master_Wait(void) {
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_Start(void) {
    I2C_Master_Wait();
    SEN = 1;
}

void I2C_Master_Stop(void) {
    I2C_Master_Wait();
    PEN = 1;
}

void I2C_Master_Write(unsigned char data) {
    I2C_Master_Wait();
    SSPBUF = data;
    while (!SSPIF);
    SSPIF = 0;
}

void IO_Expander_Write(unsigned char data) {
    I2C_Master_Start();
    I2C_Master_Write(I2C_address);
    I2C_Master_Write(data | BackLight_State);
    I2C_Master_Stop();
}

void LCD_Write_4Bit(unsigned char nibble) {
    IO_Expander_Write(nibble | 0x04);  // EN = 1
    __delay_us(1);
    IO_Expander_Write(nibble & ~0x04); // EN = 0
    __delay_us(50);
}

void LCD_CMD(unsigned char cmd) {
    unsigned char high = cmd & 0xF0;
    unsigned char low = (cmd << 4) & 0xF0;
    LCD_Write_4Bit(high | 0x00); // RS = 0
    LCD_Write_4Bit(low | 0x00);
}

void LCD_Char(char data) {
    unsigned char high = data & 0xF0;
    unsigned char low = (data << 4) & 0xF0;
    LCD_Write_4Bit(high | 0x01); // RS = 1
    LCD_Write_4Bit(low | 0x01);
}

void LCD_Init(void) {
    __delay_ms(50);
    LCD_CMD(0x03);
    __delay_ms(10);
    LCD_CMD(0x03);
    __delay_ms(10);
    LCD_CMD(0x03);
    __delay_ms(10);
    LCD_CMD(0x02);
    __delay_ms(10);
    LCD_CMD(0x28);
    LCD_CMD(0x0C);
    LCD_CMD(0x06);
    LCD_CMD(0x01);
    __delay_ms(10);
}

void LCD_String(char *str) {
    while (*str) {
        LCD_Char(*str++);
    }
}

void LCD_Set_Cursor(unsigned char row, unsigned char col) {
    unsigned char pos[] = {0x80, 0xC0, 0x94, 0xD4};
    LCD_CMD(pos[row - 1] + col - 1);
}
