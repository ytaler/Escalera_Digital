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
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    INTCON = 0;     // Deshabilitamos interrupciones
    GPIO = 0;       // Inicializamos puertos
    CMCON = 0x07;   // Apgamos comparadores
    ADCON0 = 0;     // ADC apagado
    RP0 = 1;        // Cambiamos de banco al banco 1
    GIE = 1;        // Habilita interrupciones
    INTE = 1;       // Habilita interrupcion extrena por el pin GPIO2
    ANSEL = 0;      // AD Apagado
    TRISIO = 0x1F;  // Configuramos GP5 como salida y el resto como entrada
    WPU = 0;        // Deshabilitamos las resistencias pull-up
    IOC = 0x14;     // Habilitamos interrupciones por cambio de GP4
    RP0 = 0;        // Cambiamos de banco al banco 1
    T1CON = 0;      // Apgamos el timer 1
    if(GP2){     // Verificamos si es la condicion inicial
        ADRESL = 1;      // Habilitamos el funcionamiento del circuito
        RP0 = 1;        // Cambiamos de banco al banco 1
        OPTION_REG = 0x80;  // Configuramos el timer con flanco descendente
        INTE = 0;       // Deshabilita interrupcion por GP2
        GPIE = 1;       // Habilita interrupcion por cambio de estados en los puertos
        RP0 = 0;        // Volvemos al banco 0
    }
    else    ADRESL = 0;

}

