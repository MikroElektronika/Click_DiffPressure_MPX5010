![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Diff Pressure Click

- **CIC Prefix**  : DIFFPRESSURE
- **Author**      : Nenad Filipovic
- **Verison**     : 1.0.1
- **Date**        : Aug 2018.

---

### Software Support

We provide a library for the Diff Pressure Click on our [LibStock](https://libstock.mikroe.com/projects/view/1901/diff-pressure-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library covers all the necessary functions to control of the Diff Pressure Click difference pressure measurement.

Key functions :

- ``` int32_t diffpressure_readData() ``` - Generic read data function
- ``` int32_t diffpressure_getKpaDifference( int32_t difference ) ``` - Get kPa Difference function
- ``` status_t diffpressure_statusCheck( int32_t result ) ``` - Check status of measurement

**Examples Description**

Description :

The application is composed of three sections :

- System Initialization - Initializes SPI.
- Application Initialization - Initialization driver enable's - SPI. Start sending log via UART.
- Application Task - (code snippet) This is a example which demonstrates the use of Diff Pressure click board.
              The example is display
              values of ADC module (MPC3551) 22-bit register and
              value of difference pressure [ Pa ] via UART.


```.c

void applicationTask()
{
    int32_t difference = 0;
    int32_t adcValue = 0;
    uint8_t differenceTxt[ 20 ];
    uint8_t adcValueTxt[ 20 ];
    uint8_t status;

    adcValue = diffpressure_readData();
    difference = diffpressure_getKpaDifference( adcValue );
    status = diffpressure_statusCheck( adcValue );

    LongToStr( adcValue, adcValueTxt );
    LongToStr( difference, differenceTxt );
    Ltrim(adcValueTxt);
    Ltrim(differenceTxt);

    if ( status == _DIFFPRESSURE_OK )
    {
        mikrobus_logWrite( "ADC Value:   ", _LOG_TEXT );
        mikrobus_logWrite( adcValueTxt, _LOG_LINE );

        mikrobus_logWrite( "Difference: ", _LOG_TEXT );
        mikrobus_logWrite( differenceTxt, _LOG_TEXT );
        mikrobus_logWrite( "  [Pa]", _LOG_LINE );

        Delay_ms(3000);
    }

    if ( status == _DIFFPRESSURE_OVH )
    {
        mikrobus_logWrite( "Overflow happened", _LOG_LINE );
        Delay_100ms();
    }

    if ( status == _DIFFPRESSURE_OVL )
    {
        mikrobus_logWrite( "Underflow happened", _LOG_LINE );
        Delay_100ms();
    }

    mikrobus_logWrite( "", _LOG_LINE );
}

```


The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/1901/diff-pressure-click) page.

Other mikroE Libraries used in the example:

- Conversions
- UART

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
### Architectures Supported

#### mikroC

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

#### mikroBasic

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

#### mikroPascal

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

---
---
