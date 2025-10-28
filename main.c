#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "TM4C123GH6PM.h"
#include "MyDefines.h"

void DelayMs(int ms);   // Software Delay Function
void SegDisplay(uint8_t d);
void Setup_GPIO(void);
char SevenSeg[] = { 0x3f,   // 0
                    0x06,   // 1
                    0x5B,   // 2
                    0x4F,   // 3
                    0x66,   // 4
                    0x6D,   // 5
                    0x7D,   // 6
                    0x07,   // 7
                    0x7F,   // 8
                    0x6F,   // 9
                    0x77,   // A
                    0x7C,   // B
                    0x39,   // C
                    0x5E,   // D
                    0x79,   // E
                    0x71,   // F
                  };

int main()
{
    int count = 0;
    static bool preSw2 = true;
    bool curSw1;
    bool curSw2;
    // Place your initialization/startup code here (e.g. Setup_GPIO() )
    Setup_GPIO();
    SegDisplay(0); //display 0
    while (1) {
        curSw1 = GPIOF->DATA & _PIN4;   //reset button
        curSw2 = GPIOF->DATA & _PIN0;   // count button
        
        if( curSw1 == false){   // if reset button is pressed 
            count = 0;               // go back to zero
        }
        
        else{
            if(preSw2 == true && curSw2 == false){      // detecting falling edge
                count=count+1;                                       //increase count by 1                
            }   
           
        }
        
        if (count >15){        //if count greater than 15
            count = 0;          //go back to zero
        }                  
        preSw2 = curSw2;      //updating previous state to current state
        SegDisplay(count);    //display count on 7 segment display
        DelayMs(20);
        }
}


//------------------------------------------------------------------------------

void SegDisplay(uint8_t d)
{
    char    seg;
    seg = SevenSeg[d];
    if(d > 15){
        return;
    }
    
    if((seg & _BIT0) == 0){                      //a
        GPIOA->DATA &= ~ _PIN2;
    }
    else{
        GPIOA->DATA |= _PIN2;     
    }
    
    
    if((seg & _BIT1) == 0){                     //b
        GPIOA->DATA &= ~_PIN3;
    }
    else{
        GPIOA->DATA |= _PIN3;
 }
    
    if((seg & _BIT2) == 0){                    //c
        GPIOA->DATA &= ~_PIN4;
    }
    else{
        GPIOA->DATA |= _PIN4;
    }
    
    if((seg & _BIT3) == 0){                   //d
        GPIOC->DATA &= ~_PIN4;
    }
    else{
        GPIOC->DATA |= _PIN4;      
    }
    
    if((seg & _BIT4) == 0){                   //e
        GPIOC->DATA &= ~_PIN5;
    }
    else{
        GPIOC->DATA |= _PIN5;
    }
    
    if((seg & _BIT5) == 0){                   //f
        GPIOC->DATA &= ~_PIN6;
    }
    else{
        GPIOC->DATA |= _PIN6;
    }
    
    if((seg & _BIT6) == 0){                  //g
        GPIOC->DATA &= ~_PIN7;
    }
    else{
        GPIOC->DATA |= _PIN7;
    }
    
    if((seg & _BIT7) == 0){                //dp
        GPIOD->DATA &= ~_PIN7;
    }
    else{
        GPIOD->DATA |= _PIN7;
    }
}
//------------------------------------------------------------------------------
/*
Device      Port.Pins            DIR                       DriveMode
Seg-a       PORTA.PIN2      OUT/POS
Seg-b       PORTA.PIN3      OUT/POS
Seg-c       PORTA.PIN4      OUT/POS
Seg-d       PORTC.PIN4     OUT/POS
Seg-f        PORTC.PIN5      OUT/POS
Seg-g       PORTC.PIN6     OUT/POS
Seg-dp     PORTC.PIN7    OUT/POS
SW1         PORTF.PIN4      IN/NEG               UP
SW2         PORTF.PIN0      IN/NEG               UP

Port ____
*/

void Setup_GPIO(void)
{
    // Configure GPIOs
    // 1. Enable Clock to the GPIO Modules (SYSCTL->RCGCGPIO |= (_PORTs);)
    SYSCTL->RCGCGPIO |= (_PORTA | _PORTC | _PORTD | _PORTF);
    // allow time for clock to stabilize (SYSCTL->PRGPIO & (_PORTs))
    while((SYSCTL->PRGPIO & (_PORTA | _PORTC | _PORTD | _PORTF)) != (_PORTA | _PORTC | _PORTD | _PORTF)) {};
    // 2. Unlock GPIO only PD7, PF0 on TM4C123G; PD7, PE7 on TM4C1294 (GPIOx->LOCK = 0x4C4F434B; and GPIOx->CR = _PINs;)
    GPIOD->LOCK = 0x4C4F434B;
    GPIOD->CR |= _PIN7;
    GPIOD->LOCK = 0;
    GPIOF->LOCK = 0x4C4F434B;
    GPIOF->CR |= _PIN0;
    //GPIOF->LOCK = 0;
    // 3. Set Analog Mode Select bits for each Port (GPIOx->AMSEL = _PINs; 0=digital, 1=analog)
    // 4. Set Port Control Register for each Port (GPIOx->PCTL = PMCn << _PTCL_PINn, check the PCTL table)
    // 5. Set Alternate Function Select bits for each Port (GPIOx->AFSEL = _PINs; 0=regular I/O, 1=PCTL peripheral)
    // 6. Set Output pins for each Port (Direction of the Pins: GPIOx->DIR = _PINs; 0=input, 1=output)
    GPIOA->DIR = _PIN2 | _PIN3 | _PIN4;
    GPIOC->DIR = _PIN4 | _PIN5 | _PIN6 | _PIN7;
    GPIOD->DIR = _PIN7;
    // 7. Set PUR bits (internal Pull-Up Resistor), PDR (Pull-Down Resistor), ODR (Open Drain) for each Port (0: disable, 1=enable)
    GPIOF->PUR = _PIN4 | _PIN0;
    // 8. Set Digital ENable register on all port.pins (GPIOx->DEN = _PINs; 0=disable, 1=enable)
    GPIOA->DEN = _PIN2 | _PIN3 | _PIN4;
    GPIOC->DEN = _PIN4 | _PIN5 | _PIN6 | _PIN7;
    GPIOD->DEN = _PIN7;
    GPIOF->DEN = _PIN0 | _PIN4;
}
//------------------------------------------------------------------------------
// Delay ms milliseconds (16MHz CPU Clock)
void DelayMs(int ms)
{
    volatile int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 4167; j++) {} // Do nothing for 1ms
}

