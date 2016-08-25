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
 * @file CLICKNAME_hal.c
 * @brief <h2> HAL layer </h2>
 */
/******************************************************************************
* Includes
*******************************************************************************/
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
#if defined( __MIKROC_PRO_FOR_ARM__ )       || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )
static void         ( *write_spi_p )            ( unsigned int data_out );
static unsigned int ( *read_spi_p )             ( unsigned int buffer );

#elif defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_8051__ )
static void         ( *write_spi_p )            ( unsigned char data_out );
static unsigned char( *read_spi_p )             ( unsigned char dummy );

#elif defined( __MIKROC_PRO_FOR_PIC32__ )
static void         ( *write_spi_p )            ( unsigned long data_out );
static unsigned long( *read_spi_p )             ( unsigned long buffer );

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
static void         ( *write_spi_p )            ( unsigned char data_out );
static unsigned char( *read_spi_p )             ( unsigned char dummy );
static void         ( *write_bytes_spi_p )      ( unsigned char *data_out,
                                                  unsigned int count );
static void         ( *read_bytes_spi_p )       ( unsigned char *buffer,
                                                  unsigned int count );
#endif

#if defined( __MIKROC_PRO_FOR_ARM__ )     || \
    defined( __MIKROC_PRO_FOR_AVR__ )     || \
    defined( __MIKROC_PRO_FOR_PIC__ )     || \
    defined( __MIKROC_PRO_FOR_PIC32__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )   || \
    defined( __MIKROC_PRO_FOR_8051__ )    || \
    defined( __MIKROC_PRO_FOR_FT90x__ )
extern sfr sbit DIFF_PRESSURE_CS;
extern sfr sbit DIFF_PRESSURE_RDY;
#endif

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
void diff_pressure_hal_cs_high()
{
    DIFF_PRESSURE_CS = 1;
}

void diff_pressure_hal_cs_low()
{
    DIFF_PRESSURE_CS = 0;
}

void diff_pressure_hal_init()
{
#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_AVR__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_8051__ )
    write_spi_p             = SPI_Wr_Ptr;
    read_spi_p              = SPI_Rd_Ptr;

#elif defined( __MIKROC_PRO_FOR_PIC__ )
    write_spi_p             = SPI1_Write;
    read_spi_p              = SPI1_Read;

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
    write_spi_p             = SPIM_Wr_Ptr;
    read_spi_p              = SPIM_Rd_Ptr;
    write_bytes_spi_p       = SPIM_WrBytes_Ptr;
    read_bytes_spi_p        = SPIM_RdBytes_Ptr;
#endif
    diff_pressure_hal_cs_low();
}

uint8_t diff_pressure_hal_read( uint8_t *buffer,
                         uint16_t count )
{
        uint8_t timer = 0;
        
        diff_pressure_hal_cs_low();
        Delay_us(100);
        while( DIFF_PRESSURE_RDY == 1 )        //SDO pin works as a "ready" pin for data transfering
        {
                diff_pressure_hal_cs_high();
                Delay_us(1);
                diff_pressure_hal_cs_low();
                timer++;
                Delay_ms(10);

                if( timer >= 20 )
                        return 0;
        }

        diff_pressure_hal_cs_low();
    while( count-- )
        *( buffer++ ) = read_spi_p( DUMMY_BYTE );
        diff_pressure_hal_cs_high();

        return -1;
}

/*************** END OF FUNCTIONS ***************************************************************************/