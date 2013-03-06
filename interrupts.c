/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Unfortunately the baseline detection 
 * macro is named _PIC12 */

#ifndef _PIC12

void interrupt isr(void)
{
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */

#if 0x04
    if(GPIF){
        GPIF=0;
        if(!GP2){
            RP0 = 1;        // Cambiamos de banco al banco 1
            INTE = 1;       // Habilita interrupcion por GP2
            GPIE = 0;       // Deshabilita interrupcion por cambio de estados en los puertos
            RP0 = 0;        // Volvemos al banco 0
        }
    }
    else{
        if(INTF){ // Verifica si la interrupcion es externa GP2
            INTF = 0;           // Borra la bandera
            if(ADRESL == 0){     // Verificamos si es la condicion inicial
                ADRESL = 1;      // Habilitamos el funcionamiento del circuito
                RP0 = 1;        // Cambiamos de banco al banco 1
                OPTION_REG = 0x80;  // Configuramos el timer con flanco descendente
                INTE = 0;       // Deshabilita interrupcion por GP2
                GPIE = 1;       // Habilita interrupcion por cambio de estados en los puertos
                RP0 = 0;        // Volvemos al banco 0
            }
            else{
                ADRESL = 0;      // Deshabilitamos el funcionamiento del circuito
                RP0 = 1;        // Cambiamos de banco al banco 1
                OPTION_REG = 0xC0;  // Configuramos el timer con flanco ascendente
                INTE = 1;       // Habilita interrupcion por GP2
                GPIE = 0;       // Deshabilita interrupcion por cambio de estados en los puertos
                RP0 = 0;        // Volvemos al banco 0
            }
        }
    }
#endif
}
#endif


