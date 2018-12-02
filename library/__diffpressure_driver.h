/*
    __diffpressure_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __diffpressure_driver.h
@brief    Diff_Pressure Driver
@mainpage Diff_Pressure Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   DIFFPRESSURE
@brief      Diff_Pressure Click Driver
@{

| Global Library Prefix | **DIFFPRESSURE** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Aug 2018.**      |
| Developer             | **Nenad Filipovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _DIFFPRESSURE_H_
#define _DIFFPRESSURE_H_

/** 
 * @macro T_DIFFPRESSURE_P
 * @brief Driver Abstract type 
 */
#define T_DIFFPRESSURE_P    const uint8_t*

/** @defgroup DIFFPRESSURE_COMPILE Compilation Config */              /** @{ */

   #define   __DIFFPRESSURE_DRV_SPI__                            /**<     @macro __DIFFPRESSURE_DRV_SPI__  @brief SPI driver selector */
//  #define   __DIFFPRESSURE_DRV_I2C__                            /**<     @macro __DIFFPRESSURE_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __DIFFPRESSURE_DRV_UART__                           /**<     @macro __DIFFPRESSURE_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup DIFFPRESSURE_VAR Variables */                           /** @{ */

extern const uint8_t _DIFFPRESSURE_NOT_RDY;
extern const uint8_t _DIFFPRESSURE_OVH;
extern const uint8_t _DIFFPRESSURE_OVL;
extern const uint8_t _DIFFPRESSURE_OK;
                                                                       /** @} */
/** @defgroup DIFFPRESSURE_TYPES Types */                             /** @{ */

typedef enum
{
	NOT_RDY = 0,
	OVH     = 2,
	OVL     = 3,
        OK      = 1
} status_t;
                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup DIFFPRESSURE_INIT Driver Initialization */              /** @{ */

#ifdef   __DIFFPRESSURE_DRV_SPI__
void diffpressure_spiDriverInit(T_DIFFPRESSURE_P gpioObj, T_DIFFPRESSURE_P spiObj);
#endif
#ifdef   __DIFFPRESSURE_DRV_I2C__
void diffpressure_i2cDriverInit(T_DIFFPRESSURE_P gpioObj, T_DIFFPRESSURE_P i2cObj, uint8_t slave);
#endif
#ifdef   __DIFFPRESSURE_DRV_UART__
void diffpressure_uartDriverInit(T_DIFFPRESSURE_P gpioObj, T_DIFFPRESSURE_P uartObj);
#endif


/** @defgroup DIFFPRESSURE_FUNC Driver Functions */                   /** @{ */


/**
 * @brief     Generic read data function
 *
 * @return    22-bit values of ADC module
 *
 * Function read ADC value from Diff Pressure click
 *
 * @note
 * Delay is 100 ms
 */
int32_t diffpressure_readData();


/**
 * @brief     Get kPa Difference function
 *
 * @return    kPa value ( uint32_t ) difference between two pressures
 *
 * Function get kPa difference
 */
int32_t diffpressure_getKpaDifference( int32_t difference );

/**
 * @brief     Check status of measurement
 *
 * @return    status of measurement; OK, OVH or OVL
 *
 * Function check status of measurement
 */
status_t diffpressure_statusCheck( int32_t result );





                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Diff_Pressure_STM.c
    @example Click_Diff_Pressure_TIVA.c
    @example Click_Diff_Pressure_CEC.c
    @example Click_Diff_Pressure_KINETIS.c
    @example Click_Diff_Pressure_MSP.c
    @example Click_Diff_Pressure_PIC.c
    @example Click_Diff_Pressure_PIC32.c
    @example Click_Diff_Pressure_DSPIC.c
    @example Click_Diff_Pressure_AVR.c
    @example Click_Diff_Pressure_FT90x.c
    @example Click_Diff_Pressure_STM.mbas
    @example Click_Diff_Pressure_TIVA.mbas
    @example Click_Diff_Pressure_CEC.mbas
    @example Click_Diff_Pressure_KINETIS.mbas
    @example Click_Diff_Pressure_MSP.mbas
    @example Click_Diff_Pressure_PIC.mbas
    @example Click_Diff_Pressure_PIC32.mbas
    @example Click_Diff_Pressure_DSPIC.mbas
    @example Click_Diff_Pressure_AVR.mbas
    @example Click_Diff_Pressure_FT90x.mbas
    @example Click_Diff_Pressure_STM.mpas
    @example Click_Diff_Pressure_TIVA.mpas
    @example Click_Diff_Pressure_CEC.mpas
    @example Click_Diff_Pressure_KINETIS.mpas
    @example Click_Diff_Pressure_MSP.mpas
    @example Click_Diff_Pressure_PIC.mpas
    @example Click_Diff_Pressure_PIC32.mpas
    @example Click_Diff_Pressure_DSPIC.mpas
    @example Click_Diff_Pressure_AVR.mpas
    @example Click_Diff_Pressure_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __diffpressure_driver.h

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