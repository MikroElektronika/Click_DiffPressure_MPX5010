/*
Example for Diff_Pressure Click

    Date          : Aug 2018.
    Author        : Nenad Filipovic

Test configuration TIVA :
    
    MCU              : TM4C129XNCZAD
    Dev. Board       : EasyMx PRO v7 for TIVA ARM
    ARM Compiler ver : v6.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes SPI and .
- Application Initialization - Initialization driver enable's - SPI. Start sending log via UART.
- Application Task - (code snippet) This is a example which demonstrates the use of Diff Pressure click board.
              The example is display
              values of ADC module (MPC3551) 22-bit register and
              value of difference pressure [ Pa ] via UART.

Additional Functions :

- Conversions
- Sprintf
- UART

*/

#include "Click_Diff_Pressure_types.h"
#include "Click_Diff_Pressure_config.h"


void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );
    mikrobus_spiInit( _MIKROBUS1, &_DIFFPRESSURE_SPI_CFG[0] );
    mikrobus_logInit( _MIKROBUS2, 9600 );
    Delay_100ms();
}

void applicationInit()
{
    diffpressure_spiDriverInit( (T_DIFFPRESSURE_P)&_MIKROBUS1_GPIO, (T_DIFFPRESSURE_P)&_MIKROBUS1_SPI );

    mikrobus_logWrite("  Start Measurements",_LOG_LINE);
    mikrobus_logWrite("-----------------------", _LOG_LINE);
    mikrobus_logWrite( "", _LOG_LINE );
    Delay_100ms();
}

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

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}