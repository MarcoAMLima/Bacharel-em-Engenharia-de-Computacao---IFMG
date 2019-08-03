/*
 * File:   mainzinha.c
 * Author: Mizate
 *
 * Created on 16 de Outubro de 2018, 18:32
 */


#include <xc.h>
#include <p18f4550.h>
#include <stdio.h>
#include <stdlib.h>
#include <xlcd.h>
#pragma config WDT = OFF
#pragma config PBADEN = OFF
#define _XTAL_FREQ 20000000

//Leds
#define LedTRed TRISCbits.TRISC0 //LED VERMELHO
#define LedRed LATCbits.LATC0
#define LedTYellow TRISCbits.TRISC1 //LED AMARELO
#define LedYellow LATCbits.LATC1
#define LedTGreen TRISCbits.TRISC2 //LED VERDE
#define LedGreen LATCbits.LATC2

/*
Estado do LED
 *  1 vermelho
 *  2 amarelo 
 *  3 verde

 Tela atual
 * 0 Tela inicial
 * 1 Em teste
 * 2 Resultado do teste
 */
int cont, estado, flag_tela = 0;
char tela[16],acertos, erros;

void init(){//inicializar leds
   LedTRed = 0;
   LedRed = 0;
   LedTYellow = 0;
   LedYellow = 0;
   LedTGreen = 0;
   LedGreen = 0;
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

void AlternaModo(){//Alterar a cor de pisque do led
    switch(estado){
        case 1://vermelho -> verde
            cont = 3;
            estado = 4;
            LedGreen = 1;//Acende o verde
            LedRed = 0;//Apaga o vermelho
            LedYellow = 0;//Apaga o amarelo
            break;
        case 2://amarelo -> vermelho
            cont = 4;
            estado = 1;
            LedRed = 1;//Acende o vermelho
            LedGreen = 0;//Apaga o verde
            LedYellow = 0;//Apaga o amarelo
            break;
        case 3://verde -> amarelo
            cont = 4;
            estado = 2;
            LedYellow = 1;//Acende o amarelo
            LedGreen = 0;//Apaga o verde
            LedRed = 0;//Apaga o vermelho
            break;
    }
}

void interrupt low_priority pic_ist(void){ // Interrupção
    //interrupção para alterar a cor do led
    cont--;
    if(TMR0IF){
        INTCONbits.TMR0IF = 0; 
        TMR0 = 45914; 
        if(cont<1){//se o contador chegar a zero chama a função de alternar o modo
            AlternaModo();
        }
        TMR0 = 0; // Zera o contador de interrupção
        INTCONbits.TMR0IF = 0; // Limpa flag de interrupção
    }
    
    /*if (TMR0IF){
        INTCONbits.TMR0IF = 0; 
        TMR0 = 45914; 
        cont++;
        if (cont > 1){
            flag_seg =1;
            cont =0;
        }
    }*/
}

void AtualizaTela(char flag_tela){//Telas
    switch(flag_tela){
        case 0:
            SetDDRamAddr(0x00);
            sprintf(tela," SEMAPHORE TEST ");
            putrsXLCD(tela);
            SetDDRamAddr(0x40);
            sprintf(tela,"-- Press Start --");
            putrsXLCD(tela);
            break;
        case 1:
            SetDDRamAddr(0x00);
            sprintf(tela," --- In test --- ");
            putrsXLCD(tela);
            SetDDRamAddr(0x40);
            sprintf(tela,"       ***       ");
            putrsXLCD(tela);
            break;
        case 2:
            SetDDRamAddr(0x00);
            sprintf(tela,"  --- SCORE ---  ");
            putrsXLCD(tela);
            SetDDRamAddr(0x40);
            sprintf(tela,"Acerts:%d ",acertos, " Errors:%d ", erros);
            putrsXLCD(tela);
            break;
        default:
            break;
    }
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

void main(void) {
    ADCON1= 0x0F;
    TRISC = 0x00;//definir tris C como saída
    estado = 3; // inicia com verde
    init_XLCD();//inicializar o display
    config_inicial();//configuração inicial
    
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
    init();
    while(1){
        //AtualizaTela(flag_tela);//Iniciar com a tela inicial
        if(PORTDbits.RD0 == 1){//se o start for pressionado
                Delay10KTCYx (180);
                flag_tela = 1;
                AtualizaTela(flag_tela);//chama a tela de IN TEST
            }
    }
    return;
}