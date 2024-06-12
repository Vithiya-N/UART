
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000

void rec_init();
void lcd_init();
void Lcd_Command(unsigned char val);
void Lcd_Data(unsigned char val);
void delay(unsigned char d);

unsigned char rec_val;
unsigned char a[15]= "Received:";
unsigned char b[15]= "Transmitted:";
unsigned char i;

void main()
{
    rec_init();
    lcd_init();
    while(1)
    {
        if(PIR1&0x20)
        rec_val=RCREG;
        switch(rec_val)
        {
            case 'A':
                TXREG='a';
                Lcd_Command(0x8D);
                Lcd_Data(rec_val);
                Lcd_Command(0xCD);
                Lcd_Data(TXREG);
                break;
            case 'B':
                TXREG='b';
                Lcd_Command(0x8D);
                Lcd_Data(rec_val);
                Lcd_Command(0xCD);
                Lcd_Data(TXREG);
                break;
            case 'C':
                TXREG='c';
                Lcd_Command(0x8D);
                Lcd_Data(rec_val);
                Lcd_Command(0xCD);
                Lcd_Data(TXREG); 
                break;
             case 'D':
                TXREG='d'; 
                Lcd_Command(0x8D);
                Lcd_Data(rec_val);
                Lcd_Command(0xCD);
                Lcd_Data(TXREG);
                break;
                
        }
        delay(100);
    }
}

void rec_init()
{
    TRISC=0xC0;//1100 0000 RC7 RX AND RC6 TX
    TXSTA=0x20;  //0010 0000---> Transmit Enable bit
    RCSTA=0x90; //1001 0000----> SPEN & CREN
    SPBRG=0x09;//9=0000 1001
}

void lcd_init()
{
    TRISB=0x00;
    TRISD=0x00;
    Lcd_Command(0x30);
    delay(100);
     Lcd_Command(0x30);
    delay(100);
     Lcd_Command(0x30);
    delay(100);
     Lcd_Command(0x38);
    delay(100);
     Lcd_Command(0x0C);
    delay(100);
     Lcd_Command(0x01);
    delay(100);
    Lcd_Command(0x06);
    delay(100);
    Lcd_Command(0x80);
    for(i=0;i<10;i++)
    {
        Lcd_Data(a[i]);
    }
    delay(100);
    Lcd_Command(0xC0);
    for(i=0;i<12;i++)
    {
        Lcd_Data(b[i]);
    }
    delay(100);
}
void Lcd_Command(unsigned char val)
{
    PORTB&=0xF7;  //RS =0
    PORTD=val; // data set to portd
    PORTB|=0x01; //EN=1
    PORTB&=~0x01;  //EN=0
    delay(100);
}
void Lcd_Data(unsigned char val)
{
    PORTB|=0x08;//RS=1
    PORTD=val;
    PORTB|=0x01;
    PORTB&=~0x01;
    delay(100);
}


void delay(unsigned char d)
{
    while(--d);
}
