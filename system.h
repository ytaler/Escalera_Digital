/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        500000L
#define FCY             SYS_FREQ/4
#define _XTAL_FREQ      4000000

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
