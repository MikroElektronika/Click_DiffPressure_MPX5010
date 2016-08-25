/****************************************************************************
* Title                 :   Diff Pressure CLICK
* Filename              :   diff_pressure_hw.h
* Author                :   CAL
* Origin Date           :   07/07/2016
* Notes                 :   Hardware Access layer
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version     Initials     Description
*  07/07/16        .1               CAL     Interface Created.
*
*****************************************************************************/
/**
 * @file diff_pressure_hal.h
 * @brief <h2> HAL layer </h2>
 *
 * @par
 * HAL layer for
 * <a href="http://www.mikroe.com">MikroElektronika's</a> Diff Pressure click
 * board.
 */
#ifndef DIFF_PRESSURE__HAL_H_
#define DIFF_PRESSURE_HAL_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define DUMMY_BYTE                                                  0x00
/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief <h3> CS High </h3>
 *
 * @par
 * Used by HW layer functions to set CS PIN high ( deselect )
 */
void diff_pressure_hal_cs_high( void );

/**
 * @brief <h3> CS Low </h3>
 *
 * @par
 * Used by HW layer functions to set CS PIN low ( selecet )
 */
void diff_pressure_hal_cs_low( void );

/**
 * @brief <h3> HAL Initialization </h3>
 *
 * Hal layer initialization. Must be called before any other function.
 */
void diff_pressure_hal_init( void );

/**
 * @brief <h3> HAL Read </h3>
 *
 * @par
 * Reads data from SPI bus
 *
 *
 * @param[out] buffer
 * @param[in] count
 */
uint8_t diff_pressure_hal_read( uint8_t *buffer,
                         uint16_t count );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* DIFF_PRESSURE_HAL_H_ */

/*** End of File **************************************************************/
