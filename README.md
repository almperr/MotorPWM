# MotorPWM
### Overview
This is C code used to create a PWM drive for a brushless DC motor. This project demonstrates the use of an Enhanced Capture Timer handler in a Task Scheduler to create a PWM drive. A motor is controlled using dipswitches. One switch turns the motor on and off. A second switch changes speed from slow to fast. Signals being sent to the stepper motor are being sent to different coils in the motor in a sequence. This code was created using Code Warrior IDE. This was a project for ECET 309, Advanced Embedded Micro-Controllers.

### Hardware

**NXP MC9S12XEP100 Dev Kit** - This dev kit includes the MC9S12XEP100 Micro-Controller, JTAG debugger and stepper motor on a single board

<img src="images/stepmotor.jpg" width="500">

### Files of Intrest

**ECET309_Lab9/Sources/ECT.c** - contains functions to set up enhanced capture timer 

**ECET309_Lab9/Sources/main.c** - initiallizes the micro-controller, then a task scheduler runs operation with ECT 

**ECET309_Lab9/Sources/functions.c** - contains the functions used to create the Task Scheduler, checks the dipswitches, and runs the stepper motor depending on set speed

**ECET309_Lab9/protos.h** - contains function prototypes

  
