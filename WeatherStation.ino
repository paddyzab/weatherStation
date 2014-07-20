#include "DHT.h"

#define DHTPIN 2  
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int ledPin1 = 8;
const int buttonPin1 = 13;

int button1Counter = 0;
int button1State = 0;
int lastButton1State = 0;

boolean readingOn = false;


void setup() {
  Serial.begin(9600); 
  Serial.println("Starting reading...");
 
  pinMode(ledPin1, OUTPUT);
  pinMode(buttonPin1, OUTPUT);http:
  
  dht.begin();
}


void loop() {
  
   // read the state of the pushbutton value:
  button1State = digitalRead(buttonPin1);

  if(button1State != lastButton1State) {
    button1Counter++;
    Serial.println(button1Counter);
  }

  lastButton1State = button1State;

  if (button1Counter % 4 == 0) {
    digitalWrite(ledPin1, HIGH);
    readingOn = true;
  } else {
    digitalWrite(ledPin1, LOW);
    readingOn = false;
  }
  
  if(!readingOn) {
    startReading();
  }
}

void startReading() {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);
  

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");
}
