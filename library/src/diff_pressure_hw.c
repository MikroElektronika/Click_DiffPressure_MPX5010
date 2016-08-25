/****************************************************************************
* Title                 :   Diff Pressure CLICK
* Filename              :   diff_pressure_hw.h
* Author                :   CAL
* Origin Date           :   07/07/2016
* Notes                 :   Hardware layer
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version     Initials     Description
*  07/07/16        .1               CAL     Interface Created.
*
*****************************************************************************/
/**
 * @file diff_pressure_hw.c
 * @brief <h3> Hardware Layer </h3>
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include "diff_pressure_hw.h"
#include "diff_pressure_hal.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Private Function Definitions
*******************************************************************************/

/******************************************************************************
* Public Function Definitions
*******************************************************************************/
void diff_pressure_init()
{
        diff_pressure_hal_init();
}

status_t diff_pressure_read_adc( int32_t *buffer )
{
        uint8_t big_buffer[5] = { 0 };
        int32_t retval = 0;

        if( !diff_pressure_hal_read( big_buffer, 3 ) )
                return NOT_RDY;

        if( big_buffer[0] == 0x60 && big_buffer[2] > 0 )
                return OVH;
        if( big_buffer[0] == 0x9F && big_buffer[2] > 0 )
                return OVL;

        retval = big_buffer[0];
        retval = (retval << 8) | big_buffer[1];
        retval = (retval << 8) | big_buffer[2];

    if ( ( big_buffer[0] & 0x20) >> 5 )       // Bit 21 = 1 ; value is negative
        retval = retval - 4194304;                    // for 22 bit resolution

        *buffer = retval;
        return OK;
}

float diff_pressure_get_kpa_difference( int32_t difference )
{
        float press;
        float volt;

        volt = (5./2097151.) * difference;
        press = ( volt / 0.45 ) - 0.45;

        return press;
}

/*************** END OF FUNCTIONS *********************************************/