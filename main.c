/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    bool luz=false;
    long retardo,retardo_max=2000; // Retardo maximo 6000 x 10 ms = 60 segundos
    // Configuramos el oscilador del micro
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
    
    // Bucle infinito
    while(1){
        SLEEP();
        if(ADRESL == 1){
            // Preguntamos si hay un uno en la pata GPIO4 que corresponden a las barreras infrarrojas
            if(GP4){
                // Si hay un uno, preguntamos si estaba encendida la luz
                if(luz){
                    // Si estaba encendida, esperamos 3 seg, la apagamos y cambiamos la bandera
                    for(retardo=300;retardo>0;retardo--){
                        __delay_ms(10);
                    }
                    Apaga_Luz();
                    luz=false;
                }
                else{
                    // Si no estaba encendida, la encendemos y cambiamso la bandera
                    Enciende_Luz();
                    luz=true;
                }
            }
            retardo=100;        // Cargamos este registro con 100 (equivale a 1s)
            while(GP4){
                retardo--;      // Decrementamos el registro
                if(retardo == 0)
                    break;      // Si llego a cero salimos
                __delay_ms(10); // Sino esperamos 10 ms
            }
            // Solamente ingresa aca si esta prendida la luz
            if(luz){
                // Preguntamos si retardo max (60 segundos) es mayor que cero.
                if(retardo_max > 0)
                // Si es mayor decrementamos. Siempre deberia pasar por aca.
                    retardo_max--;
                else{
                    // Si pasaron 60 segundos apagamos la luz.
                    retardo_max=2000; // Retardo maximo 6000 x 10 ms = 60 segundos
                    Apaga_Luz();
                    luz=false;
                } // Cierra else
            } // Cierra if luz
        } // Cierra 
        else{
            if(luz){
                // Si estaba encendida, esperamos 3 seg, la apagamos y cambiamos la bandera
                for(retardo=300;retardo>0;retardo--){
                    __delay_ms(10);
                }
                Apaga_Luz();
                luz=false;
            }
        }
        // Delay de 10 ms
        __delay_ms(10);
    } // Cierra el while

} // Cierra el main

