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
#define SYS_FREQ        500000L
#define FCY             SYS_FREQ/4
#define _XTAL_FREQ      4000000

#define Enciende_Fuente() GP1 = 0x01;
#define Apaga_Fuente() GP1 = 0x00;

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

#ifndef _PIC12

void interrupt isr(void){
    int i, resultado;

#if 0x04
    if(GPIF){
        /*
         * Interrupcion por cambio de estado en los puertos GPIO
         * Ingresa aca unicamente cuando esta activado el circuito,
         * NO hace nada en particular, solamente verifica si hay que
         * desactivar el circuito mediante la señal en GP2 (cero)
         */
        GPIF=0; // Borramos la bandera
        if(!GP2){
                    Apaga_Fuente()      // Dehabilitamos el transistor que comanda la fuente secundaria
                    ADRESL = 0;         // Deshabilitamos el funcionamiento del circuito
                    OPTION_REG = 0xC0;  // Configuramos el timer con flanco ascendente
                    INTE = 1;           // Habilita interrupcion por GP2
                    GPIE = 0;           // Deshabilita interrupcion por cambio de estados en los puertos
        } // Cierra if(!GP2)
    }
    else{
        if(INTF){
            /*
             * Verifica si la interrupcion es externa GP2
             * Si es externa, realiza un ciclo de 30 lecturas del sensor de luz
             * conectado a GP2. Si es mayor a 15, significa que ya hay suficiente
             * oscuridad para encender el circuito (>= de la mitad de lecturas)
             */
            INTF = 0;           // Borra la bandera
            resultado = 0;      // Inicializamos contador
            for(i=0;i<30;i++){
                if(GP2)
                    resultado = resultado + 1;
                __delay_ms(500);
            }
            // Si la sumatoria es mayor a la media,
            if(resultado >= 15){
                if(ADRESL == 0){        // Verificamos si es la condicion inicial
                    Enciende_Fuente()   // Habilitamos el transistor que comanda la fuente secundaria
                    ADRESL = 1;         // Habilitamos el funcionamiento del circuito
                    OPTION_REG = 0x80;  // Configuramos el timer con flanco descendente
                    INTE = 0;           // Deshabilita interrupcion por GP2
                    GPIE = 1;           // Habilita interrupcion por cambio de estados en los puertos
                    // Delay por secuencia inicializacion sensor PIR y estabilizacion de la fuente = 1 minuto
                    __delay_ms(15000);
                    __delay_ms(15000);
                    __delay_ms(15000);
                    __delay_ms(15000);
                    // Fin inicializacion
                } // Cierra if(ADRESL == 0)
            } // Cierta if(resultado >= 15)
            else{
                if(ADRESL == 1){
                    Apaga_Fuente()      // Dehabilitamos el transistor que comanda la fuente secundaria
                    ADRESL = 0;         // Deshabilitamos el funcionamiento del circuito
                    OPTION_REG = 0xC0;  // Configuramos el timer con flanco ascendente
                    INTE = 1;           // Habilita interrupcion por GP2
                    GPIE = 0;           // Deshabilita interrupcion por cambio de estados en los puertos
                } // Cierra if(ADRESL == 1)
            } // Cierra else if(resultado >= 15)
        } // Cierra if(INTF)
    } // Cierra else
#endif
}
#endif