#include <AFMotor.h>

#define LED1 = 36;
#define LED2 = 39;
#define LED3 = 38;
#define LED4 = 37;

#define LAMP1 = 52;
#define LAMP2 = 50;
#define LAMP3 = 24;
#define LAMP4 = 22;

int BUZZER = 48;

String readString;

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_64KHZ);

int val = 0;
int stato = 0;

void setup() {
  Serial.begin(9600);
  motor1.setSpeed(500);
  motor2.setSpeed(500);
  motor3.setSpeed(500);
  motor4.setSpeed(500);
  pinMode(36, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(52, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(48, OUTPUT);
}

void loop() {
  while (Serial.available()) {
    delay(3);
    char c = Serial.read();
    readString += c;
  }

  if (readString.length() > 0) {
    Serial.println(readString);

    if (readString == "A") {
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
    }

    if (readString == "I") {
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor3.run(BACKWARD);
      motor4.run(BACKWARD);
    }

    if (readString == "D") {
      motor1.run(FORWARD);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(FORWARD);
    }

    if (readString == "S") {
      motor1.run(RELEASE);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(RELEASE);
    }

    if (readString == "STOP") {
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
    }

    val = readString == "L";

    if (val == HIGH) {
      stato = 1 - stato;
    }

    if (stato == 1) {
      digitalWrite(36, HIGH);
      digitalWrite(38, HIGH);
      digitalWrite(39, HIGH);
      digitalWrite(37, HIGH);
    }

    else {
      digitalWrite(36, LOW);
      digitalWrite(38, LOW);
      digitalWrite(39, LOW);
      digitalWrite(37, LOW);
    }

    if (readString == "B") {
      digitalWrite (22 , LOW);
      digitalWrite (52 , HIGH);
      digitalWrite (24 , HIGH);
      digitalWrite (50 , LOW);
      tone(48, 392);
      delay(300);
      digitalWrite (22 , HIGH);
      digitalWrite (24 , LOW);
      digitalWrite (52 , LOW);
      digitalWrite (50 , HIGH);
      tone(48, 660);
    }
    
    else if (readString == "Z") {
      digitalWrite (52 , LOW);
      digitalWrite (50 , LOW);
      digitalWrite (24 , LOW);
      digitalWrite (22 , LOW);
      noTone(48);
    }
  }
  readString = "";
}

