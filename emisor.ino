//Librerias
#include <DHT.h>
#include <VirtualWire.h>

#define DHTPIN 5          
#define DHTTYPE DHT11     
#define RF_TX_PIN 2

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  vw_set_tx_pin(RF_TX_PIN);
  vw_setup(2000);
  dht.begin();
}


void loop()
{
  float h = dht.readHumidity(); //Se lee la humedad
  float t = dht.readTemperature(); //Se lee la temperatura

  char buf[VW_MAX_MESSAGE_LEN]; // Cadena para enviar
  String str = "";

  str = "i" + String(h); //convertimos el float a String y agregamos un inicio de trama
  str.toCharArray(buf, sizeof(buf)); //convertimos el String en un array
  vw_send((uint8_t *)buf, strlen(buf)); //Enviamos el array
  vw_wait_tx(); //Esperamos hasta que el mensaje se envie

  str = "f" + String(t); //convertimos el float a String y agramos un inicio de trama
  str.toCharArray(buf, sizeof(buf)); //convertimos el String en un array
  vw_send((uint8_t *)buf, strlen(buf)); ////Enviamos el array
  vw_wait_tx(); //Esperamos hasta que el mensaje se envie

  delay(20);
}
