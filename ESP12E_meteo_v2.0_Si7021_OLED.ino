
/**
 * NodeMCU (ESP12E) + Si7021 + 128x64px OLED
 *
 * made by Petus (2017)
 * https://chiptron.cz/articles.php?article_id=113
 * https://time4ee.com/articles.php?article_id=48
 *
 * Si7021 library - https://github.com/LowPowerLab/SI7021
 * 128x64px OLED display - http://www.adafruit.com/category/63_98
 * Add to Arduino IDE "Adafruit GFX Library" and "Adafruit SSD1306" library
 */

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SI7021.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SDA 4 // GPIO4 on D2
#define SCL 5 // GPIO5 on D1

#define OLED_RESET 19 //choose unused pin, connect the RESET pin to VCC (3.3V)
Adafruit_SSD1306 display(OLED_RESET);

SI7021 sensor;

void setup() {
  
  Serial.begin(9600); // Open serial connection to report values to host
  delay(10);

  sensor.begin(SDA,SCL);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  delay(2000);
  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("chiptron.cz");
  display.setCursor(0,10);
  display.println("time4ee.com");
  display.setCursor(0,20);
  display.println("Meteostation board");
  display.display();
  delay(2000);
  display.clearDisplay();

  display.setTextSize(2);

}


void loop() {
  int temperature = sensor.getCelsiusHundredths();
  unsigned int humidity = sensor.getHumidityPercent();

  Serial.println("Temperature: ");
  Serial.print(String(temperature/100.0, 2));
  Serial.println(" °C");
  Serial.println("Humidity: ");
  Serial.println(humidity);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(String(temperature/100.0, 2));
  display.println(" 'C");
  display.setCursor(0, 15);
  display.print(humidity);
  display.println(" %");
  display.display();
  
  delay(10000);
  
}
