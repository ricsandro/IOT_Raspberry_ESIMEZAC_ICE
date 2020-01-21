
#include "io430.h"
#include "CON_DEC_SERIAL.h"
char buffer;    // variable de Rx,Tx
volatile int s,val;
//volatile  char funcion;
//volatile int ms,ns,zs,is,cs;
//volatile int memory[10];


int uno(void)
{ ADC10CTL0 = SREF_0+ADC10SHT_3+REFON+ADC10ON;              //Configuracion de Pag 553  registro uno
  ADC10CTL1 = INCH_3+CONSEQ_0;                  /// Canal de entrada 5 (un solo canal ) 
  ADC10AE0 |= BIT3;  
  ADC10CTL0 |= ENC+ADC10SC; ///// Aqui activa el convertidor
  __delay_cycles(190);
  val=ADC10MEM;
  s=val;  
}
int dos(void)
{ ADC10CTL0 = SREF_0+ADC10SHT_3+REFON+ADC10ON;              //Configuracion de Pag 553  registro uno
  ADC10CTL1 = INCH_4+CONSEQ_0;                  /// Canal de entrada 5 (un solo canal ) 
  ADC10AE0 |= BIT4;
  ADC10CTL0 |= ENC+ADC10SC; ///// Aqui activa el convertidor
  __delay_cycles(190);
  val=ADC10MEM; 
  s=val;
}
int tres(void)
{ ADC10CTL0 = SREF_0+ADC10SHT_3+REFON+ADC10ON;              //Configuracion de Pag 553  registro uno
  ADC10CTL1 = INCH_5+CONSEQ_0;                  /// Canal de entrada 5 (un solo canal ) 
  ADC10AE0 |= BIT5;    
  ADC10CTL0 |= ENC+ADC10SC; ///// Aqui activa el convertidor
  __delay_cycles(190);
  val=ADC10MEM;
  s=val;  
}
int cuatro(void)
{ ADC10CTL0 = SREF_0+ADC10SHT_3+REFON+ADC10ON;              //Configuracion de Pag 553  registro uno
  ADC10CTL1 = INCH_6+CONSEQ_0;                  /// Canal de entrada 5 (un solo canal ) 
  ADC10AE0 |= BIT6;  
  ADC10CTL0 |= ENC+ADC10SC; ///// Aqui activa el convertidor
  __delay_cycles(190);
  val=ADC10MEM;
  s=val;
 }

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  //DCO Trabajando a 12MHz aprox.    
    //EXTERNAL CLOCK
    //BCSCTL1 &= (~XTS);
    //BCSCTL3 &= ~(BIT4|BIT5);    
  BCSCTL1 = CALBC1_12MHZ;
  DCOCTL  = CALDCO_12MHZ;
     
  // CONFIGURACIONES DE PINES
  P2SEL |=(BIT6 | BIT7);  ///SALIDAS
  P2SEL2 &=~(BIT6 | BIT7);////SALIDAS
  P1DIR |= BIT0;            // P1.0 (LED) como salida digital    

  /*********************Para cambiar los valores de BAUD , por cambio de los valores de freq interna del micro 
pagina 424*//////////////////////
  
  P1SEL  = BIT1 + BIT2 ;                // Configurando las terminales P1.1 y P1.2
  P1SEL2 = BIT1 + BIT2 ;                // como parte del sistema UART
  P1DIR &= ~BIT1;                       // P1.1 <-- RXD
  P1DIR |= BIT2;                        // P1.2 --> TXD
  UCA0CTL1 |= UCSSEL_2;                 // SMCLK
  //UCA0CTL1 |= UCSSEL_1;                 // ACLK
  
  //--------9600bps----------------------------------------------
 // UCA0BR0 = 104;                       // 1MHz 9600
 // UCA0BR1 = 0;                     //
  //UCA0MCTL = UCBRS0;                   // Modulation UCBRSx = 1
  //--------9600bps---------------------4 MHz  
  //UCA0BR0 = 416;                     // 12MHz/9600=1250 (see User's Guide)
  //UCA0BR1 = 0;                     // 1250 = 0x4e2
  //UCA0MCTL = UCBRS2+UCBRS1;            // Modulation UCBRSx = 6 AUN NO FUNCIONA     
  //--------9600bps---------------------12 MHz
  UCA0BR0 = 1250;                     // 12MHz/9600=1250 (see User's Guide)
  UCA0BR1 = 0x04;                     // 1250 = 0x4e2
  UCA0MCTL = UCBRS_0+UCBRF_0;         // Modulation UCBRSx=0, UCBRFx=0
  //--------9600bps---------------------16 MHz
  //UCA0BR0 = 1666;                      // 16MHz/115200=138 (see User's Guide)
  //UCA0BR1 = 0x00;                     //
  //UCA0MCTL = UCBRS_7+UCBRF_0;         // Modulation UCBRSx=3, UCBRFx=0   
   //-------------------------------------------------------------
  //--------19200bps---------------------------------------------
  //UCA0BR0 = 52;                        // 1MHz 19200
  //UCA0BR1 = 0;                         // 1MHz 19200
  //-------------------------------------------------------------
  //--------38400bps---------------------------------------------
  //UCA0BR0 = 26;                        // 1MHz 38400
  //UCA0BR1 = 0;                         // 1MHz 38400
  //-------------------------------------------------------------
  //--------115200bps----------------------------------------------
  //UCA0BR0 = 8;                         // 1MHz 115200
  //UCA0BR1 = 0;                         // 1MHz 115200
  //UCA0MCTL = UCBRS2+UCBRS1;            // Modulation UCBRSx = 6
  //-------------------------------------------------------------
  
  
  UCA0CTL1 &= ~UCSWRST;                 // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                      // Enable USCI_A0 RX interrupt
  
  __bis_SR_register(GIE);    
  
   while (1)
  {
  }
    return 0;

}

//  Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
  buffer= UCA0RXBUF;      /// LEER EL VALOR AL BUFFER DE TRANSMISION
//__delay_cycles(1000);
//UCA0TXBUF=buffer;        /// CARGAR EL VALOR AL BUFFER DE TRANSMISION
  //   while (!(IFG2&UCA0TXIFG))              //// BANDERA QUE ESPERA A QU ACABE DE RECIBIR LOS DATOS 
    //  {}
P1OUT^=BIT0;
if(buffer =='1' )
uno();
if(buffer =='2' )
dos();
if(buffer =='3' )
tres();
if(buffer =='4' )
cuatro();

Send_Num(s);
}

  