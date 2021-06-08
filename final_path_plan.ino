#include <Servo.h>
//sensor pins
int trigPin=12; int echoPin=13;int metalD=3;
long duration,cm;
int distance = 100;
Servo servo_motor; //our servo name
char getstr;
//L298 motor driver pin
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;
int lookRight(){
servo_motor.write(60);
delay(500);
int distance = readPing();
delay(100);
servo_motor.write(90);
return distance;
}
int lookLeft(){
servo_motor.write(120);
delay(500);
int distance = readPing();
delay(100);
servo_motor.write(90);
return distance;
delay(100);
}
//Reading the distance of obstacle
int readPing(){
36
delay(70);
digitalWrite(trigPin,LOW); delayMicroseconds(5);
digitalWrite(trigPin,HIGH); delayMicroseconds(10);
digitalWrite(trigPin,LOW);
duration = pulseIn(echoPin,HIGH);
cm=(duration/2)/29.1; //*0.0341
if (cm==0){
cm=250;
}
return cm;
}
//Forward Movement Function
void _mForward()
{
digitalWrite(LeftMotorForward, HIGH);
digitalWrite(RightMotorForward, HIGH);
digitalWrite(LeftMotorBackward, LOW);
digitalWrite(RightMotorBackward, LOW);
Serial.println("go forward!");
}
//Backward Movement Function
void _mBack()
{
digitalWrite(LeftMotorBackward, HIGH);
digitalWrite(RightMotorBackward, HIGH);
digitalWrite(LeftMotorForward, LOW);
digitalWrite(RightMotorForward, LOW);
Serial.println("go back!");
}
//Left Movement Function
void _mleft()
{
digitalWrite(LeftMotorBackward, HIGH);
digitalWrite(RightMotorForward, HIGH);
digitalWrite(LeftMotorForward, LOW);
digitalWrite(RightMotorBackward, LOW);
delay(1000);
digitalWrite(LeftMotorForward, HIGH);
37
digitalWrite(RightMotorForward, HIGH);
digitalWrite(LeftMotorBackward, LOW);
digitalWrite(RightMotorBackward, LOW);
Serial.println("go left!");
}
//Right Movement Function
void _mright()
{
digitalWrite(LeftMotorForward, HIGH);
digitalWrite(RightMotorBackward, HIGH);
digitalWrite(LeftMotorBackward, LOW);
digitalWrite(RightMotorForward, LOW);
delay(1000);
digitalWrite(LeftMotorForward, HIGH);
digitalWrite(RightMotorForward, HIGH);
digitalWrite(LeftMotorBackward, LOW);
digitalWrite(RightMotorBackward, LOW);
Serial.println("go right!");
}
//Stop Function
void _mStop()
{
digitalWrite(RightMotorForward, LOW);
digitalWrite(LeftMotorForward, LOW);
digitalWrite(RightMotorBackward, LOW);
digitalWrite(LeftMotorBackward, LOW);
Serial.println("Stop!");
}
//Pin Declaration
void setup()
{
Serial.begin(9600);
pinMode(RightMotorForward, OUTPUT);
pinMode(LeftMotorForward, OUTPUT);
pinMode(LeftMotorBackward, OUTPUT);
pinMode(RightMotorBackward, OUTPUT);
servo_motor.attach(9); //our servo pin
//Ultrasonic sensor pin
38
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);
// metal detector pin
pinMode(metalD,INPUT);
servo_motor.write(90);
delay(2000);
distance = readPing();
delay(100);
distance = readPing();
delay(100);
}
void loop()
{
int m=25;
int distanceRight = 0;
int distanceLeft = 0;
delay(50);
distance = readPing();
Serial.println(distance);
delay(300);
if (distance <= 20){
Serial.println(distance);
_mStop();
delay(300);
_mBack();
delay(1000);
_mStop();
delay(300);
distanceRight = lookRight();
Serial.println("Right:");
Serial.println(distanceRight);
delay(300);
distanceLeft = lookLeft();
Serial.println("Left:");
Serial.println(distanceLeft);
delay(300);
if (m >= distanceRight){
_mleft();
_mStop();
}
else if(m >distanceLeft)
{
_mright();
_mStop();
}
}
39
else{
_mForward();
}
//Metal Detection
If(digitalRead(metalD)==LOW){
Serial.println(“Metal Detected”);
_mStop();
}
distance = readPing();
//Wireless Controlling
getstr=Serial.read();
if(getstr=='F') //For Forward Movement
{
_mForward();
}
else if(getstr=='B') //For Backward Movement
{
_mBack();
delay(200);
}
else if(getstr=='L') //For Left Movement
{
_mleft();
delay(200);
}
else if(getstr=='R') // For Right Movement
{
_mright();
delay(200);
}
else if(getstr=='X') // For Stop The Car
{
_mStop();
}
distance = readPing();
}
