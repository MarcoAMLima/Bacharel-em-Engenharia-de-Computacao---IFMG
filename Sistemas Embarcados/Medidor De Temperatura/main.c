#include <xc.h>
#include <stdio.h>
#include <p18f4550.h>
#include <xlcd.h>
#pragma config WDT = OFF
#pragma config PBADEN = OFF
#define _XTAL_FREQ 2000000

char valor[16];
char teste = 0;
float temp;

void DelayFor18TCY(){
    Delay10TCYx(120);
}

void DelayPORXLCD(){
    Delay1KTCYx(180);
}

void init_XLCD(void){//Inicializar o LCD
  OpenXLCD(FOUR_BIT&LINES_5X7);
  while(BusyXLCD());
  WriteCmdXLCD(0X06);
  WriteCmdXLCD(0x0C);
}

void config_inicial(){//configuração inicial da tela
    T0CONbits.TMR0ON =0;// desabilita o timer 0
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    T0CONbits.T08BIT= 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS0 = 0;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS2 =1;
    T0CONbits.T0CS =0;
    TMR0 = 0;
    T0CONbits.TMR0ON =1;
    INTCONbits.GIEH =1;
    INTCONbits.GIEL =1;
}

void interrupt Interrupcao(){
    if(PIR1bits.ADIF){
        teste = 1;
        PIR1bits.ADIF = 0;
    }
}

void WriteLCD(){
    char nome[16];
    SetDDRamAddr(0x00);
    putrsXLCD("Temp:"); //exibe no lcd
}

void WriteTemp(){
    temp = ((float)ADRES * 5 * 100) / 1024; 
    sprintf(valor, "%.2fC", temp);
    SetDDRamAddr(0x40);
    putrsXLCD(valor);
}

void ConfigAD(){
    ADCON0 = 0b00000000;    //controla as operações do módulo AD
    ADCON1 = 0b00001110;    //configura as funções dos pinos da porta
    ADCON2 = 0b10011110;    //Configura a fonte do clock do AD
    
    ADCON0bits.ADON = 1; //Ligou o módulo AD converter
    
    __delay_us(5);
    
    ADCON0bits.GODONE = 1;
}

void main(){
    init_XLCD(); //inicializa o LCD
    config_inicial();
    WriteLCD();
    T0CONbits.TMR0ON = 0; // Desabilita o timer 0
    INTCONbits.TMR0IE = 1; // Habilita interrupção TMR0
    INTCONbits.TMR0IF = 0; // Limpa flag de interrupção
    T0CONbits.T08BIT = 0; // Temporizador/ contador de 16 bits
    T0CONbits.PSA = 0; //
    T0CONbits.T0PS0 = 1; // Configura Prescaler como 1:16
    T0CONbits.T0PS1 = 0;
    T0CONbits.T0PS2 = 1;
    T0CONbits.T0CS = 0; // Utilizar clock interno
    TMR0 = 0; // Zera o contador de interrupção
    T0CONbits.TMR0ON = 1; // Habilitar timer 0;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    PIE1bits.ADIE   = 1; //Interrupção do módulo ADC ativada
    SetDDRamAddr(0x00);
    
    while(1){
        ConfigAD();
        if(teste == 1){
            WriteTemp();
            teste = 0;
            SetDDRamAddr(0x10);
            putrsXLCD("Medidor de temperatura");
        }
    }
    return;
}
