#include <Arduino.h>
#include <Servo.h>


class Motor
{
  Servo servo;
  int current_pos;            // current servo position
  int target_pos;             // target servo positions
  int increment;              // increment to move for each interval
  int updateInterval;         // interval between updates (define the speed of the motor)
  int max_amplitude;          // max range of the motor
  int min_amplitude;          // min range of the motor
  int target_angle;           // target angle to reach
  unsigned long lastUpdate;   // last update of position
  int speed;

  public:
    Motor(int b_min, int b_max, int start_pos)
    {
      min_amplitude = b_min;
      max_amplitude = b_max;
      current_pos = start_pos;
      target_pos = start_pos;
      increment = 1;
      speed = 20;
    }

    void Attach(int pin)
    {
      servo.attach(pin);
    }
    
    void Detach()
    {
      servo.detach();
    }
  
    int GetSpeed()
    {
      return speed;
    }
  
    void UpdateSpeed(int new_speed)
    {
      speed = new_speed;
      updateInterval = (int) new_speed / 4;
      Serial.println(updateInterval);
    }

    int GetPosition()
    {
      return current_pos;
    }

    void UpdatePosition(int new_pos)
    {
      // limit rotation range
      if (new_pos > max_amplitude)
      {
        new_pos = max_amplitude;
      }
      else if (new_pos < min_amplitude)
      {
        new_pos = min_amplitude;
      }
      
      target_pos = new_pos;

      // reverse increment in case we have to switch directions
      if (((target_pos < current_pos) && increment > 0) || ((target_pos > current_pos) && increment < 0))
      {
        increment = -increment;
      }
    }
    
    void Update()
    {

      if(((millis() - lastUpdate) > updateInterval) && current_pos != target_pos)  // time to update
      {
        lastUpdate = millis();
        current_pos += increment;
        servo.write(current_pos);
      }
    }
};
