/*
    __diffpressure_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__diffpressure_driver.h"
#include "__diffpressure_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __DIFFPRESSURE_DRV_I2C__
static uint8_t _slaveAddress;
#endif

const uint8_t _DIFFPRESSURE_NOT_RDY = 0;
const uint8_t _DIFFPRESSURE_OK      = 1;
const uint8_t _DIFFPRESSURE_OVH     = 2;
const uint8_t _DIFFPRESSURE_OVL     = 3;


/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __DIFFPRESSURE_DRV_SPI__

void diffpressure_spiDriverInit(T_DIFFPRESSURE_P gpioObj, T_DIFFPRESSURE_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
    hal_gpio_csSet(0);
}

#endif
#ifdef   __DIFFPRESSURE_DRV_I2C__

void diffpressure_i2cDriverInit(T_DIFFPRESSURE_P gpioObj, T_DIFFPRESSURE_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __DIFFPRESSURE_DRV_UART__

void diffpressure_uartDriverInit(T_DIFFPRESSURE_P gpioObj, T_DIFFPRESSURE_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif



/* ----------------------------------------------------------- IMPLEMENTATION */

/* Generic read data function */
int32_t diffpressure_readData()
{
    uint8_t buffer[3] = {0};
    int32_t result = 0;

    hal_gpio_csSet(0);
    Delay_100ms();
    hal_spiRead( buffer, 3);
    hal_gpio_csSet(1);
    
    result = buffer[0];
    result = ( result << 8 ) | buffer[1];
    result = ( result << 8 ) | buffer[2];
    
    if ( ( buffer[0] & 0x20) >> 5 )       // Bit 21 = 1 ; value is negative
    {
        result = result - 4194304;        // for 22 bit resolution
    }

    return result;
}

/* Get kPa Difference function */
int32_t diffpressure_getKpaDifference( int32_t difference )
{
    float press;
    float volt;
    int32_t result;

    volt = ( 5.0f / 2097151.0f ) * (float) difference;
    press = ( volt / 0.45f ) - 0.45f;
    
    result = (int32_t) ( press * 1000.0f );

    return result;
}

/* Check status of measurement */
status_t diffpressure_statusCheck( int32_t result )
{
    if( !result )
        return NOT_RDY;
    if( result > 0x00BFFFFE)
        return OVH;
    if( result > 0x009FFFFF )
        return OVL;

    return OK;
}




/* -------------------------------------------------------------------------- */
/*
  __diffpressure_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */