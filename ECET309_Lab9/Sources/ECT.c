//Name: Alexander Perr
//Class:ECET 309
//Assignment:Lab 9 - Task Scheduler  
//Date:3/20/2018
//File Description: This file is the Enhanced Capture Timer file. 
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "protos.h"          //includes the protos.h file

#define ENABLE_INT asm cli          //global variable that will allow interrupt to be enabled. Written in assembly language

extern volatile long Global_msDelay;    //variable created for the task that needs to be completed the fastest 
extern volatile int faster_msDelay;     //variable for the fastest blinking LED. Blinks at 0.1 seconds. Gets externed to the functions file.
extern volatile int fast_msDelay;       //variable for the slightly less fast blinking LED. Blinks at 0.2 seconds. Gets externed to the functions file 
extern volatile int slow_msDelay;       //variable for the slowest blinking light. Blinks every 2 seconds. Gets externed to the functions file 
extern volatile int checkSpeed;         //variable that is used to check the speed switch every 5 seconds
extern volatile int runMotor;           //variable that is used to run the motor. 


void initECTInterrupts(void)                   //function that initializes all of the neccessary registers in order to enable the Enhanced Capture Timer
{
   ENABLE_INT;                                 //allows for interupts to be Enabled. 
   ECT_TIOS_IOS1 = 1;                          //sets bit 1 of the Timer Input/Output register select to a one. This configures the register to be an output capture.
   ECT_TC1 = ECT_TCNT + Global_msDelay;        //loads Timer Capture and Compare register with a Timer Counter with addition of the Global Delay.
   ECT_TIE_C1I = 1;                            //this activates bit 1 of the Timer Mask register. 
   ECT_TFLG1_C1F = 1;                          //clears the flag at bit 1 of the Timer Flag Register.
   ECT_TSCR1_TEN=1;                            //enables bit 7 of the Timer System Control register. This bit enables the timers. 
}

void interrupt ECTOutCompHandler(void)         //this function is the ECT output handler function. Gets called in the Project.prm file
{
 
 static int interruptCount = 0;                //this is variable that is used for a global timer 
 
 ECT_TFLG1_C1F = 1;                            //clears the flag at bit 1 of the Timer Flag Register
 ECT_TC1 = ECT_TCNT + Global_msDelay;          //loads Timer Capture and Compare register with a Timer Counter with addition of the Global Delay.
 
 if((interruptCount % 50)==0)                  //this increases the faster_msDelay variable by 1 every 50 cycles
 {
   faster_msDelay++;                           //increases faster_msDelay
 }
 
 if((interruptCount % 125)==0)                 //increases fast_msDelay every 125 cycles
 {
   fast_msDelay++;                             //increases fast_msDelay
 }
 
 if((interruptCount % 1000)==0)                //increases slow_msDelay every 1000 cycles
 {
   slow_msDelay++; 
 }
 
 //Motor Tasks
 
 if((interruptCount % 2500)==0)                //this will be used to check the speed every 5 seconds 
 {
   checkSpeed++;
 }
 
 if((interruptCount % 1)==0)                   //this will activate run motor every cycle. This will help generate the pulse for the motor. 
 {
   runMotor++;
 }
                                               //increases interruptCount++
 interruptCount++;
 
}

