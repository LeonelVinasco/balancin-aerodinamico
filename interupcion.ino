#include<Servo.h>

Servo ESC;
String mara="";
int vel = 1400; // Amplitud minima de pulso para tu ESC
int datos[800];
int contador=0;
int cuentaPasos=0;
bool inter=true;
void setup() {
  //delay(3000);
  ESC.attach(9); // Pin en el que funciona
  //delay(3000); //Esperar 5 segundos para hacer la activacion
  //Activar el ESC
  ESC.writeMicroseconds(1000); //1000 = 1ms
  //Cambia el 1000 anterior por 2000 si
  //tu ESC se activa con un pulso de 2ms
  delay(5000); //Esperar 5 segundos para hacer la activacion


  Serial.begin(115200);
  Serial.println("yaaaaaaaaa1");
  SREG = (SREG & 0b01111111); //Desabilitar interrupciones
 TIMSK2 = TIMSK2|0b00000001; //Habilita la interrupcion por desbordamiento
 TCCR2B = 0b00000101; //Configura preescala para que FT2 sea de 68000.5Hz
 SREG = (SREG & 0b01111111) | 0b10000000; //Habilitar interrupciones //Desabilitar interrupciones
}


void loop() {
  if (Serial.available()>0) {
   mara = Serial.readString();
    vel=mara.toInt();
  }

  Serial.print(vel);
 Serial.print("   \t");
 Serial.println(analogRead(A0));
  Serial.print("   \t");


ESC.writeMicroseconds(vel);
//Serial.println("yaaaaaaaaa2");
 //Serial.println(vel);
if(contador>=1000){
for(int i=0; i<800; i++){
 Serial.println(datos[i]);
 Serial.println('\t');

 
}
}
}

ISR(TIMER2_OVF_vect) {
   if (vel<=2000 && inter){
      if (cuentaPasos<300){
          cuentaPasos++;
      }else{
          cuentaPasos=0;
          vel=vel+10;
      }
   }else{inter=false;
      if (cuentaPasos<300){
          cuentaPasos++;
      }else{
          cuentaPasos=0;
          vel=vel+10;
      }
   }
  /*  
    if(contador<800){
  datos[contador] = analogRead(A0);
  if(datos[contador]<=770){
    vel=1550;
  }
}else{
  vel=1550;
}
if(contador<10000){
  contador++;
}*/
}
