#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>
 
const char *ssid =  "Name Wifi";// Nama wifi yang akan di pakai
const char *pass =  "password";// katasandi 
const char *server = "api.thingspeak.com";//server yang akan dipakai

#define DHTPIN 2 //pin DATA konek ke pin 2 Arduino
#define DHTTYPE DHT11 //tipe sensor DHT11
DHT dht(DHTPIN, DHTTYPE); //set sensor + koneksi pin

 
WiFiClient client;
 
long myChannelNumber =   2315244;//channel id pada server thingspeak
const char myWriteAPIKey[] = "TO5H5RBK5AW0UISW";//Write APIkeys pada server thingspeak
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
  ThingSpeak.begin(client);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println("Temperature: " + (String) t);
  Serial.println("Humidity: " + (String) h);
  ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  delay(200);
}
