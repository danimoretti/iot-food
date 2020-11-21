# iot-food
Um projeto para alimentar o animal doméstico via internet.

Materiais:

Raspberry Pi 3B
NodeMCU v3
Bateria externa
Motor de passos com micro controlador

Bibliotecas utilizadas no ArduinoIDE

PubSubClient -> Para utilizar o protocolo MQTT

Stepper -> Para utilizar  o motor de passos

Basta carregar o iot-food.ino usando o Arduino IDE ao modulo NodeMCU v3

Instalar no Raspberry PI 3 B o sistema do HomeAssistant - https://github.com/home-assistant/operating-system/releases/download/4.16/hassos_rpi3-4.16.img.gz

Configurar o dispositivo de acordo com a sua rede local e validar a conexão entre o NodeMCU com o Raspberry.


Video explicando a conexão entre os dispositivos e a estrutura dos jumpers entre o NodeMCU e o Micro Controlador do Motor de passos -> https://www.youtube.com/watch?v=ZqD2OyDVG9s&feature=youtu.be
