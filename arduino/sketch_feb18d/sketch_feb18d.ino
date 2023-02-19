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

double arrUS1[10];
double arrIR1[10];
bool firstten = true;
int counter = 0;
double sum;

void setup(){
    Serial.begin(9600);
}



void loop() {

  double distance1 = 0;
  double distance2 = 0;

  double l_us = (double)us1.distanceInMillimeters()/1000;
  double l_ir = (double)sharp1.getDist()/100;
  
  

  
  
  if(counter < 10){
    if(!firstten){
      sum -= arrUS1[counter] + arrIR1[counter];  
    }
    arrIR1[counter] = l_us;
    arrUS1[counter] = l_ir;
    counter++;
  }
  else{
    counter = 0;
    firstten = false;
  }

  sum += arrUS1[counter] + arrIR1[counter];


  if (l_us > 1.5 && l_ir < 2.2) {
    distance1 = sum/20;
  }
  else if(l_us < 1.5){
    distance1 = l_us;
  }
  else if(l_ir > 2.2){
    distance1 = l_ir;
  }

  

  Serial.print("US1: ");
  Serial.print(arrUS1[counter]);
  Serial.print(" IR1: ");
  Serial.print(arrIR1[counter]);
  Serial.print(" D: ");
  Serial.println(distance1);



  // Wait some time    
  delay(50);

}