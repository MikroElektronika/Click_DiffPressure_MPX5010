![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

![Diff Pressure Click](http://cdn.mikroe.com/img/click/diff-pressure/diff-pressure-click.png)

---
[Product Page](http://www.mikroe.com/click/diff-pressure/)

[Manual Page](http://docs.mikroe.com/Diff_pressure_click)

---

### General Description

Diff pressure is a mikroBUS add-on board carrying an NXP MPXV5010DP signal conditioned, temperature compensated and calibrated pressure sensor with two axial ports to accommodate industrial grade tubing. It is designed for comparing two pressure measurements.

The two ports are designated as Pressure side (P1) and Vacuum side (P2). The sensor is designed to operate with a positive differential pressure where P1 > P2. The measurement range is from 0 to 10 kPa. In the temperature range between 0º and 85ºC, the sensor has a maximum error rate of 5.0%.

MPXV5010DP IC has an analog output. The signal passes through the onboard 22-bit ADC before being outputted through the mikroBUS SPI interface (CS, SCK, MISO).

Diff pressure click is designed to use either a 3.3V or a 5V power supply.


---

### Example

#### Configuration
* MCU:             STM32F107VC
* Dev.Board:       EasyMx Pro v7
* Oscillator:      72 Mhz internal
* Ext. Modules:    Diff Pressure click
* SW:              MikroC PRO for ARM 4.7.4

```

/*      Functions
 ****************************/

#include "diff_pressure_hw.h"

sbit DIFF_PRESSURE_CS         at GPIOD_ODR.B13;
sbit DIFF_PRESSURE_RST  at GPIOC_ODR.B2;
sbit DIFF_PRESSURE_RDY  at GPIOC_IDR.B11; //SPI3 MISO pin, data is converted and ready when this pin goes low ( 0 )

void system_setup( void );

void main()
{
    //Local Declarations
    int32_t buffer = 0;
    char uart_text[20] = { 0 };
    float difference = 0.;

    system_setup();

    while (1)
    {
        if (        diff_pressure_read_adc( &buffer ) == OK )
        {
            LongToStr( buffer, uart_text );
            UART1_Write_Text( "ADC Value: " );
            Ltrim( uart_text );
            UART1_Write_Text( uart_text );
            UART1_Write_Text( "\r\n" );
            difference = diff_pressure_get_kpa_difference( buffer );
            sprintf( uart_text, "KPA Difference: %.2f", difference );
            UART1_Write_Text( uart_text );
            UART1_Write_Text( "\r\n" );
            Delay_ms( 100 );
            buffer = 0;
        }
        else if ( diff_pressure_read_adc( &buffer ) == OVH )
            UART1_Write_Text( "Overflow happened\r\n" );
        else if ( diff_pressure_read_adc( &buffer ) == OVL )
            UART1_Write_Text( "Underflow happened\r\n" );
    }


}

void system_setup( void )
{
    //GPIOs
    GPIO_Digital_Output( &GPIOD_BASE, _GPIO_PINMASK_13 );
    GPIO_Digital_Output( &GPIOC_BASE, _GPIO_PINMASK_2 );
    GPIO_Digital_Input( &GPIOC_BASE, _GPIO_PINMASK_11 );

    //UART
    UART1_Init( 9600 );
    Delay_ms(200);
    UART1_Write_Text( "UART Initialized\r\n" );

    // SPI
    SPI3_Init_Advanced( _SPI_FPCLK_DIV128, _SPI_MASTER | _SPI_8_BIT |
                        _SPI_CLK_IDLE_LOW | _SPI_FIRST_CLK_EDGE_TRANSITION |
                        _SPI_MSB_FIRST | _SPI_SS_DISABLE | _SPI_SSM_ENABLE |
                        _SPI_SSI_1, &_GPIO_MODULE_SPI3_PC10_11_12 );
    Delay_ms(200);
    UART1_Write_Text( "SPI Initialized\r\n" );

    //Diff Pressure Click
    diff_pressure_init();
    UART1_Write_Text( "Diff Pressure Click Initialized\r\n" );

}

```


