//primeira versão ponteH com gyro
/*Pinagem do arduino*/

#include <MPU6050_tockn.h>
#include <Wire.h>
#include <math.h>

MPU6050 mpu6050(Wire);

int const balanceESC = 0;
int const balanceDIR = 7;


int AcrecESC = 0;
int AcrecDIR = 0;

int anguloZ = 0;

int velAjustDIR = 0;
int velAjustESC = 0;

int valMult = 20;

int const velInicial = 110;

//motor_ESQUERDO
int IN1 = 2 ;
int IN2 = 4 ;
int velocidadeESC = 3;

//motor_DIREITO
int IN3 = 6 ;
int IN4 = 7 ;
int velocidadeDIR = 5;

//variavel auxiliar
int cont = 0;
//Inicializa Pinos
void setup(){

Serial.begin(9600);
Wire.begin();
mpu6050.begin();
mpu6050.calcGyroOffsets(true);
  
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
pinMode(velocidadeESC,OUTPUT);
pinMode(velocidadeDIR,OUTPUT);

}

void loop(){

//=====================================================================================================

//=====================================================================================================

  mpu6050.update();
  
  //angulo atual do sensor


  
  anguloZ = mpu6050.getAngleZ();
  
 //acrecimo para correção
  AcrecDIR = round(anguloZ)*valMult;
  AcrecESC = round(anguloZ)*valMult;
    Serial.println(AcrecDIR);
      Serial.println(AcrecESC);
  Serial.println(round(anguloZ));
  if(int(anguloZ) ==0){
    analogWrite(velocidadeDIR,velInicial + balanceDIR);
    analogWrite(velocidadeESC,velInicial + balanceESC);
    
    delay(100);
    
  }

  if(anguloZ<0){
    velAjustDIR = velInicial+balanceDIR + abs(AcrecDIR);

    if(velAjustDIR <255){
      analogWrite(velocidadeDIR,velAjustDIR);
      analogWrite(velocidadeESC,velAjustESC-abs(AcrecESC));
      delay(10);
    }    
    else if(velAjustDIR > 255){
      velAjustDIR = 255;
      analogWrite(velocidadeDIR,velAjustDIR);
      analogWrite(velocidadeESC,velAjustESC-abs(AcrecESC));
      delay(10);  
    }
 }
  
  if(anguloZ >0){
    
    velAjustESC = velInicial+balanceESC + abs(AcrecESC);
    if(velAjustESC <255){
      analogWrite(velocidadeESC,velAjustESC);
      analogWrite(velocidadeDIR,velAjustDIR - abs(AcrecDIR));
      delay(10);
    }
    else if(velAjustESC >255){
      velAjustESC = 255;
      analogWrite(velocidadeESC,velAjustESC);
      analogWrite(velocidadeDIR,velAjustDIR - abs(AcrecDIR));
      delay(10);
    }
    
  }
//MOTOR A
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);

//MOTOR B
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);


}
