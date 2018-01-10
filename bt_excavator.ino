#include <Servo.h> // To Control Servo
#include <SoftwareSerial.h> // For UART Communication with Bluetooth Module

// Servo Setup
Servo base;
Servo arm_c;
Servo arm_base;

// For moving excavator
int right_wheel_fwd = 11;
int right_wheel_bckwd= 10;
int left_wheel_bckwd = 9;
int left_wheel_fwd = 8;

// UART Communication setup with bluetooth
SoftwareSerial bluetooth(2,3);
void setup() {
  // Attaching Servo here!
  base.attach(9);
  arm_c.attach(11); // Here use some other pins which is PWM Enabeled
  arm_base.attach(12); // Here use some other pins which is PWM Enabeled

  // Setting Pin Mode of Pins connected to Motor Driver
  pinMode(left_wheel_fwd, OUTPUT);
  pinMode(left_wheel_bckwd, OUTPUT);
  pinMode(right_wheel_fwd, OUTPUT);
  pinMode(right_wheel_bckwd, OUTPUT);

  // Starting Bluetooth Module
  bluetooth.begin(9600);  
}

void loop() {
  if(bluetooth.available()){ // If Bluetooth is available
    char _buffer = bluetooth.read();  // Read what bluetooth is sending and store in _buffer vairable
    //
    if(_buffer == 'F'){
      Serial.println("Forward");
     forward();
      
    }else if(_buffer == 'B'){
      Serial.println("Backwards");
      backward();
    }else if(_buffer == 'R'){
      Serial.println("Right");
      right();
    }else if(_buffer == 'L'){
      Serial.println("left");
      left();
    }else{
      brake();
    }
  }
  delay(10);
}

// Stop the bot
void brake(){
  digitalWrite(right_wheel_fwd, HIGH);
  digitalWrite(right_wheel_bckwd, HIGH);
  digitalWrite(left_wheel_fwd, HIGH);
  digitalWrite(left_wheel_bckwd, HIGH);
}

// Move Forward
void forward(){
  digitalWrite(right_wheel_fwd, HIGH);
  digitalWrite(right_wheel_bckwd, LOW);
  digitalWrite(left_wheel_fwd, HIGH);
  digitalWrite(left_wheel_bckwd, LOW);
}

// Move Backwards
void backward(){
  digitalWrite(right_wheel_fwd, LOW);
  digitalWrite(right_wheel_bckwd, HIGH);
  digitalWrite(left_wheel_fwd, LOW);
  digitalWrite(left_wheel_bckwd, HIGH);
}

// Move Right
void right(){
  digitalWrite(right_wheel_fwd, LOW);
  digitalWrite(right_wheel_bckwd, HIGH);
  digitalWrite(left_wheel_fwd, HIGH);
  digitalWrite(left_wheel_bckwd, LOW);
}

// Move Left
void left(){
  digitalWrite(right_wheel_fwd, HIGH);
  digitalWrite(right_wheel_bckwd, LOW);
  digitalWrite(left_wheel_fwd, LOW);
  digitalWrite(left_wheel_bckwd, HIGH);
}
