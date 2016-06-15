#include <LiquidCrystal.h>

// Global variables:
// LCD variables
LiquidCrystal lcd (8, 9, 4, 5, 6, 7);
//Custom degree character
byte degree[8] = {  B00110,  B01001,  B01001,  B00110,  B00000,  B00000,  B00000,  B00000, };
/*
LM35
 U
GO5
Top View
*/
//Start the time at 0
int temperatureSensorPin = A15;
long timer = millis();
char message[] = "Temperature:    ";

int pin = 48; // connected to the Trig on the module, this serves as both Trigger and Echo
unsigned long time;
unsigned long sizeofpulse;
float cm;

void setup() {
  setup_serial();
  setup_LCD();
  setup_SDM_IO();
}

void loop() {
  
  //Move cursor to second line, first position  
  //lcd.setCursor(0,1);  

  if( millis() - timer > 5000 ) {
      
      float tempCelcius = convertSensorTemperatureToCelsius();
      float tempKelvin = tempCelcius + 273.15;

      //write temperature on LCD
      writeTemperatureCelsiusToLCD(tempCelcius);
      //printLine(1);
      timer = millis();
      
  }

  ultrasound_distance();
  
  //Wait 1 second 
  delay(1000);
}

//calculates temperature for temperature sensor reading
float convertSensorTemperatureToCelsius()
{
      int val = analogRead( temperatureSensorPin );
      float tempCelsius = val * 0.48828125;
      Serial.print("Val: "); Serial.println(val);
      Serial.print("Temperature: "); Serial.print(tempCelsius); Serial.println(" C");

      return tempCelsius;
}

//writes temperature in celsius degrees to LCD screen at the beginning of the second row
void writeTemperatureCelsiusToLCD(float temperature)
{
  //Move cursor to first line, position 9
  lcd.setCursor(9,0); 
  //Print current temperature to 2 decimal places
  lcd.print(temperature, 2);
  lcd.home();
  int temperatureInt = (int) (temperature+0.5);
  byte temp = (byte)temperatureInt;
  Serial.print("Temperature: "); Serial.print(temp); Serial.println(" C");
  char tempValue = temp;
  //String toSend = "A" + tempValue;
  Serial.println("A" + tempValue);
  Serial1.print( "A" );
  Serial1.print( tempValue );
}

void setup_LCD() 
{
  //setup lcd
  lcd.begin(16, 2);
  
  //Make custom characters
  lcd.createChar(0, degree); 

  //First row print
  lcd.setCursor(0,0);
  lcd.print("Temper.:");
  lcd.setCursor(14,0); lcd.write((byte)0);
  lcd.setCursor(15,0); lcd.print("C");
  //Second row print
  lcd.setCursor(0,1);
  lcd.print("Distan.: ");
  lcd.setCursor(14,1); lcd.print("cm");
}

void setup_serial() 
{
  Serial.begin(9600);
  Serial1.begin(9600);
}

void setup_SDM_IO()
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH); // Trig pin is normally HIGH
}

void ultrasound_distance()
{
  pinMode(pin, OUTPUT); //return digital pin to OUTPUT mode after reading
  digitalWrite(pin, LOW);
  delayMicroseconds(25);
  digitalWrite(pin, HIGH); //Trig pin pulsed LOW for 25usec
  time = micros(); //record timer
  pinMode(pin, INPUT); //change pin to INPUT to read the echo pulse
  sizeofpulse = pulseIn(pin, LOW, 18000); //should be approx 150usec, timeout at 18msec
  time = micros() - time - sizeofpulse; // amount of time elapsed since we sent the trigger pulse and detect the echo pulse, then subtract the size of the echo pulse
  cm=(time*340.29/2/10000)-3; // convert to distance in centimeters
  Serial.println("SDM-IO:;");
  Serial.print(cm); Serial.println("cm;");
  lcd.setCursor(8,1);
  lcd.print(cm, 2);
  lcd.home();
  //byte distanceValue = floatToByte(cm);
  //Serial.println("B" + distanceValue);
  //Serial1.print( "B" );
  //Serial1.print( distanceValue );
  pinMode(pin, OUTPUT);
}

byte floatToByte(float value) {
  int valueInt = (int) (value+0.5);
  byte valueByte = (byte) valueInt;
}
