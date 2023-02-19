#include <hcsr04.h>
#include <SharpDistSensor.h>
#include "string.h"
#include <SD.h>

using namespace std; 

//Pins for IR Sensors
const byte sharpPin1 = A0;
const byte sharpPin2 = A1;

// Window size of the median filter (odd number, 1 = no filtering)
const byte medianFilterWindowSize = 5;

//Pins for Ultra Sound Sensors
#define TRIG_PIN1 10
#define ECHO_PIN1 9
#define TRIG_PIN2 12
#define ECHO_PIN2 11

//Instances of SharpDistSensor Class
SharpDistSensor sharp1(sharpPin1, medianFilterWindowSize);
SharpDistSensor sharp2(sharpPin2, medianFilterWindowSize);


//Instances of Ultrasound Sensor Class
HCSR04 us1(TRIG_PIN1, ECHO_PIN1, 20, 4000);
HCSR04 us2(TRIG_PIN2, ECHO_PIN2, 20, 4000);



void setup(){
    Serial.begin(9600);
}

double sum;
int counter = 0;

double ir[20];
double us[20];

double average;


void loop() {

  double distance1 = 0;
  double distance2 = 0;

  double l_us = (double)us1.distanceInMillimeters()/1000;
  double l_ir = (double)sharp1.getDist()/100;


  double r_us = (double)us2.distanceInMillimeters()/1000;
  double r_ir = (double)sharp2.getDist()/100;

  int l_vol;
  int r_vol;
  
  if(counter < 10){
    ir[counter] = l_ir;
    us[counter] = l_us;
    sum += ir[counter] + us[counter];
    counter++;
  }
  else{
    average = sum/20;
    sum = 0;
    counter = 0;
    if (l_us > 1.5 && l_us < 2.2) {
      distance1 = average;
      l_vol = (distance1 * -25) + 125;
    }
    else if(l_us < 1.5){
      distance1 = l_us;
      l_vol = 100;
    }
    else if(l_ir > 2.2){
      distance1 = l_ir;
      l_vol = (distance1 * -25) + 125;
    }

    if (r_us > 1.5 && r_us < 2.2) {
      distance2 = (r_us + r_ir)/2;
      r_vol = (distance2 * -25) + 125;

    }
    else if(r_us < 1.5){
      distance2 = r_us;
      r_vol = 100;

    }
    else if(r_ir > 2.2){
      distance2 = r_ir;
      r_vol = (distance2   * -25) + 125;

    }

    String leftvol;
    String rightvol;
/*
    if(l_vol < 100 & l_vol > 10){
      leftvol = '0' + (String)((int)l_vol);
    }
    else if(l_vol < 10 && l_vol > 0){
      leftvol = '0' + '0' + (String)((int)l_vol);
    }
    else{
      leftvol = '000';
    }
    if(r_vol < 100 & r_vol > 10){
      rightvol = '0' + (String)((int)r_vol);
    }
    else if(r_vol < 10 && r_vol > 0){
      rightvol = '0' +'0' + (String)((int)r_vol);
    }
    else{
      rightvol = '000';
    }
*/
    // String l0 = "";
    // String r0 = "";
    // int l = l_vol;
    // int r = r_vol;

    // for (int i = 0; i < 1; i++)
    // {
    //     if (l / 10 < 10)
    //     {
    //         l0 += '0';
    //         l/=10;
    //     }
    //     if (r / 10 < 10)
    //     {
    //         r0 += '0';
    //         r/=10;
    //     }
    // }

    //File file;
    

    String send = String(l_vol) + " " +String(r_vol);
    
    // Serial.print("US1: ");
    Serial.println(send);
   // Serial.write(13);
    //Serial.write(10);
    // Serial.print(" IR1: ");
    // Serial.print(l_ir);
    // Serial.print(" D: ");
    // Serial.println(distance1);
  }
  


  

  

  



  // Wait some time    
  delay(0);

}