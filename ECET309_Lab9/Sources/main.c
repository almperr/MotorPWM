//Name: Alexander Perr
//Class:ECET 309
//Assignment:Lab 9 - Task Scheduler  
//Date:3/20/2018
//File Description: This file is the main function

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "protos.h"


void main(void) 
{
  /* put your own code here */
  initIO();                          //calls initialization function
  initECTInterrupts();               //initiates the Enhanced Capture Timers 

  for(;;) 
  {
    RunTaskSched();                  //runs task scheduler
  } /* loop forever */
  /* please make sure that you never leave main */
}
