/*
 * File:   main.c
 * Author: Marco, Pâmela
 *
 * Created on 27 de Junho de 2018, 07:11
 */

#include <xc.h>
#include <p18f4550.h>
#include <stdio.h>
#include <stdlib.h>
#include <xlcd.h>
#include "Configuration_Header_File.h"          /* Header File for Configuration bits */
#include "LCD_16x2_8-bit_Header_File.h"                 /* Header File for LCD Functions */
#include "PIC18F4550_ADC_Header_File.h"
#pragma config WDT = OFF

#define _XTAL_FREQ = 48000000;

#define BotaoSomar TRISCbits.TRISC0 //botão para incrementar a temperatura
#define BtnSomar LATCbits.LATC0

#define BotaoSub TRISCbits.TRISC1 //botão para decrementando a temperatura
#define BtnSub LATCbits.LATC1

#define LEDAMARELO TRISDbits.TRISD0 //led amarelo, temperatura entre 10 e 20
#define LedY LATDbits.LATD0

#define LEDVERMELHO TRISDbits.TRISD0 //led vermelho, temperatura acima 20
#define LedR LATDbits.LATD0

#define LEDVERDE TRISDbits.TRISD0 //led verde, temperatura entre 0 a 10
#define LedG LATDbits.LATD0

char flag_tela = 4, tela[16];
float celsius;

void ADC_Init()
{    
    TRISA = 0xff;       /*set as input port*/
    ADCON1 = 0x00;      /*ref vtg is VDD and Configure pin as analog pin*/    
    ADCON2 = 0x92;      /*Right Justified, 4Tad and Fosc/32. */
    ADRESH=0;           /*Flush ADC output Register*/
    ADRESL=0;   
}

int ADC_Read(int channel)
{
    int digital;
    ADCON0 =(ADCON0 & 0b11000011)|((channel<<2) & 0b00111100);      /*channel is selected i.e (CHS3:CHS0) 
                                                                      and ADC is disabled i.e ADON=0*/
    ADCON0 |= ((1<<ADON)|(1<<GO));                   /*Enable ADC and start conversion*/
    while(ADCON0bits.GO_nDONE==1);                  /*wait for End of conversion i.e. Go/done'=0 conversion completed*/        
    digital = (ADRESH*256) | (ADRESL);              /*Combine 8-bit LSB and 2-bit MSB*/
    return(digital);
}

void LCD_Init()
{
   	LCD_Dir1 = 0x00;          /*Set PORTB as output PORT for LCD data(D0-D7) pins*/
    LCD_Dir2 = 0x00;          /*Set PORTD as output PORT LCD Control(RS,EN) Pins*/
    MSdelay(20);
	LCD_Command(0x38);     /*uses 2 line and initialize 5*7 matrix of LCD*/
    LCD_Command(0x01);     /*clear display screen*/
    LCD_Command(0x0c);     /*display on cursor off*/
    LCD_Command(0x06);     /*increment cursor (shift cursor to right)*/
    //inicializar os leds como desligado
	LedY = 0;
    LedR = 0;
    LedG = 0;
}

void LCD_Clear(){
    	LCD_Command(0x01);     /*clear display screen*/
}

void LCD_Command(char cmd ){
	ldata= cmd;            /*Send data to PORT as a command for LCD*/   
	RS = 0;                /*Command Register is selected*/
	EN = 1;                /*High-to-Low pulse on Enable pin to latch data*/ 
	NOP();
	EN = 0;
    MSdelay(3);
}

void LCD_Char(char dat){
	ldata= dat;            /*Send data to LCD*/  
	RS = 1;                /*Data Register is selected*/
	EN=1;                  /*High-to-Low pulse on Enable pin to latch data*/   
	NOP();
	EN=0;
    MSdelay(1);
}


void LCD_String(const char *msg)
{
	while((*msg)!=0)
	{		
	  LCD_Char(*msg);
	  msg++;	
    }
		
}

void LCD_String_xy(char row,char pos,const char *msg){
    char location=0;
    if(row<1)
    {
        location=(0x80) | ((pos) & 0x0f);      /*Print message on 1st row and desired location*/
        LCD_Command(location);
    }
    else
    {
        location=(0xC0) | ((pos) & 0x0f);      /*Print message on 2nd row and desired location*/
        LCD_Command(location);    
    }  
    

    LCD_String(msg);

}

void AtualizaTela(){ //função para atualizar a temperatura na tela
    switch(flag_tela){
        case 0:
            SetDDRamAddr(0x00);
            sprintf(tela,"       Temp OK       ");
            putrsXLCD(tela);
            SetDDRamAddr(0x40);
            //sprintf(tela,"DATA: %d:%d:%d  ", dia, mes, ano);
            //putrsXLCD(tela);
            break;
        case 1:
            sprintf(tela,"    Verificar Temp    ");
            putrsXLCD(tela);
            SetDDRamAddr(0x40);
            break;
        case 2:
            sprintf(tela,"      Temp Fora      ");
            putrsXLCD(tela);
            SetDDRamAddr(0x40);
            break;
        default:
            
            break;
    }
}

void MSdelay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<=val;i++)
            for(j=0;j<81;j++);      /*This count Provide delay of 1 ms for 8MHz Frequency */
 }

void DelayFor18TCY(void){
    Delay10TCYx(120);
}
 
void DelayPORXLCD(void){
    Delay1KTCYx(180);
    return;
}
 
void DelayXLCD(void){
    Delay1KTCYx(60);
    return;
}

void main()
{    
    char Temperature[10];    
     
    OSCCON=0x72;                /* set internal Oscillator frequency to 8 MHz*/
    LCD_Init();                 /* initialize 16x2 LCD*/
    ADC_Init();                 /* initialize 10-bit ADC*/
    
    while(1)
    {  
        AtualizaTela();
        LCD_String_xy(0,0,"Temperature");     
        celsius = (ADC_Read(0)*4.88);
        celsius = (celsius/10.00);
        sprintf(Temperature,"%d C ",(int)celsius);               /* it is used to convert integer value to ASCII string */
        LCD_String_xy(1,0,Temperature);                /* send string data for printing */    
        MSdelay(10);
        memset(Temperature,0,10);
    }
    
}
