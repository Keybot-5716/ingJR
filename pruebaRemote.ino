/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.13 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.13.13 or later version;
     - for iOS 1.10.3 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG    

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__SOFTSERIAL

#include <SoftwareSerial.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 8
#define REMOTEXY_SERIAL_TX 9
#define REMOTEXY_SERIAL_SPEED 9600


#include <RemoteXY.h>
// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 60 bytes
  { 255,3,0,0,0,53,0,17,0,0,0,31,1,106,200,1,1,3,0,5,
  20,52,60,60,21,2,26,31,10,41,145,24,24,48,6,26,31,79,78,0,
  31,79,70,70,0,129,23,173,56,12,6,65,117,116,111,110,111,109,111,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t joystick_01_x; // from -100 to 100
  int8_t joystick_01_y; // from -100 to 100
  uint8_t pushSwitch_01; // =1 if state is ON, else =0

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

/* defined the right motor control pins */
#define PIN_MOTOR_RIGHT_UP 4
#define PIN_MOTOR_RIGHT_DN 5
#define PIN_MOTOR_RIGHT_SPEED 10

/* defined the left motor control pins */
#define PIN_MOTOR_LEFT_UP 6
#define PIN_MOTOR_LEFT_DN 7
#define PIN_MOTOR_LEFT_SPEED 9

/* defined the LED pin */
#define PIN_LED 13

/* defined two arrays with a list of pins for each motor */
unsigned char RightMotor[3] = 
  {PIN_MOTOR_RIGHT_UP, PIN_MOTOR_RIGHT_DN, PIN_MOTOR_RIGHT_SPEED};
unsigned char LeftMotor[3] = 
  {PIN_MOTOR_LEFT_UP, PIN_MOTOR_LEFT_DN, PIN_MOTOR_LEFT_SPEED};

void setup() 
{

  /* initialization pins */
  pinMode (PIN_MOTOR_RIGHT_UP, OUTPUT);
  pinMode (PIN_MOTOR_RIGHT_DN, OUTPUT);
  pinMode (PIN_MOTOR_LEFT_UP, OUTPUT);
  pinMode (PIN_MOTOR_LEFT_DN, OUTPUT);
  pinMode (PIN_LED, OUTPUT);
  
  RemoteXY_Init (); 
  
  
  // TODO you setup code
  
}

void loop() 
{ 
  int apagaTeleop = 0;
  RemoteXY_Handler ();
  
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay(), use instead RemoteXY_delay() 
  if (RemoteXY.pushSwitch_01 == 1) {
      // Modo autónomo
        digitalWrite (PIN_LED, HIGH);

      // En caso de que se haya quedado prendido lo apaga he inicia la rutina auto
      if (apagaTeleop) {
        apagaTeleop = 0;
        RemoteXY.joystick_01_x = 0;
        RemoteXY.joystick_01_y = 0;      
      }
      
  }
  else {
      // Modo teleoperado
        apagaTeleop = 1;
      
        /* manage LED pin */
        digitalWrite (PIN_LED, HIGH);
        delay(100);
        digitalWrite (PIN_LED, LOW);
        delay(100);
      
        Wheel(RightMotor,  RemoteXY.joystick_01_x - RemoteXY.joystick_01_y);
        Wheel(LeftMotor, RemoteXY.joystick_01_x + RemoteXY.joystick_01_y );
  }

}



/*
   speed control of the motor
   motor - pointer to an array of pins
   v - motor speed can be set from -100 to 100
*/
void Wheel (unsigned char * motor, int v)
{
  if (v>100) v=100;
  if (v<-100) v=-100;
  if (v>0) {
    digitalWrite(motor[0], LOW);
    digitalWrite(motor[1], HIGH);
    analogWrite(motor[2], v*2.55);
  }
  else if (v<0) {
    digitalWrite(motor[0], HIGH);
    digitalWrite(motor[1], LOW);
    analogWrite(motor[2], (-v)*2.55);
  }
  else {
    digitalWrite(motor[0], LOW);
    digitalWrite(motor[1], LOW);
    analogWrite(motor[2], 0);
  }
}
