/**
* @file inclusions.h
* 
* @brief Inclusions diverses 
* @details 
  - 
*/ 

#ifndef __INCLUSIONS_H__
#define __INCLUSIONS_H__

#define PIN_BUTTONS 2
#define PIN_LED 4
#define PIN_SENSOR 1

//#define BOUNCES_DELAY 100000 //Anti-rebonds

/*** Gestion du timer ***/
// Select USING_16MHZ     == true for  16MHz to Timer TCBx => shorter timer, but better accuracy
// Select USING_8MHZ      == true for   8MHz to Timer TCBx => shorter timer, but better accuracy
// Select USING_250KHZ    == true for 250KHz to Timer TCBx => shorter timer, but better accuracy
// Not select for default 250KHz to Timer TCBx => longer timer,  but worse accuracy
#define USING_16MHZ     true
#define USING_8MHZ      false
#define USING_250KHZ    false

// Select the timers you're using, here ITimer1
#define USE_TIMER_0     false
#define USE_TIMER_1     true
#define USE_TIMER_2     false
#define USE_TIMER_3     false
/********************************/


#include <math.h>
#include "megaAVR_TimerInterrupt.h"
#include "lcdscreen.h"
#include "button.h"
#include "tempsensor.h"
#include "setpoint.h"
#include "control.h"



#endif
