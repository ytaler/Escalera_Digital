/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"

/******************************************************************************/
/* Funciones de usuario                                                       */
/******************************************************************************/

void InitApp(void)
{
    GPIO = 0;       // Inicializamos puertos
    CMCON = 7;      // Apgamos comparadores
    ADCON0 = 0;     // ADC apagado
    T1CON = 0;      // Apgamos el timer 1
    ANSEL = 0;      // AD Apagado
    TRISIO = 0x1F;  // Configuramos GP5 y GP1 como salida, el resto como entrada - 0001-1101
    WPU = 0;        // Deshabilitamos las resistencias pull-up
    IOC = 0x1C;     // Habilitamos interrupciones por cambio de GP4 y GP2 - 0001-1100
    if(GP2){        // Verificamos si esta habilitado cuando prendemos el micro
        ADRESL = 1;         // Circuito encendido. Este registro es para otra cosa
                            // pero lo usamos para comunicarnos entre funciones
        OPTION_REG = 0x80;  // Configuramos el timer con flanco descendente
        INTCON = 0x88;      // Habilitamos interrupciones global e interrupcion por cambio de estado en GP2 y GP4
                            // GIE=1, GPIE=1 - 1000-1000
    }
    else{
        ADRESL = 0;         // Circuito apagado
        OPTION_REG = 0xC0;  // Configuramos el timer para funcionar con flanco ascendente
        INTCON = 0x90;      // Habilitamos interrupciones global e interrupcion extrena por el pin GP2
                            // GIE=1, INTE=1 - 1001-0000
    }
}