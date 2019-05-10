#include "main.h"
#include "stm32f4xx_hal.h"
#include "fatfs.h"

__IO uint8_t FlashData;

int main(void)
{
  timer = 0;
  timer_event = false;
  //FRESULT fr_result = FR_NOT_READY;
 /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  
  /* Configure the system clock */
  SystemClock_Config();
  
  /* Initialize all configured peripherals */
  /*MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_DMA_Init();
  MX_RTC_Init();
  MX_I2C1_Init();
  MX_SDIO_SD_Init();
  MX_FATFS_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();*/
  //MX_TIM5_Init();
  /*All State Machines Initialization*/
  /*current_state=SKELETON_INIT;
  uart_state=UART_INIT;*/

//  Initialized_Aurora_SM();

  /*aurora_system_state=EMA_INIT;
  gprs_state=GPRS_INIT;
  current_datastate=DR_INIT;*/

  /*Sensors Enabled*/
  /*EMA_status.BME_port=true;
  EMA_status.BME_node.Ch0=true;
  EMA_status.BME_node.Ch1=true;
  EMA_status.BME_node.Ch2=false;
  EMA_status.BME_node.Ch3=false;

  EMA_status.TSL_port=true;
  EMA_status.TSL_node.Ch0=true;
  EMA_status.TSL_node.Ch1=true;
  EMA_status.TSL_node.Ch2=false;
  EMA_status.TSL_node.Ch3=false;*/

 /*Configuration*/
  //__HAL_TIM_SetAutoreload(&htim4, (uint16_t)1999);
  /*EMA_cnfg.tmr_smpl=8;
  EMA_cnfg.pwr=SLEEP_MODE;//STOP_MODE; //SLEEP_MODE;*/

  //start_timers();
  /*if(HAL_TIM_Base_Start(&htim2) != HAL_OK){
    _Error_Handler(__FILE__, __LINE__);
  }
  
  if(HAL_TIM_Base_Start(&htim3) != HAL_OK){
    _Error_Handler(__FILE__, __LINE__);
  }
  
  if(HAL_TIM_Base_Start(&htim4) != HAL_OK){
    _Error_Handler(__FILE__, __LINE__);
  }*/

  //enable_uart_interruptions();
  /*__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
  HAL_UART_Receive_IT(&huart2, (uint8_t *)GPRS_buffer, 1);*/

  /*HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);*/

  /*Battery*/
  //setCapacity(2200);
  /*Files on SD Initialization*/
  /*fr_result = Create_MyData_File();
  if(fr_result == FR_OK || fr_result==FR_EXIST)
  {
    Create_ErrorLog_File();
    Create_BackUp_File();
  }
  else
  {
    TriverPort=uart3;
    printf("SD Memory Initialization Failed, press a key!\r\n");
  }*/

  /*TriverPort=uart3;
  printf("Entrando al loop infinito\r\n");
  while(1)
  {  
    if(timer_event)
    {
      printf("Rock & Roll...\r\n");
      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
      timer = 0;
      timer_event = false;
    }
    //timer++;
  }*/
  
  /*LEDs Initialization*/
  /*HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);*/
  
  /*GPRS Initialization*/
  /*TriverPort = uart2;
  if(GPRS_Begin() == GPRS_FAILED)
  {
    TriverPort=uart3;
    printf("GPRS Initialization Failed!\r\n");
  }
  else
  {
    SendATCmdWaitResp("AT+CSCLK=0\r\n", 500, 50, "OK", 2);
    MQTTpublish();
    //GPRS_Sleep();
    //GPRS_Wakeup();
    FlashData= *(__IO uint32_t *)0x080E0000;
    if(FlashData==0xA6)
    {
      TriverPort=uart3;
      printf("Come back from Skeleton System reset...\r\n");
      TriverPort=uart2;
      EMA_cnfg.tmr_smpl=*(__IO uint32_t *)(0x080E0000+4);
      aurora_system_state=EMA_CORE;
    }
    else if(FlashData==0xB7)
    {
      TriverPort=uart3;
      printf("Come back from System Reset from User interface ...\r\n");
      TriverPort=uart2;
      EMA_cnfg.tmr_smpl=*(__IO uint32_t *)(0x080E0000+4);
      HAL_FLASH_Unlock();
      __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP|FLASH_FLAG_OPERR|FLASH_FLAG_WRPERR|FLASH_FLAG_PGAERR|FLASH_FLAG_PGPERR);
      FLASH_Erase_Sector(FLASH_SECTOR_11, FLASH_VOLTAGE_RANGE_3);
      HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, (uint32_t)0x080E0000, 0x00);
      HAL_FLASH_Lock();
    }
  }*/
  /*if(GPRS_AT()==GPRS_FAILED)
  {
    TriverPort=uart3;
    printf("\r\n");
    printf("First AT Failed...\r\n");
    for(uint8_t counter=0; counter<2; counter++)
    {
      HAL_Delay(6000);
      TriverPort=uart2;
      if(GPRS_AT()==GPRS_FAILED)
      {
        TriverPort=uart3;
	printf("Power Key Attempt %d...\r\n", counter);
	TriverPort=uart2;
 	if(GPRS_PWKEY()==GPRS_FAILED)
	{
	  TriverPort=uart3;
	  printf("Unable to communicate with SIM900...\r\n");
	  TriverPort=uart2;
	}
	else
	{
	  TriverPort=uart3;
	  printf("Success recovering communication with SIM900...\r\n");
	  TriverPort=uart2;
	  counter=4;
	}
      }
      else
      {
	TriverPort=uart3;
	printf("Recovering communication with SIM900...\r\n");
	TriverPort=uart2;
	counter=4;
      }
      HAL_Delay(2000);
    }
  }
  else
  {
    TriverPort=uart3;
    printf("\r\n");
    printf("Success communication with SIM900...\r\n");
    TriverPort=uart2;
  }
  
  TriverPort=uart2;
  Sending_Data_Counter=0;
  SMS_available=false;
  DeleteAllSMS();*/

//  TriverPort=uart3;

  /*State Machine Aurora_System starts its job*/
/*  while (1)
  {
    #ifdef DEBUG_SYSTEM_STATE_MACHINE
    if(last_state!=aurora_system_state)
    {
      print_machine_state = true;
    }
    #endif
    Aurora_System[aurora_system_state](); 
  }
*/
  return 0;
}
