#include <Wire.h>
#include "motor_control.cpp"


Motor pan_servo(50, 130, 90);
Motor tilt_servo(120, 180, 170);


void setup() {
  Serial.begin(9600);
  
  Wire.begin(0x8);              // join i2c bus with address #8
  Wire.onReceive(receiveData);  // register receive event
  Wire.onRequest(sendData);     // register sending event
  
  pan_servo.Attach(9);
  tilt_servo.Attach(10);
}


void loop() {
  pan_servo.Update();
  tilt_servo.Update();
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
        pan_servo.UpdatePosition(Buffer[1]);
        pan_servo.UpdateSpeed(Buffer[2]);
      }
      else 
      {
        tilt_servo.UpdatePosition(Buffer[1]);
        tilt_servo.UpdateSpeed(Buffer[2]);
      }
    }
  }
}


void sendData() {
  uint8_t Buffer[2];
  Buffer[0] = pan_servo.GetSpeed();
  Buffer[1] = pan_servo.GetPosition();
  Buffer[2] = tilt_servo.GetSpeed();
  Buffer[3] = tilt_servo.GetPosition();
  Wire.write(Buffer, 4); 
}
