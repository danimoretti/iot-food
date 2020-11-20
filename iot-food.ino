#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Stepper.h>
// Update these with values suitable for your network.
const char* ssid = "Moretti";//put your wifi ssid here
const char* password = "vi10thais97";//put your wifi password here
const char* mqtt_server = "192.168.15.123";
const char* clientId = "iotfeeder";
const char* userName = "Moretti";
const char* passWord = "chico103";

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// initialize the stepper library on D1,D2,D5,D6
Stepper myStepper(stepsPerRevolution, D1, D2, D5, D6);
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
   delay(100);
  // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Executando comando via MQTT: [ topico:");
  Serial.print(topic);
  int p =(char)payload[0]-'0';
  int stepperLoop = 0;
  // step one revolution  in one direction:
  if(p==1) 
  {
    myStepper.step(stepsPerRevolution);
    Serial.print("  rodar motor]" );
   }
  // step one revolution in the other direction:
  else if(p==2)
  {
    myStepper.step(-stepsPerRevolution);
    Serial.print("  rodar o motor invertido]" );
  }
  else if(p==3)
  {
    Serial.print("  Liberando a ração: " );
    for (stepperLoop = 0; stepperLoop < 10; stepperLoop++) {
      myStepper.step(+stepsPerRevolution);
      Serial.print(stepperLoop);
      Serial.print(" ");
      delay(50);
    }
    Serial.print("]");
  }
  else if(p==4)
  {
    Serial.print("  Liberando a ração invertido: " );
    for (stepperLoop = 0; stepperLoop < 10; stepperLoop++) {
      myStepper.step(-stepsPerRevolution);
      Serial.print(stepperLoop);
      Serial.print(" ");
      delay(50);
    }
    Serial.print("]");
  }
  else if(p==0)
  {
    digitalWrite (D1,LOW);
    digitalWrite (D2,LOW);
    digitalWrite (D5,LOW);
    digitalWrite (D6,LOW); 
    Serial.print("  Desligado!]" );
  }
  Serial.println();
   
}
 
//  Serial.println();
 //end callback

void reconnect() {
  // Continua tentando estabelecer a conexão
  while (!client.connected()) 
  {
    Serial.print("Realizando conexão MQTT...");

    // Conectar
    if (client.connect(clientId,userName,passWord))
    {
      Serial.println("Conectado!");
     // once connected to MQTT broker, subscribe command if any
      client.subscribe("iotfeeder");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos...");
      // Aguarda 5 segundos antes de tentar novamente
      delay(5000);
    }
  }
} //end reconnect()

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  // Velocidade em rpm do motor em 100:
  myStepper.setSpeed(100);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
