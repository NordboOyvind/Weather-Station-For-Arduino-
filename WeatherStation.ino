//Interface the DHT11 Temp & Humidity sensor and display humidity and  temperature
//in Celsius on a 16x2 character LCD

//52 temp
//SDA 20
//SCA 21

#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 31     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // Start serial communication
  Serial.begin(9600);

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Read temperature and humidity from DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Print temperature and humidity to serial monitor
  Serial.print(F("Temperature: "));
  Serial.print(temperature);
  Serial.print(F(" °C\t"));
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.println(F("%"));

  // Print temperature to the first line of the LCD
  lcd.setCursor(0, 0);
  lcd.print(F("Temp: "));
  lcd.print(temperature);
  lcd.print(F(" C"));

  // Print humidity to the second line of the LCD
  lcd.setCursor(0, 1);
  lcd.print(F("Hum: "));
  lcd.print(humidity);
  lcd.print(F("%"));
}

