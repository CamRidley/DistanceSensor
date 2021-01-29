// 
// CPA 20210129
// Distance measurement by ultrasonic trasducer and display on i2c LCD diplay.
// 
// Wiring (for Arduino Uno): 
// LCD display: SDA to pin A4, SCL to pin A5
// Ultransonic sensor: Trig to pin 12, Echo to pin 11
//   

#include <NewPing.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

  lcd.init();                      // initialize the lcd 
//  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Distance Sensor");
  
}

void loop() {
  delay(250);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  unsigned int DIST = uS / US_ROUNDTRIP_CM;
  Serial.print(DIST); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  lcd.setCursor(0,1);
  lcd.print("Distance: ");
  lcd.print(DIST);
  lcd.print(" cm   ");
  }
