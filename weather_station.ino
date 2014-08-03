#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 11  
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int ledPin1 = 12;
const int buttonPin1 = 13;

int button1Counter = 0;
int button1State = 0;
int lastButton1State = 0;
boolean readingOn = false;
unsigned long lastRefreshTime = 0;
float humidity;
float temperature;
int moisture;

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);
int runXTimesRead = 1;
int runXTimesReset = 1;

void setup() {  
  lcd.begin(16, 2);
  defaultDisplayState();
  resetResetCounter();
  
  pinMode(ledPin1, OUTPUT);
  pinMode(buttonPin1, OUTPUT);

  dht.begin();
}

void loop() {  
  button1State = digitalRead(buttonPin1);

  if(button1State != lastButton1State) {
    button1Counter++;
    Serial.println(button1Counter);
  }

  lastButton1State = button1State;

  if (button1Counter % 4 == 0) {
    digitalWrite(ledPin1, HIGH);
    readingOn = true;
  } 
  else {
    digitalWrite(ledPin1, LOW);
    readingOn = false;
  }

  if(!readingOn) {
    startReading();
    printTemperatureAndHumidity();
    readMoisture();
  }
}


//----------- Helper methods ----------------//
void startReading() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humidity = dht.readHumidity();
  // Read temperature as Celsius
  temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  } 
}



void readMoisture() {
  moisture = analogRead(0); 
}

void printTemperatureAndHumidity() {
  String resultTemp = String((long) temperature, DEC) + "*C";
  String resultHum  = String((long) humidity, DEC) + "%h";
  String resultMoist = String(moisture);
  
  lcd.setCursor(0, 0);
  lcd.print("Reading data...");
  lcd.setCursor(0, 1);
  lcd.print(resultTemp);
  lcd.setCursor(5, 1);
  lcd.print(resultHum);
  lcd.setCursor(10, 1);
  lcd.print(resultMoist);
}

void preReadState() {
  if (runXTimesRead) {
    lcd.clear();
    lcd.noBlink();
    runXTimesRead--;
   }
}

void defaultDisplayState() {
  if (runXTimesReset) {
    lcd.print("press button...");
    lcd.blink();
    runXTimesReset--;
   }
}

void resetReadCounter() {
  runXTimesRead = 1;
}

void resetResetCounter() {
  runXTimesReset = 1;
}

