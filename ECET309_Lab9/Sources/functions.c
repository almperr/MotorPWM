//Name: Alexander Perr
//Class:ECET 309
//Assignment:Lab 9 - Taskscheduler 
//Date:3/20/2018
//File Description: Contains the functions used to create the Task Scheduler, checks the dipswitches, and runs the stepper motor depending on set speed

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "protos.h"          //includes the protos.h file

volatile long Global_msDelay=16000;        //variable created for the task that needs to be completed the fastest
volatile int faster_msDelay=0;             //variable for the fastest blinking LED. Blinks at 0.1 seconds.
volatile int fast_msDelay=0;               //variable for the slightly less fast blinking LED. Blinks at 0.2 seconds.
volatile int slow_msDelay=0;               //variable for the slowest blinking light. Blinks every 2 seconds.
volatile int speed;                        //variable that is used activate either fast speed or slow speed for the motor
volatile int checkSpeed=0;                 //variable that is used to check the speed switch every 5 seconds
volatile int runMotor=0;


void initIO(void)                          //initializes DDRs
{
 DDRC=0xff;                                //enables LED DDR to be outputs
 DDRB=0x00;                                //enables dipswitch DDR to be inputs
 DDRP=0x01;                                //enables bit 0 of the DC motor DDR to be an output
}

void RunTaskSched(void)                    //declares function for a Task Scheduler 
{
   if(faster_msDelay>0)                    //this will turn LED0 on and off at the time specified in the ECT handler. Constantly being turned off and on. 
   {
      faster_msDelay--;
      ToggleLED0();
   }
   
   if(fast_msDelay>0)                      //this will turn LED1 on and off at the time specified in the ECT handler. Constantly being turned off and on. 
   {
      fast_msDelay--;
      ToggleLED1();
   }
   
   if(slow_msDelay>0)                      //this will turn LED2 on and off at the time specified in the ECT handler. Constantly being turned off and on. 
   {
      slow_msDelay--;
      ToggleLED2();
   }
   
   //motor
   
   if(checkSpeed>0)                        //this will check the switch state every 5 seconds, specified in the ECT handler.   
   {
      checkSpeed--;
      CheckSwitch();
   }
   
   if(runMotor>0)                          //will activate the motor off and on, where it the motor gets activated off and on. 
   {
      runMotor--;
      MotorPWM(); 
   }
      
   
}

void MotorPWM(void)                       //used in the task scheduler to be able to determine the duty cycle of the motor signal. 
{
   static int motorCount;                 //used as a counter to count a number of cycles
   motorCount++;                          //increases the integer value of motorCount by 1
   
   if((speed) && (motorCount < 9))        //duty cycle 90%  for fast speed
   {
      PTP |= 0x01;                        //activates bit 0 of the motor 
   }
   else if((!speed) && (motorCount<3))    //duty cycle 30%. for slow speed
   {
      PTP |= 0x01;
   }
   else
   {
      PTP &= ~0x01;                        //turns motor off
   }
   
   if(motorCount > 10)                     //resets motorCount after the motorCount has reached 10
   {
      motorCount = 0;
   }
   
}

void ToggleLED0(void)                      //toggles LED0
{
   PORTC ^= 0x01;
}

void ToggleLED1(void)                      //toggles LED1
{
   PORTC ^= 0x02;
}

void ToggleLED2(void)                      //toggles LED2
{
   PORTC ^= 0x04;
}

void CheckSwitch(void)                     //function that checks the switch state and sets Speed to either a 1 or a 0 
{
   if(PORTB & 0x01)
   {
      speed = 1;
   }
   else
   {
      speed = 0;
   }
}


      