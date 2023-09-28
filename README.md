# Proyecto: Señalamiento Vial Inteligente Programable

Señalamiento Vial - Prototipo de pruebas

## Descripción

El proyecto "Señalamiento Vial Inteligente Programable" es un prototipo en desarrollo que tiene como objetivo crear un sistema de señalamiento vial inteligente y programable para diferentes entornos. Este sistema utiliza dos placas ESP32 que se comunican a través del protocolo I2C, una como maestro y otra como esclavo.

## Características Principales

- **Maestro (ESP32)**
  - Sensor de temperatura y humedad DHT11 para monitoreo de condiciones climáticas.
  - Sensor de lluvia para detectar la presencia de lluvia.
  - Sensor ultrasónico para medir la distancia a objetos cercanos.
  - Recopilación de datos de sensores y envío por protocolo I2C al esclavo.
  
- **Esclavo (ESP32)**
  - Pantalla ILI9342 de 320x240 píxeles para mostrar señales de tráfico programables.
  - Recepción de datos del maestro a través de la comunicación I2C.
  - Almacenamiento de imágenes en una tarjeta SD.
  
## Tecnologías Utilizadas

- Para el maestro:
  - Bibliotecas utilizadas: Ultrasonic, DHT y Wire.

- Para el esclavo:
  - Bibliotecas utilizadas: TFT_eSPI, Wire, SD y SPI.

## Uso

Este proyecto es un prototipo en desarrollo y su uso está limitado a pruebas y demostraciones conceptuales. No se recomienda su implementación en entornos de producción o en situaciones reales de señalización vial.

El propósito principal de este prototipo es servir como una plataforma de aprendizaje y experimentación para la creación de sistemas de señalización vial inteligente más profesionales y completos en el futuro. Puede ser utilizado para:

- Experimentar con la comunicación entre dispositivos ESP32 a través del protocolo I2C.
- Familiarizarse con la integración de sensores como DHT11, sensor de lluvia y sensor ultrasónico en un sistema embebido.
- Explorar la interfaz de pantalla ILI9342 y su capacidad para mostrar señales de tráfico programables.
- Practicar el almacenamiento de imágenes en una tarjeta SD.
- Explorar la dinámica de comunicación entre un maestro y un esclavo, similar a una relación de backend y frontend, donde el maestro actúa como backend (manejo de sensores) y el esclavo como frontend (interfaz de usuario).

Por favor, ten en cuenta que este proyecto no está diseñado para su implementación en condiciones de tráfico real o entornos de producción. Se recomienda utilizarlo únicamente en entornos controlados con fines educativos y de desarrollo.

## Instalación

Por ser un prototipo de temprano desarrollo se recomienda hacer pruebas de los sensores en condiciones controladas

## Licencia

Este proyecto está bajo la Licencia MIT. Consulta el archivo [LICENSE](LICENSE) para más detalles.
