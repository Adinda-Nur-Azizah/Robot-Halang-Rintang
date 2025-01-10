#include <Servo.h>

// Pin definition
#define trigPin 6
#define echoPin 7
#define servoPin 5
#define motor1Pin1 8
#define motor1Pin2 9
#define motor2Pin1 11
#define motor2Pin2 12
#define enablePin1 10
#define enablePin2 13

Servo myservo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  
  myservo.attach(servoPin);
  myservo.write(90);  // Servo awal pada sudut 90 derajat
  
  Serial.begin(9600);
}

void loop() {
  long distance90 = measureDistance(90);
  if (distance90 < 40) {  // Menggunakan 50 cm sebagai batasan
    stopMotors();
    delay(500);  // Waktu untuk memastikan motor berhenti
    long distance0 = measureDistance(0);
    delay(500);
    long distance180 = measureDistance(180);
    
    if (distance0 > distance180) {
      turnLeft();

    } else {
      turnRight();
    }
    delay(2000);  // Menambah waktu untuk motor belok
    stopMotors();
    myservo.write(90);  // Servo kembali ke sudut 90 derajat
  } else {
    moveForward();
  }
  
  delay(100);  // Delay untuk mengurangi frekuensi pembacaan
}

long measureDistance(int angle) {
  myservo.write(angle);
  delay(500);  // Waktu untuk servo bergerak
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  
  Serial.print("Sudut: ");
  Serial.print(angle);
  Serial.print(" Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  return distance;
}

void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enablePin1, 255);  // Kecepatan penuh
  analogWrite(enablePin2, 255);  // Kecepatan penuh
}

void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enablePin1, 0);  // Hentikan motor
  analogWrite(enablePin2, 0);  // Hentikan motor
}

void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enablePin1, 255);  // Kecepatan penuh
  analogWrite(enablePin2, 255);  // Kecepatan penuh
}

void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(enablePin1, 255);  // Kecepatan penuh
  analogWrite(enablePin2, 255);  // Kecepatan penuh
}