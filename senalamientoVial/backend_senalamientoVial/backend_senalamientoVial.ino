/*
█▄▄ ▄▀█ █▀▀ █▄▀ █▀▀ █▄░█ █▀▄   ▄▄   █▀ █▀▀ █▄░█ ▄▀█ █░░ ▄▀█ █▀▄▀█ █ █▀▀ █▄░█ ▀█▀ █▀█   █░█ █ ▄▀█ █░░
█▄█ █▀█ █▄▄ █░█ ██▄ █░▀█ █▄▀   ░░   ▄█ ██▄ █░▀█ █▀█ █▄▄ █▀█ █░▀░█ █ ██▄ █░▀█ ░█░ █▄█   ▀▄▀ █ █▀█ █▄▄

Backend - Parte de sensores para senalamiento Vial
DHT11(Humedad y Temperatura del ambiente) -Sensor Laser(VLX53L0X)-Sensor De LLuvia

Este backend consiste en hacer la lectura de los sensores y recopilarla y despues hacer el envio
por EspNow a otro Esp para dibujar en Frontend
*/
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_VL53L0X.h>
#include <Ultrasonic.h>

#define DHTPIN 5            //pin de sensor dht
#define DHTTYPE DHT11 // Tipo de sensor DHT (DHT11, DHT21 o DHT22)
#define sensorLluviaPin 34  //pin de sensor de lluvia
#define TRIGGER_PIN 14      // Pin del Arduino conectado al pin TRIG del sensor
#define ECHO_PIN 12         // Pin del Arduino conectado al pin ECHO del sensor

#define ESP32_SENDER_ADDRESS 0x10
#define ESP32_RECEIVER_ADDRESS 0x20

double humedad;
double temperatura;
double velocidad;
double lluvia;

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);  //instancia del sensor
DHT dht(DHTPIN, DHTTYPE);                     //Objeto de sensor DHT11

void setup() {
  Serial.begin(115200);  //comunicacion serial
  while (!Serial) {
    delay(1);  // espere hasta que se abra el puerto serie para dispositivos USB nativos
  }
  pinMode(2,OUTPUT);
  pinMode(sensorLluviaPin, INPUT);  //pin de sensor de lluvia
  Wire.begin();                     // Inicializa la comunicación I2C
}

void loop() {
  lectura();  //lectura de sensores
  impresion();
  digitalWrite(2,HIGH);
  // Envío de datos por I2C
  enviarDatosI2C();

  delay(100);
  digitalWrite(2,LOW);
}

void lectura() {
  //metodo de lectura de lectura
  temperatura = dht.readTemperature();  //lectura de temperatura ambiente
  humedad = dht.readHumidity();         //lectura de humedad
  lluvia = analogRead(sensorLluviaPin);   //lectura digital de sensor de lluvia
  velocidad = calcular_velocidad();       //lectura de velocidad
}

float dist1, dist2;          // Distancias medidas
unsigned long time1, time2;  // Tiempos de las mediciones

double calcular_velocidad() {
  delay(50);  // Esperamos un poco entre mediciones

  dist1 = ultrasonic.read();  // Realizamos la primera medición
  time1 = millis();           // Guardamos el tiempo de la primera medición

  delay(1000);  // Esperamos un segundo

  dist2 = ultrasonic.read();  // Realizamos la segunda medición
  time2 = millis();           // Guardamos el tiempo de la segunda medición

  return (dist2 - dist1) / ((time2 - time1) / 1000.0);  // Calculamos la velocidad en cm/s
}

void impresion() {
  Serial.print(humedad);
  Serial.print(" - ");
  Serial.print(temperatura);
  Serial.print(" - ");
  Serial.print(lluvia);
  Serial.print(" - ");
  Serial.println(velocidad);
}

void enviarDatosI2C() {
  Wire.beginTransmission(ESP32_RECEIVER_ADDRESS);
  Wire.write((uint8_t*)&humedad, sizeof(double));
  Wire.write((uint8_t*)&temperatura, sizeof(double));
  Wire.write((uint8_t*)&lluvia, sizeof(double));
  Wire.write((uint8_t*)&velocidad, sizeof(double));
  Wire.endTransmission();
}
