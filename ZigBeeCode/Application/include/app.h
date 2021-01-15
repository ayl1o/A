//#include <stdint-gcc.h>
/**************************************************************************//**
  \file app.h

  \brief Usart-Anwendung Headerdatei.

  \author
    Markus Krauﬂe

******************************************************************************/
#ifndef _APP_H
#define _APP_H

#define APP_READ_INTERVAL    1000
#define CCS811_DEVICE_ADDRESS   0x5A

#define OPEN_USART HAL_OpenUsart
#define CLOSE_USART HAL_CloseUsart
#define WRITE_USART HAL_WriteUsart
#define READ_USART HAL_ReadUsart
#define USART_CHANNEL USART_CHANNEL_1
#define USART_RX_BUFFER_LENGHT 0

void appInitUARTManager( void );
void appWriteDataToUart(uint8_t* aData , uint8_t aLength);
typedef enum {
	
	CCS811_MEAS_MODE = 0x01,
	CCS811_ALG_RESULT_DATA = 0x02,

	//CCS811_DRIVE_MODE_1SEC = 0x01,
	CCS811_DRIVE_MODE_10SEC = 0x02,
	
	APP_INIT,
	APP_READ_SENSOR,
	APP_OUTPUT,
	APP_NOTHING
	
	
} AppState_t;

struct meas_mode {
 
    
  };
  


#endif 


