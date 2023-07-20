
#include "runTimeStats_hooks.h"
#include <sam.h>
//************************************************************************

// setup the hardware timer to use as a counter
void vMainConfigureTimerForRunTimeStats( void )
{
	// do nothing, will use the arduino systick timer
	// can change this if you want
    ;
}

static int ticks = -1;
/** Tick Counter united by ms */
static volatile uint32_t _ulTickCount=0 ;
unsigned long micros( void )
{
    uint32_t ticks, ticks2;
    uint32_t pend, pend2;
    uint32_t count, count2;

    ticks2  = SysTick->VAL;
    pend2   = !!(SCB->ICSR & SCB_ICSR_PENDSTSET_Msk)  ;
    count2  = _ulTickCount ;

    do
    {
        ticks=ticks2;
        pend=pend2;
        count=count2;
        ticks2  = SysTick->VAL;
        pend2   = !!(SCB->ICSR & SCB_ICSR_PENDSTSET_Msk)  ;
        count2  = _ulTickCount ;
    } while ((pend != pend2) || (count != count2) || (ticks < ticks2));

    return ((count+pend) * 1000) + (((SysTick->LOAD  - ticks)*(1048576/(48000000/1000000)))>>20) ;
    // this is an optimization to turn a runtime division into two compile-time divisions and
    // a runtime multiplication and shift, saving a few cycles
}

// will return the counter value to generate run time stats
unsigned long ulMainGetRunTimeCounterValue( void )
{
  return micros(); //use already setup arduino systick timer
}


void tickReset() {
    if (ticks == -1)
        return;
    ticks--;
    if (ticks == 0)
        return;
}

void SysTick_DefaultHandler(void)
{
    // Increment tick count each ms
    _ulTickCount++;
    tickReset();
}

//************************************************************************

