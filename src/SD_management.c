#include "SD_management.h"
#include "stm32f4xx_hal.h"

extern RTC_HandleTypeDef hrtc;


	FATFS myFAT;
	FIL myFile;
	char filenamebuffer[255];
	uint8_t myfilenumber=0;
	//uint8_t myData[11]= "Triverlogic";
	//uint8_t header[]="WindSpeed,WindVane,RainGauge,Temperature[0],Temperature[1],Temperature[2],Temperature[3],Pressure[0],Pressure[1],Pressure[2],Pressure[3],Humidity[0],Humidity[1],Humidity[2],Humidity[3],Lux[0],Lux[1],Soil_Moisture,Vdd,State-of-Charge[%], Battery_Voltage[mV], Average_Current[mA], Full_Capacity[mAh], Remaining_Capacity[mAh], Average_Power_Draw[mW], State_of_Health[%],Time\n";
	uint8_t header[]="WindSpeed,WindVane,RainGauge,Temperature[0],Temperature[1],Pressure[0],Pressure[1],Humidity[0],Humidity[1],Lux[0],Lux[1],Soil_Moisture,Vdd,Time\n";
	uint8_t errorheader[]="Data logger errors from Aurora Station:\r\n";
	UINT byteCount;
	FRESULT myresult;

FRESULT Create_MyData_File(void)
{
	myresult=FR_OK;

	myresult=f_mount(&myFAT, SD_Path, 1);
	if(myresult==FR_OK)
	{
		//myresult = f_open(&myFile, "EMADATA.csv", FA_WRITE|FA_CREATE_ALWAYS);
		myresult = f_open(&myFile, "EMADATA.csv", FA_WRITE|FA_CREATE_NEW);
		if(myresult==FR_OK)
		{
		f_write(&myFile, header, sizeof(header), &byteCount);
		f_close(&myFile);
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
		}
		else if(myresult==FR_EXIST)
		{

		}
	}
	return myresult;
}

void Adding_MyData_File(char *SDbuffer, uint8_t lenght)
{
	unsigned long result;
	myresult=FR_OK;
	myresult=f_mount(&myFAT, SD_Path, 1);
	if(myresult==FR_OK)
	{
		

		f_open(&myFile, "EMADATA.csv", FA_READ|FA_WRITE);
		result=f_size(&myFile);
		if(result<10000)
		{
			f_lseek(&myFile, f_size(&myFile));

			f_write(&myFile, SDbuffer, lenght, &byteCount);
			f_close(&myFile);

		}
		else
		{
			myfilenumber++;
			f_close(&myFile);

			sprintf(filenamebuffer, "File%d.csv", myfilenumber);
			myresult=f_rename("EMADATA.csv", filenamebuffer);

			Create_MyData_File();
			f_open(&myFile, "EMADATA.csv", FA_READ|FA_WRITE);
			f_lseek(&myFile, f_size(&myFile));
			f_write(&myFile, SDbuffer, lenght, &byteCount);
			f_close(&myFile);


		}

		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
		
	}
}

void Create_ErrorLog_File(void)
{

	myresult=FR_OK;

	myresult=f_mount(&myFAT, SD_Path, 1);
	if(myresult==FR_OK)
	{
		myresult=f_open(&myFile, "ERRORLOG.txt", FA_WRITE|FA_CREATE_NEW);
		if(myresult==FR_OK)
		{
			//f_write(&myFile, errorheader, sizeof(errorheader), &byteCount);
			f_puts("Data logger errors from Aurora Station:\r\n", &myFile);
			f_close(&myFile);
		}
		else if(myresult==FR_EXIST)
		{

		}

	}
}

void Adding_ErrorLog_File(char *SDbuffer, uint8_t lenght)
{
	RTC_TimeTypeDef mytime;
	RTC_DateTypeDef mydate;

	HAL_RTC_GetTime(&hrtc, &mytime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &mydate, RTC_FORMAT_BIN);

	myresult=FR_OK;
	myresult=f_mount(&myFAT, SD_Path, 1);
	if(myresult==FR_OK)
	{

		f_open(&myFile, "ERRORLOG.txt", FA_READ|FA_WRITE);
		f_lseek(&myFile, f_size(&myFile));

		f_printf(&myFile, "%s Time:%02d:%02d:%02d Date: %02d/%02d/%02d\r\n", SDbuffer, mytime.Hours, mytime.Minutes, mytime.Seconds,
				mydate.Month, mydate.Date, mydate.Year);
		f_close(&myFile);
	}

}

void Create_BackUp_File(void)
{
	myresult=FR_OK;

	myresult=f_mount(&myFAT, SD_Path, 1);
	if(myresult==FR_OK)
	{
		myresult = f_open(&myFile, "BACKUP.csv", FA_WRITE|FA_CREATE_NEW);
		if(myresult==FR_OK)
		{
			f_write(&myFile, header, sizeof(header), &byteCount);
			f_close(&myFile);
		}
		else if(myresult==FR_EXIST)
		{

		}
	}
}

void Adding_BackUp_File(char *SDbuffer, uint8_t lenght)
{
	//unsigned long result;
	myresult=FR_OK;
	myresult=f_mount(&myFAT, SD_Path, 1);
	if(myresult==FR_OK)
	{

		f_open(&myFile, "BACKUP.csv", FA_READ|FA_WRITE);
//		result=f_size(&myFile);

			f_lseek(&myFile, f_size(&myFile));

			f_write(&myFile, SDbuffer, lenght, &byteCount);
			f_close(&myFile);

	}
}
