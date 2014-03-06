
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
/* Declaracion de variables globales de usuario                               */
/******************************************************************************/

/******************************************************************************/
/* Programa principal                                                         */
/******************************************************************************/

void main(void)
{
    bool luz=false;
    long retardo,retardo_max=2500; // Retardo maximo 3000 x 10 ms = 30 segundos
    ConfigureOscillator();  // Configuramos el oscilador del micro
    InitApp();              // Inicializa puertos de I/O y perifericos
    // Delay por secuencia inicializacion sensor PIR
    __delay_ms(27000);
    Enciende_Luz();
    __delay_ms(1000);
    Apaga_Luz();
    __delay_ms(1000);
    Enciende_Luz();
    __delay_ms(1000);
    Apaga_Luz();
    // Fin inicializacion
    // Comienza bucle infinito
    while(1){
        if(!luz)
            SLEEP(); // Entra en modo bajo consumo hasta que ocurra una interrupcion solamente cuando esta apagada la luz
        if(ADRESL == 1){ // Si es igual a uno esta encendido el circuito. Habilitado desde las interrupciones.
            // Solamente ingresa aca si esta prendida la luz
            if(luz){
                // Preguntamos si retardo max (25 segundos) es mayor que cero.
                if(retardo_max > 0) // Si es mayor decrementamos. Siempre deberia pasar por aca.
                    retardo_max--;
                else{ // Sino, pasaron 20 segundos, apagamos la luz.
                    retardo_max=2500; // Retardo maximo 2500 x 10 ms = 25 segundos
                    Apaga_Luz();
                    luz=false;
                } // Cierra else
            } // Cierra if(luz)
            else{
                luz=true;
                Enciende_Luz();
            }
        } // Cierra if(ADRESL == 1)
        else{ // Sino significa que se debe deshabilitar porque el sensor ldr informa que hay luz solar
            // ADRESL = 0 --> manejado desde las interrupciones
            if(luz){
                // Si estaba encendida, esperamos 3 seg, la apagamos y cambiamos la bandera
                for(retardo=300;retardo>0;retardo--)
                    __delay_ms(10);
                Apaga_Luz();
                luz=false;
                retardo_max=2500; // Retardo maximo 2500 x 10 ms = 25 segundos
            } // Cierra if(luz)
        } // Cierra else
        __delay_ms(10); // Delay de 10 ms
    } // Cierra el while
} // Cierra el main