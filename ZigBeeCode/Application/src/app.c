/**************************************************************************//**
  \file app.c

  \brief Basis-Anwendung.

  \author Markus Krauﬂe

******************************************************************************/


#include <appTimer.h>
#include <zdo.h>
#include <app.h>
#include <sysTaskManager.h>
#include <usartManager.h>

#include <i2cPacket.h>

//#define MEAS_MODE 0x01
//#define DRIVE_MODE 001
//#define ALG_RESULT_DATA 0x02

	static AppState_t appstate = APP_INIT;	
	static HAL_AppTimer_t readTimer;
	
	static uint8_t ccs811Data[8];
	static uint8_t output_CO2[]="Co2: 0000pm\r\n";
	static uint8_t output_TVOC[]="TVOC: 0000\r\n";
	static uint16_t _eCO2;
	static uint16_t _TVOC;
	
	static void readTimerFired(void);
	static void initTimer(void);
	static void readSensorDoneCb(void);
	static void calculateOutput(void);
	
	//static uint8_t setDriveMode[CCS811_DRIVE_MODE_10SEC];	
	
	
	static HAL_I2cDescriptor_t i2cdescriptor={
		.tty = TWI_CHANNEL_0,
		.clockRate = I2C_CLOCK_RATE_62,
		.f = readSensorDoneCb,
		.id = CCS811_DEVICE_ADDRESS,
		.data = ccs811Data,
		.length = 2,
		.lengthAddr = HAL_NO_INTERNAL_ADDRESS
	};
	
	
	
	void APL_TaskHandler(void){
		
		switch(appstate){
	
			case APP_INIT:
				appInitUsartManager();
				initTimer();
				
				if (-1 == HAL_OpenI2cPacket(&i2cdescriptor))
				appWriteDataToUsart((uint8_t*)"open fail\r\n", sizeof("open fail\r\n")-1);
				
				appstate=APP_NOTHING;
				
				break;

			case APP_READ_SENSOR:
				
				if (-1 == HAL_ReadI2cPacket(&i2cdescriptor))
					
					appWriteDataToUsart((uint8_t*)"read fail\r\n", sizeof("readfail\r\n")-1);
				
				appstate=APP_NOTHING;
				break;

			case APP_OUTPUT:
				calculateOutput();
				uint32_to_str(output_CO2, sizeof(output_CO2),_eCO2,5,4);
				uint32_to_str(output_TVOC, sizeof(output_TVOC),_TVOC,6,4);
				
				appWriteDataToUsart(output_CO2, sizeof(output_CO2));
				appWriteDataToUsart(output_TVOC, sizeof(output_TVOC));
				
				
				appstate=APP_NOTHING;
				break;

			case APP_NOTHING:
				break;
		}

	}
	
	//static uint8_t setDriveMode[] asm() {
		//_meas_mode.DRIVE_MODE = mode;
		//write8(CCS811_MEAS_MODE, _meas_mode.get());
	//}
	
	static void initTimer(){
		readTimer.interval = APP_READ_INTERVAL; 
		readTimer.mode = TIMER_REPEAT_MODE; 
		readTimer.callback = readTimerFired; 
		HAL_StartAppTimer(&readTimer); 
	}
	
	
	static void readTimerFired(){
		
		appstate =  APP_READ_SENSOR;
		SYS_PostTask(APL_TASK_ID);
			
	}
	
	static void readSensorDoneCb(){
			
			appstate= APP_OUTPUT;
			SYS_PostTask(APL_TASK_ID);
	
	}
	
	static void calculateOutput(){
		
		 _eCO2 = ((uint16_t)ccs811Data[0] << 8) | ((uint16_t)ccs811Data[1]);
		 _TVOC = ((uint16_t)ccs811Data[2] << 8) | ((uint16_t)ccs811Data[3]);
		
	}





/*******************************************************************************
  \brief The function is called by the stack to notify the application about 
  various network-related events. See detailed description in API Reference.
  
  Mandatory function: must be present in any application.

  \param[in] nwkParams - contains notification type and additional data varying
             an event
  \return none
*******************************************************************************/
void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *nwkParams)
{
  nwkParams = nwkParams;  // Unused parameter warning prevention
}

/*******************************************************************************
  \brief The function is called by the stack when the node wakes up by timer.
  
  When the device starts after hardware reset the stack posts an application
  task (via SYS_PostTask()) once, giving control to the application, while
  upon wake up the stack only calls this indication function. So, to provide 
  control to the application on wake up, change the application state and post
  an application task via SYS_PostTask(APL_TASK_ID) from this function.

  Mandatory function: must be present in any application.
  
  \return none
*******************************************************************************/
void ZDO_WakeUpInd(void)
{
}

#ifdef _BINDING_
/***********************************************************************************
  \brief The function is called by the stack to notify the application that a 
  binding request has been received from a remote node.
  
  Mandatory function: must be present in any application.

  \param[in] bindInd - information about the bound device
  \return none
 ***********************************************************************************/
void ZDO_BindIndication(ZDO_BindInd_t *bindInd)
{
  (void)bindInd;
}

/***********************************************************************************
  \brief The function is called by the stack to notify the application that a 
  binding request has been received from a remote node.

  Mandatory function: must be present in any application.
  
  \param[in] unbindInd - information about the unbound device
  \return none
 ***********************************************************************************/
void ZDO_UnbindIndication(ZDO_UnbindInd_t *unbindInd)
{
  (void)unbindInd;
}
#endif //_BINDING_

/**********************************************************************//**
  \brief The entry point of the program. This function should not be
  changed by the user without necessity and must always include an
  invocation of the SYS_SysInit() function and an infinite loop with
  SYS_RunTask() function called on each step.

  \return none
**************************************************************************/
int main(void)
{
  SYS_SysInit();
  
  for(;;) 
  
  {SYS_RunTask();}
}
	



//eof app.c
