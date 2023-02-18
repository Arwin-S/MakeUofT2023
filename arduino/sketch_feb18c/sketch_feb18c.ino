#include <hcsr04.h>

#define TRIG_PIN1 10
#define ECHO_PIN1 9
#define TRIG_PIN2 12
#define ECHO_PIN2 11

HCSR04 source1(TRIG_PIN1, ECHO_PIN1, 20, 4000);


HCSR04 source2(TRIG_PIN2, ECHO_PIN2, 20, 4000);

void setup(){
    Serial.begin(9600);
}

void loop() {

    // Output the distance in mm
	Serial.print("US 1: ");
  Serial.print(source1.distanceInMillimeters());
  
  Serial.print(" US 2: ");
  Serial.println(source2.distanceInMillimeters());

    // Output information about the device, driver, and distance in Bifrost JSON format
    //Serial.println(hcsr04.ToString());
    delay(100);

}