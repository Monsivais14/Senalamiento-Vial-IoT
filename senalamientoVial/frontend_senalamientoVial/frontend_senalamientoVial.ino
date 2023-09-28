#include <Wire.h>
#include <TFT_eSPI.h>
#include <SD.h>
#include <SPI.h>

#define ESP32_SENDER_ADDRESS 0x10
#define ESP32_RECEIVER_ADDRESS 0x20
#define SD_CS 5

double humedad;
double temperatura;
double velocidad;
double lluvia;

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  Wire.begin(ESP32_RECEIVER_ADDRESS);
  Wire.onReceive(receiveData);

  tft.init();
  tft.setRotation(0);  // 320 de altura, 240 de ancho
  tft.fillScreen(TFT_WHITE);

  // Inicializa la tarjeta SD
  if (!SD.begin(SD_CS)) {
    tft.println("La inicialización de la tarjeta SD falló");
    Serial.println("La inicialización de la tarjeta SD falló!");
    return;
  }

  if (SD.exists("/sr-33.bmp")) {
    drawBMP("/sr-33.bmp", 0, 0);
  }

  delay(8000);

  if (SD.exists("/sr-100.bmp")) {
    drawBMP("/sr-100.bmp", 0, 0);
  }

  delay(8000);

    if (SD.exists("/sr-001.bmp")) {
    drawBMP("/sr-001.bmp", 0, 0);
  }

  delay(8000);
}

void loop() {
  // Tu código de loop, si es necesario.
}

void drawBMP(const char *filename, int16_t x, int16_t y) {
  File bmpFile = SD.open(filename);

  if (!bmpFile) {
    tft.println("No se pudo abrir el archivo BMP");
    return;
  }

  if (read16(bmpFile) == 0x4D42) {
    read32(bmpFile);
    read32(bmpFile);
    uint32_t bmpImageoffset = read32(bmpFile);
    read32(bmpFile);
    int32_t bmpWidth = read32(bmpFile);
    int32_t bmpHeight = read32(bmpFile);

    if (read16(bmpFile) == 1) {
      uint16_t bmpDepth = read16(bmpFile);

      if ((bmpDepth == 24) && (read32(bmpFile) == 0)) {
        bmpFile.seek(bmpImageoffset);

        uint16_t padding = (4 - ((bmpWidth * 3) % 4)) % 4;
        uint8_t lineBuffer[bmpWidth * 3 + padding];

        for (int32_t i = bmpHeight - 1; i >= 0; i--) {
          bmpFile.read(lineBuffer, sizeof(lineBuffer));
          uint8_t *bptr = lineBuffer;
          for (int32_t j = 0; j < bmpWidth; j++) {
            uint8_t b = *bptr++;
            uint8_t g = *bptr++;
            uint8_t r = *bptr++;
            uint16_t color = tft.color565(r, g, b);  // Convertir y mostrar en pantalla
            tft.drawPixel(x + j, y + i, color);      // Utilizar drawPixel en lugar de pushPixel
          }
        }
      }
    }
  }

  bmpFile.close();
}

uint16_t read16(File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read();
  ((uint8_t *)&result)[1] = f.read();
  return result;
}

uint32_t read32(File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read();
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read();
  return result;
}

void receiveData(int byteCount) {
  if (byteCount == sizeof(double) * 4) {
    Wire.readBytes((uint8_t *)&humedad, sizeof(double));
    Wire.readBytes((uint8_t *)&temperatura, sizeof(double));
    Wire.readBytes((uint8_t *)&lluvia, sizeof(double));
    Wire.readBytes((uint8_t *)&velocidad, sizeof(double));
  }
}