const int directionSwitchPin = 6;    // switch input
const int onOffSwitchPin = 7; // On - off button
const int motor1Pin = 11;    // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 12;    // H-bridge leg 2 (pin 7, 2A)
const int enablePin = 9;    // H-bridge enable pin
const int encoderA = 2;    // Encoder A output
const int encoderB = 3;    // Encoder B output
const int speedControl = A0;
int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
int directionSwitchState = 0;
int previousDirectionSwitchState = 0;
int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1;
int encoderValueA;
int previousValueA = 0;
long stepsA = 0;
int encoderValueB;
int previousValueB = 0;
int motorPosition;

void setup() {
    // set the switch as an input:
    pinMode(directionSwitchPin, INPUT); 
    pinMode(onOffSwitchPin, INPUT);
 
    // set all the other pins you're using as outputs:
    pinMode(motor1Pin, OUTPUT);
    pinMode(motor2Pin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    pinMode(encoderA, INPUT);
    pinMode(encoderB, INPUT);
 
    // set enablePin high so that motor can turn on:
    digitalWrite(enablePin, LOW);

    Serial.begin(2000000);
  }
//In the main loop() read the switch. If it’s high, turn the motor one way by taking one H-bridge pin high and the other low. If the switch is low, reverse the direction by reversing the states of the two H-bridge pins.

void loop() {

  onOffSwitchState = digitalRead(onOffSwitchPin);
  delay(1);
  directionSwitchState = digitalRead(directionSwitchPin);
  motorSpeed = analogRead(speedControl)/4;

  if(onOffSwitchState != previousOnOffSwitchState){
    if(onOffSwitchState == HIGH){
      motorEnabled = !motorEnabled;
    }
  }

  if (directionSwitchState != previousDirectionSwitchState){
    if (directionSwitchState == HIGH) {
      motorDirection = !motorDirection;
    }
  }
  
    // if the switch is high, motor will turn on one direction:
    if (motorDirection == 1 ) {
      digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
      digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high
    }
    // if the switch is low, motor will turn in the other direction:
    else {
      digitalWrite(motor1Pin, HIGH);  // set leg 1 of the H-bridge high
      digitalWrite(motor2Pin, LOW);   // set leg 2 of the H-bridge low
    }
    

    //while(stepsA != -1){
    //digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
    //digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high
   
    encoderValueA = digitalRead(encoderA);
    encoderValueB = digitalRead(encoderB);

   if((encoderValueA == 0) && previousValueA == 1){
    if(encoderValueB == 0){
      stepsA--;
    }
    else{
      stepsA++;
    }
   }

   if((encoderValueA == 1) && (previousValueA == 0)){
    if(encoderValueB == 1){
      stepsA--;
    }
    else{
      stepsA++;
    }
   }

   Serial.print("Position: ");
   Serial.print(stepsA);
   Serial.print("  Enable Pin: ");
   Serial.print(motorEnabled);
   Serial.print("  Direction Pin: ");
   Serial.print(motorDirection);
   Serial.print("  Motor Speed: ");
   Serial.println(motorSpeed);

   if (motorEnabled == 1){
    analogWrite(enablePin, motorSpeed);
   }
   else {
    analogWrite(enablePin, 0);
   }
   previousValueA = encoderValueA;

   previousDirectionSwitchState = directionSwitchState;
   previousOnOffSwitchState = onOffSwitchState;

   

    //}

   

    //Serial.print("Encoder Value A is: ");
    //Serial.println(encoderValueA);
    //Serial.print("Encoder value B is: ");
    //Serial.println(encoderValueB);
    //Serial.print("Position: ");
    //Serial.println(stepsA);
   
  }
