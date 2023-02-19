#include <hcsr04.h>
#include <SharpDistSensor.h>

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



void loop() {

  double distance1 = 0;
  double distance2 = 0;

  double l_us = (double)us1.distanceInMillimeters()/1000;
  double l_ir = (double)sharp1.getDist()/100;


  double r_us = (double)us2.distanceInMillimeters()/1000;
  double r_ir = (double)sharp2.getDist()/100;
  
  
  if (l_us > 1.5 && l_ir < 2.2) {
    distance1 = (l_us + l_ir)/2;
  }
  else if(l_us < 1.5){
    distance1 = l_us;
  }
  else if(l_ir > 2.2){
    distance1 = l_ir;
  }

  if (r_us > 1.5 && r_ir < 2.2) {
    distance2 = (r_us + r_ir)/2;
  }
  else if(r_us < 1.5){
    distance2 = r_us;
  }
  else if(r_ir > 2.2){
    distance2 = r_ir;
  }

  

  Serial.print("US1: ");
  Serial.print(r_us);
  Serial.print(" IR1: ");
  Serial.print(r_ir);
  Serial.print(" D: ");
  Serial.println(distance2);



  // Wait some time    
  delay(50);

}