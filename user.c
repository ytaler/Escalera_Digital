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
    TRISIO = 0x1D;  // Configuramos GP5 y GP1 como salida, el resto como entrada - 0001-1101
    GP1 = 1;        // Comanda fuente secundaria, transistor PNP
    WPU = 0;        // Deshabilitamos las resistencias pull-up
    IOC = 0x1C;     // Habilitamos interrupciones por cambio de GP2, GP3 y GP4 - 0001-1100
}