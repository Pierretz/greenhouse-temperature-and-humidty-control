/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  Attention! Please check out TinyGSM guide:
    https://tiny.cc/tinygsm-readme

  Change GPRS apn, user, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!

 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL2J0YIn1v5"
#define BLYNK_TEMPLATE_NAME "Green house control"
#define BLYNK_AUTH_TOKEN "MK_n3lNEao8g8FClb0y8M5YtLbgppAIJ"

// Select your modem:
#define TINY_GSM_MODEM_SIM800
//#define TINY_GSM_MODEM_SIM900
//#define TINY_GSM_MODEM_M590
//#define TINY_GSM_MODEM_A6
//#define TINY_GSM_MODEM_A7
//#define TINY_GSM_MODEM_BG96
//#define TINY_GSM_MODEM_XBEE

// Default heartbeat interval for GSM is 60
// If you want override this value, uncomment and set this option:
//#define BLYNK_HEARTBEAT 30

#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>
#include <DHT.h>
#include <LiquidCrystal.h>

// DHT sensor type and pin
#define DHTTYPE DHT11
#define DHTPIN A1

DHT dht(DHTPIN, DHTTYPE);

// Your GPRS credentials
// Leave empty, if missing user or pass
char apn[]  = "internet";
char user[] = "";
char pass[] = "";

// LCD pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Buzzer and fan pins
const int RELAY_PIN = 9; 

// Thresholds for temperature and humidity
const float TEMP_THRESHOLD = 10.0;  // Set your desired temperature threshold
const float HUMI_THRESHOLD = 30.0;  // Set your desired temperature threshold
// Hardware Serial on Mega, Leonardo, Micro
//#define mySerial Serial1

// or Software Serial on Uno, Nano
#include <SoftwareSerial.h>
SoftwareSerial mySerial(7,8); // RX, TX

TinyGsm modem(mySerial);

// Add this at the beginning of the code
int messageCount = 0;  // Counter for the number of messages sent
const int maxMessages = 3;  // Maximum number of messages to send

void setup()
{
  // Debug console
  Serial.begin(9600);

  delay(10);

  // Set GSM module baud rate
  mySerial.begin(9600);
  delay(3000);

  // Initialize modem
  Serial.println("Initializing modem...");
  modem.restart();
  
  // Unlock your SIM card with a PIN if needed
  //modem.simUnlock("1234");

  Blynk.begin(BLYNK_AUTH_TOKEN, modem, apn, user, pass);

  // Initialize DHT sensor
  dht.begin();
  
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("DHT11 Sensor");
  
  // Initialize buzzer and fan
  pinMode(RELAY_PIN, OUTPUT);
  
  Serial.println("DHT11 Humidity & Temperature Sensor");
}

void loop()
{
  Blynk.run();
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.setCursor(0, 1);
    lcd.print("Sensor Error    ");
    return;
  }
  
  Serial.print("Current humidity = ");
  Serial.print(humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(temperature); 
  Serial.println("°C");

  // Update LCD display
  lcd.setCursor(0, 0);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print("%    ");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C     ");
  
  // Send data to Blynk
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V0, temperature);
 
  // Check temperature threshold and activate buzzer, fan, or send message
  if (temperature > TEMP_THRESHOLD || humidity > HUMI_THRESHOLD) {
    // Activate buzzer and fan
    digitalWrite(RELAY_PIN, HIGH); // turn on fan 5 seconds
    delay(50000);
    digitalWrite(RELAY_PIN, LOW);  // turn off fan 5 seconds
    delay(50000);

    // Check if the number of messages sent is less than the maximum allowed
    if (messageCount < maxMessages) {
      // Send SMS
      Serial.println("Initializing..."); 
      delay(1000);

      mySerial.println("AT"); // Once the handshake test is successful, it will back to OK
      updateSerial();

      mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
      updateSerial();
      delay(3000);
      mySerial.println("AT+CPIN=1234");
      updateSerial();
      delay(1000);
      mySerial.println("AT+CMGS=\"+255768572253\""); // Change ZZ with country code and xxxxxxxxxxx with phone number to SMS
      updateSerial();
      mySerial.print("Alert Temperature has exceeded"); // Text content
      updateSerial();
      mySerial.write(26);

      // Increment the message counter
      messageCount++;
    }
  } 

  if (humidity > HUMI_THRESHOLD) {
    // Activate buzzer and fan
    digitalWrite(RELAY_PIN, HIGH); // turn on fan 5 seconds
    delay(5000);
    digitalWrite(RELAY_PIN, LOW);  // turn off fan 5 seconds
    delay(5000);

    // Check if the number of messages sent is less than the maximum allowed
    if (messageCount < maxMessages) {
      // Send SMS
      Serial.println("Initializing..."); 
      delay(1000);

      mySerial.println("AT"); // Once the handshake test is successful, it will back to OK
      updateSerial();

      mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
      updateSerial();
      delay(3000);
      mySerial.println("AT+CPIN=1234");
      updateSerial();
      delay(1000);
      mySerial.println("AT+CMGS=\"+255768572253\""); // Change ZZ with country code and xxxxxxxxxxx with phone number to SMS
      updateSerial();
      mySerial.print("Alert humidity is below the requred value"); // Text content
      updateSerial();
      mySerial.write(26);

      // Increment the message counter
      messageCount++;
    }
  } 

  delay(5000); // Wait 5 seconds before accessing sensor again.
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read()); // Forward what Serial received to Software Serial Port
  }
  while (mySerial.available()) 
  {
    Serial.write(mySerial.read()); // Forward what Software Serial received to Serial Port
  }
}
