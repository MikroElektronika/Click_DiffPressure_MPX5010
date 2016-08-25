![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

![Cap Extend Click](http://cdn.mikroe.com/img/click/cap-extend/cap-extend-click.png)

---
[Product Page](http://www.mikroe.com/click/cap-extend/)

[Manual Page](http://docs.mikroe.com/Cap_Extend_click)

---

### General Description

Cap Extend click is a mikroBUS™ add-on board with a SEMTECH SX8633 low power, capacitive button touch controller. It has 12 pins for connecting capacitive inputs (either touch-buttons or proximity sensors). Any sort of conductive object can be used as an input. Additional 8 GPIO pins, available on the side-edges of the board, can be used as LED drivers. The SX8633 IC integrates a 10 bit ADC – a resolution high enough to support a wide variety of touch pad sizes and shapes to be used with the click. Cap Extend click communicates with the target MCU through the mikroBUS™ I2C interface, with additional functionality provided by RST and INT pins. Designed to use a 3.3V power supply only.


---

### Example

#### Configuration
* MCU:             STM32F107VC
* Dev.Board:       EasyMx Pro v7
* Oscillator:      72 Mhz internal
* Ext. Modules:    Accel 3 click
* SW:              MikroC PRO for ARM 4.7.4

```
#include <stdint.h>

/*      Functions
 ****************************/

#include <stdint.h>
#include "capextend_hw.h"

void system_init( void );

sbit RST at GPIOC_ODR.B2;

//Global Declatations
uint8_t address     = 0x2B;
uint8_t my_buffer         = 0;

void system_init( void )
{
    //GPIOs
    GPIO_Digital_Output( &GPIOC_BASE, _GPIO_PINMASK_2 );
    GPIO_Digital_Output( &GPIOD_BASE, _GPIO_PINMASK_ALL );

    //Toggle Reset Pin
    RST = 0;
    Delay_ms(50);
    RST = 1;
    Delay_ms(200);
    
    //Initialize UART
    UART1_Init( 9600 );
    Delay_ms(100);
    UART1_Write_Text( "UART Initialized\r\n" );
    
    //Initialize I2C
    I2C1_Init_Advanced( 400000, &_GPIO_MODULE_I2C1_PB67 );
    UART1_Write_Text( "I2C Initialized\r\n" );
    
    //Initialize Cap Extend
    capextend_init( address );
    UART1_Write_Text( "Cap Extend Initialized\r\n" );
    
}

void main() 
{
    //Local Decalartions
    uint8_t msb        = 0;
    uint8_t lsb          = 0;
    char uart_text[20] = { 0 };
    
    system_init();
    Delay_ms(100);
    
    GPIOD_ODR = 0xFF;

    while(1)
    {
         msb = capextend_read_msb_buttons();
         lsb = capextend_read_lsb_buttons();
         GPIOD_ODR = ( lsb | ( msb << 8 ) );

    }  //While

}  //Main

```


