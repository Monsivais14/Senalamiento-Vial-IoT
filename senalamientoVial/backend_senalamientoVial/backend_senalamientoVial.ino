/*
█▄▄ ▄▀█ █▀▀ █▄▀ █▀▀ █▄░█ █▀▄   ▄▄   █▀ █▀▀ █▄░█ ▄▀█ █░░ ▄▀█ █▀▄▀█ █ █▀▀ █▄░█ ▀█▀ █▀█   █░█ █ ▄▀█ █░░
█▄█ █▀█ █▄▄ █░█ ██▄ █░▀█ █▄▀   ░░   ▄█ ██▄ █░▀█ █▀█ █▄▄ █▀█ █░▀░█ █ ██▄ █░▀█ ░█░ █▄█   ▀▄▀ █ █▀█ █▄▄

Backend - Parte de sensores para senalamiento Vial
DHT11(Humedad y Temperatura del ambiente) -Sensor Laser(VLX53L0X)-Sensor De LLuvia

Este backend consiste en hacer la lectura de los sensores y recopilarla y despues hacer el envio
por EspNow a otro Esp para dibujar en Frontend
*/
#include <DHT11.h>
#include <Adafruit_VL53L0X.h>
#include <Ultrasonic.h>

#define dhtPin 5            //pin de sensor dht
#define sensorLluviaPin 34  //pin de sensor de lluvia
#define TRIGGER_PIN 14      // Pin del Arduino conectado al pin TRIG del sensor
#define ECHO_PIN 12         // Pin del Arduino conectado al pin ECHO del sensor

//variables capturadas por el backend
double humedad;
double temperatura;
double velocidad;
double lluvia;

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);  // Creamos una instancia del sensor
DHT11 dht11(dhtPin);                           //Objeto de sensor DHT11

void setup() {
  Serial.begin(115200);  //comunicacion serial
  while (!Serial) {
    delay(1);  // espere hasta que se abra el puerto serie para dispositivos USB nativos
  }

  pinMode(sensorLluviaPin, INPUT);  //pin de sensor de lluvia
}

void loop() {

  lectura();  //lectura de sensores

  impresion();

  //envio por espNow al frontend

  delay(100);  //delay de envio
}

void lectura() {
  //metodo de lectura de lectura
  temperatura = dht11.readTemperature();  //lectura de temperatura ambiente
  humedad = dht11.readHumidity();         //lectura de humedad
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
