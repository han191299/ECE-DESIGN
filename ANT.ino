// preprocessor directive to the Adafruit header file
#include "Adafruit_VEML7700.h"

// constant integer global variable declarations for pin numbers
const int led = 7;
const int pumpPin = 12;
const int soilSensor = A4;

// constant integer global variable declarations for upper/lower bounds of sensor conditionals
const int tooDry = 270;
const int tooDark = 50;
const int tooBright = 300;

void setup() {
  // initializes each pin to its default state
  pinMode(pumpPin, OUTPUT); 
  pinMode(soilSensor, INPUT);
  pinMode(led, OUTPUT);   
  digitalWrite(pumpPin, HIGH);  

  // wait 0.5 seconds
  delay(500); 

  // waits for the serial port to connect and checks every 0.01 seconds
  while (!Serial) { delay(10); } 

  // sets the serial communication data rate to be 9600 bits per seconds (baud)
  Serial.begin(9600); 

  // Outputs Adafruit VEML7700 Test then checks to see if the sensor is detected under serial communication
  Serial.println("Adafruit VEML7700 Test"); 
  if (!veml.begin()) { 
    // if sensor is not detected, output "Sensor not found"
    Serial.println("Sensor not found"); 
    // creates an endless loop that can only be stopped by resetting the arduino
    while (1); 
  } 
  // if the endless loop is not entered... output "Sensor found"
  Serial.println("Sensor found"); 


  
  // manually sets the default gain value for the light sensor
  // gain is the quantitative variable for how much the value of the data being read (in our case luminosity) will be increased
  veml.setGain(VEML7700_GAIN_1); 

  // manually sets the default integration time value for the light sensor
  // integration time is how long the sensor will collect data for under one instance (more time = more precision)
  veml.setIntegrationTime(VEML7700_IT_800MS); 

  // outputs the gain value and gives a switch statement to allow for manual override of the initial gain value of VEML7700_GAIN_1
  Serial.print(F("Gain: ")); 
  switch (veml.getGain()) { 
    
    case VEML7700_GAIN_1: Serial.println("1"); 
    break; 
    
    case VEML7700_GAIN_2: Serial.println("2"); 
    break; 
    
    case VEML7700_GAIN_1_4: Serial.println("1/4"); 
    break; 
    
    case VEML7700_GAIN_1_8: Serial.println("1/8"); 
    break; 

  } 

  
// outputs the integration time value and gives a switch statement to allow for manual override of the initial integration time value of VEML7700_IT_800MS
  Serial.print(F("Integration Time (ms): ")); 
  switch (veml.getIntegrationTime()) { 

    case VEML7700_IT_25MS: Serial.println("25");
    break; 

    case VEML7700_IT_50MS: Serial.println("50");
    break; 

    case VEML7700_IT_100MS: Serial.println("100");
    break; 

    case VEML7700_IT_200MS: Serial.println("200");
    break; 

    case VEML7700_IT_400MS: Serial.println("400");
    break; 

    case VEML7700_IT_800MS: Serial.println("800");
    break; 

  } 
} 

void loop() {
  // read current moisture 
  int moisture = analogRead(soilSensor); 

  // output moisture level
  Serial.println(moisture); 

  // wait 0.5 seconds
  delay(500); 

   
  // If the moisture level is above the tooDry threshold (high moisture levels = drier soil)
  if (moisture >= tooDry) { 

    // outputs the moisture level and begins watering
    Serial.println("Watering starts now...moisture level is " + String(moisture)); 
    digitalWrite(pumpPin, LOW); 

    // keep watering for 5 sec 
    delay(5000); 

    // turn off water & output the statement "Done watering."
    digitalWrite(pumpPin, HIGH); 
    Serial.println("Done watering."); 

  }

  // If the moisture level is not above the tooDry threshold
  else { 
    
    // outputs the moisture level showing that it is not low enough to begin watering
    Serial.println("Moisture is adequate. No watering needed " + String(moisture)); 

  } 

  

   
  // outputs "Lux: " then the luminosity (lux) value directly after
  Serial.print("Lux: "); 
  Serial.println(veml.readLux()); 

  // if the luminosity is below the lower bound for light (almost complete darkness), turn off and wait 0.2 seconds
  if (veml.readLux() <= tooDark) { 
    digitalWrite(led, LOW); 
    delay(200); 
  } 

  // if the luminosity is in the optimum region of luminosity, turn on the grow light and wait 0.2 seconds
  else if (veml.readLux() > tooDark && veml.readLux() <= tooBright){ 
   digitalWrite(led, HIGH); 
   delay(200); 
  } 

  // this acts as a catchall for any other situation (namely the situation where too much light is being received by the sensor) and turns off the grow light
  else{ 
    digitalWrite(led, LOW); 
  } 

  wait 0.5 seconds before looping again
  delay(500); 
  } 
}
