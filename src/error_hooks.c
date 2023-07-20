
#include "error_hooks.h"
#include "FreeRTOSConfig.h" //for configCAL_FACTOR

//************************************************************************
// global variables


//************************************************************************


// set the error led to use by the rtos
void vSetErrorLed(uint8_t pin, uint8_t activeState)
{

}


// set the error serial port for debugging asserts and crashes
void vSetErrorSerial()
{

}


//************************************************************************


// remove a linux or windows path from the file name
const char* removePath(const char* path)
{
	 const char* lastname = path;
	 for (const char* p=path; *p; ++p)
	 {
		if ( (*p == '/' || *p == '\\') && *(p+1) )
		{
			lastname = p+1;
		}

	 }
	 return lastname;
}

//************************************************************************

//called on fatal error (interrupts disabled already)
void rtosFatalError(void)
{
	taskDISABLE_INTERRUPTS();

	while (1)
	{
		errorBlink(3);
	}

}

// fatal error print out what file assert failed
void rtosFatalErrorSerial(unsigned long ulLine, const char *pcFileName)
{

	// proceed the same as other fatal rtos error
	rtosFatalError();
}

void rtosFatalErrorSerialPrint(unsigned long ulLine, const char *pcFileName, uint8_t valueA, const char* evaluation, uint8_t valueB)
{


	// proceed the same as other fatal rtos error
	rtosFatalError();
}

// called on full heap or malloc failure
void vApplicationMallocFailedHook(void) 
{


  
	while (1)
	{
		errorBlink(1);
	}
}

// called on full stack
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{


	while (1)
	{
		errorBlink(2);
	}
}

//************************************************************************


// blink an error code out the default led when the rtos has crashed
void errorBlink(int errorNumber)
{

}

// will delay the processors using nops
// this is used when the rtos has crashed and we cannot use more advanced timing
// assert will cause interrupts to be disabled and delay() to fail, but this will work
// note this function does not play nice with interrupts apparently, this does not replace delay() which is more interrupt friendly
void vNopDelayMS(unsigned long millis) 
{
  unsigned long iterations = millis * configCAL_FACTOR;
  unsigned long i;
  for(i = 0; i < iterations; ++i) 
  {
    asm volatile("nop\n\t");
  }
}

//************************************************************************
