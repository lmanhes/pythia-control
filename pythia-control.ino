#include <Wire.h>
//#include "motor_control.cpp"
#include <VarSpeedServo.h> 



//Motor pan_servo(50, 130, 90);
//Motor tilt_servo(120, 180, 170);

VarSpeedServo pan_servo;
VarSpeedServo tilt_servo;


void setup() {
  Serial.begin(9600);
  
  Wire.begin(0x8);              // join i2c bus with address #8
  Wire.onReceive(receiveData);  // register receive event
  Wire.onRequest(sendData);     // register sending event
  
  pan_servo.attach(9);
  tilt_servo.attach(10);
}


void loop() {
  //pan_servo.Update();
  //tilt_servo.Update();
}


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveData(int howMany) {
  while(Wire.available())
  {
    byte cmd = Wire.read();  //cmd
    if (cmd == 5){
      uint8_t Buffer[howMany];
      Serial.print("Data : ");
      for(int i=0; i<howMany-1; i++){
        byte data = Wire.read();
        Buffer[i] = data;
        Serial.print(data);
        Serial.print("--");
      }
      Serial.println("");
      if (Buffer[0] == 0)
      {
        //pan_servo.UpdatePosition(Buffer[1]);
        //pan_servo.UpdateSpeed(Buffer[2]);
        pan_servo.write(Buffer[1], Buffer[2], false);
      }
      else 
      {
        //tilt_servo.UpdatePosition(Buffer[1]);
        //tilt_servo.UpdateSpeed(Buffer[2]);
        tilt_servo.write(Buffer[1], Buffer[2], false);
      }
    }
  }
}


void sendData() {
  uint8_t Buffer[2];
  //Buffer[0] = pan_servo.GetSpeed();
  //Buffer[1] = pan_servo.GetPosition();
  //Buffer[2] = tilt_servo.GetSpeed();
  //Buffer[3] = tilt_servo.GetPosition();
  Buffer[0] = 0;
  Buffer[1] = 0;
  Buffer[2] = 0;
  Buffer[3] = 0;
  Wire.write(Buffer, 4); 
}
