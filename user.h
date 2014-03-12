/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

#define Enciende_Luz() GP5 = 1;
#define Apaga_Luz() GP5 = 0;
#define Enciende_Fuente() GP1 = 0;
#define Apaga_Fuente() GP1 = 1;

void InitApp(void);         // Inicializacion de I/O y perifericos
