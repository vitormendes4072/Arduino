#include <Ultrasonic.h>

int servo1 = 6;
int servo2 = 11;
int posicao;
int potpin = A0;

HC_SR04 sensor1(4,5);
HC_SR04 sensor2(12,10);

void setup() {
	Serial.begin(9600);
	pinMode(servo1, OUTPUT);
	pinMode(servo2, OUTPUT);
}

void loop() {
	servoPos(servo1, 0);//começa fechado compartimento da cápsula
	servoPos(servo2, 90);//começa na condição de repouso
	
	//posicao = analogRead(potpin);            // faz a leitura do potenciometro e salva em valor (valores entre 0-1023)
	//posicao = map(valor, 0, 1023, 0, 180);     // converte os valores para a escala do servo motor (valores entre 0-180)
	Serial.println(String("Distancia da xícara: ") + sensor1.distance() +String(" cm"));
	delaySegundos(1);
	if(sensor1.distance()<20){//distancia < 20cm tem que fazer café
		
		Serial.println(String("Distância da xícara: ") + sensor1.distance() +String(" cm"));
		Serial.println("Abrindo compartimento");
		delaySegundos(1);
		servoPos(servo1, 90);//abre o compartimento da cápsula
		delaySegundos(1);
		if(sensor2.distance()>30){//distancia >30cm cafe longo
			servoPos(servo2, 0);//faz o cafe longo
			//delaySegundos(10);
			Serial.println(String("Distância da mão: ") + sensor2.distance() +String(" cm"));
			Serial.println("Cafe longo");
			delaySegundos(1);
		}else{	
			servoPos(servo2, 180);//faz o cafe curto
			Serial.println("Cafe curto");
			delaySegundos(1);
		}
		servoPos(servo2, 90);//volta para a posição de repouso         
	}else{
		Serial.println("Nao tem que fazer cafe");
		servoPos(servo1, 0);//nao tem que fazer cafe
	}
}

void delaySegundos(int segundos){
	int mili = segundos * 1000;
	delay(mili);
}

//Função que controla a posição do servo motor. 
void servoPos (int servo, int pos)
{
  int microPulso = map(pos, 0,180,1000,2000);
  digitalWrite(servo, HIGH);
  delayMicroseconds(microPulso);
  digitalWrite(servo, LOW);
  delay(10);                   
}