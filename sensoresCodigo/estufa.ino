#include "DHT.h"
#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

// Definir as entradas da lâmpada e da válvula
int releLampada = 7;
int releValvula = 6;

// Conecte pino 1 do sensor (esquerda) ao +5V
// Conecte pino 2 do sensor ao pino de dados definido em seu Arduino
// Conecte pino 4 do sensor ao GND
// Conecte o resistor de 10K entre pin 2 (dados)
// e ao pino 1 (VCC) do sensor
DHT dht(DHTPIN, DHTTYPE);

const int sensor_ldr = A5;     // pino de leitura analogica do sensor ldr
#define sensor_umidade_solo A2 // pino de leitura analogica do sensor de umidade do solo

void setup()
{
  Serial.begin(9600);
  Serial.println("DHT OK!");
  pinMode(sensor_umidade_solo, INPUT);
  pinMode(releLampada, OUTPUT);
  pinMode(releValvula, OUTPUT);
  dht.begin();
}

void loop()
{
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  int luminosidade = analogRead(sensor_ldr);
  int umidadeSolo = analogRead(sensor_umidade_solo);

  //Se a luminosidade for maior que 500 liga a lâmpada, caso contrário, desliga
  if (luminosidade > 500) {
    digitalWrite(releLampada, HIGH);
  } else {
    digitalWrite(releLampada, LOW);
  }

  //Segundo o FilipeFlop: 0-400 - Solo umido, 400-800 - Solo com umidade moderada, 800-1024 - Solo seco
  //Se o a umidade do solo estiver entre 800 e 1024, liga a valvula, caso contrário, desliga
  if (umidadeSolo > 700 && umidadeSolo < 1024)
  {
    digitalWrite(releValvula, HIGH);
  } else {
    digitalWrite(releValvula, LOW);
  }


/*
  Serial.print("Luminosidade: ");
  Serial.println(luminosidade);*/

  Serial.print("Umidade do solo: ");
  Serial.println(umidadeSolo);

/*
   Serial.print("Umidade do ar: ");
    Serial.println(h);
    Serial.print("Temperatura: ");
    Serial.println(t);*/

   /*
  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.print(" %t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C");*/
  
  delay(200);
}
