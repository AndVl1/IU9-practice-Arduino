#include "GyverTimers.h"

#define RUNNING_LIGHTS_SWITCH_PIN_INDEX 13
#define EMERGENCE_SWITCH_PIN_INDEX 4
#define ANALOG_INPUT_PIN_INDEX A0

#define RUNNING_LIGHTS_LED_LEFT 5
#define RUNNING_LIGHTS_LED_RIGHT 6

#define TURN_SIGNAL_LED_LEFT 12
#define TURN_SIGNAL_LED_RIGHT 8

#define STOP_LED 11

#define RIGHT_TURN_SWITCH_INDEX 2
#define LEFT_TURN_SWITCH_INDEX 3

#define ANALOG_READ_MIN 0
#define ANALOG_READ_MAX 1023

#define INTERVAL 1000

#define ON 0
#define OFF 1

#define TURNING_OFF 0
#define TURN_LEFT 1
#define TURN_RIGHT 2

unsigned long previous_millis = 0;

int run_l_switch_state = 0;
int emergence_switch_state = 0;
int stop_input_value = 0;
int turning_right_input_value = 0;
int turning_left_input_value = 0;
int turn_left_state = OFF;
int turn_right_state = OFF;
int emergence_state = OFF;
byte timer_10ms_event = 0;
byte turning_state = TURNING_OFF;

void turning_isr();
int get_percentage(int value, int percentage);

void setup() {
  // put your setup code here, to run once:
  Timer1.setFrequencyFloat(10);
  Timer1.enableISR();
  
  pinMode(RUNNING_LIGHTS_SWITCH_PIN_INDEX, INPUT_PULLUP);
  pinMode(EMERGENCE_SWITCH_PIN_INDEX, INPUT_PULLUP);

  pinMode(RIGHT_TURN_SWITCH_INDEX, INPUT_PULLUP);
  pinMode(LEFT_TURN_SWITCH_INDEX, INPUT_PULLUP);

  pinMode(ANALOG_INPUT_PIN_INDEX, INPUT);
  
  pinMode(TURN_SIGNAL_LED_RIGHT, OUTPUT);
  pinMode(TURN_SIGNAL_LED_LEFT, OUTPUT);

  attachInterrupt(
    0, turning_isr, CHANGE
  );

  attachInterrupt(
    1, turning_isr, CHANGE
  );
  
  Serial.begin(9600, SERIAL_8N1);
}

void loop() {
  run_l_switch_state = digitalRead(RUNNING_LIGHTS_SWITCH_PIN_INDEX);
  emergence_switch_state = digitalRead(EMERGENCE_SWITCH_PIN_INDEX);
  stop_input_value = analogRead(ANALOG_INPUT_PIN_INDEX);

  unsigned long current_millis = millis();

  if (get_percentage(1023, 30) < stop_input_value) 
  {
    analogWrite(STOP_LED, 0);
    
    analogWrite(RUNNING_LIGHTS_LED_LEFT, 0);
    analogWrite(RUNNING_LIGHTS_LED_RIGHT, 0);
  }
  else 
  {
    analogWrite(STOP_LED, 255);

    if (run_l_switch_state == LOW)
    {
      analogWrite(RUNNING_LIGHTS_LED_LEFT, 255);
      analogWrite(RUNNING_LIGHTS_LED_RIGHT, 255);
    }
    else
    {  
      analogWrite(RUNNING_LIGHTS_LED_LEFT, 255 - get_percentage(255, 30));
      analogWrite(RUNNING_LIGHTS_LED_RIGHT, 255 - get_percentage(255, 30));
    }
  }

  if (emergence_switch_state == LOW)
  {
    if (current_millis - previous_millis >= INTERVAL)
    {
      previous_millis = current_millis;
      if (emergence_state == OFF)
      {
        emergence_state = ON;
      } 
      else
      {
        emergence_state = OFF;
      }
    }
    digitalWrite(TURN_SIGNAL_LED_LEFT, emergence_state);
    digitalWrite(TURN_SIGNAL_LED_RIGHT, emergence_state);
  }
  else
  {
    if (timer_10ms_event)
    {
      timer_10ms_event = 0;

      switch(turning_state) {
        case TURN_LEFT:
          digitalWrite(TURN_SIGNAL_LED_RIGHT, HIGH);
          if (current_millis - previous_millis >= INTERVAL)
          {
            previous_millis = current_millis;
            if (turn_left_state == OFF)
            {
              turn_left_state = ON;
            } 
            else
            {
              turn_left_state = OFF;
            }
          }
          digitalWrite(TURN_SIGNAL_LED_LEFT, turn_left_state);
          break;
        case TURN_RIGHT:
          digitalWrite(TURN_SIGNAL_LED_LEFT, HIGH);
          if (current_millis - previous_millis >= INTERVAL)
          {
            previous_millis = current_millis;
            if (turn_right_state == OFF)
            {
              turn_right_state = ON;
            } 
            else
            {
              turn_right_state = OFF;
            }
          }
          digitalWrite(TURN_SIGNAL_LED_RIGHT, turn_right_state);
          break;
        default:
          digitalWrite(TURN_SIGNAL_LED_LEFT, HIGH);
          digitalWrite(TURN_SIGNAL_LED_RIGHT, HIGH);
          emergence_state = OFF;
          turn_right_state = OFF;
          turn_left_state = OFF;
          break;
      }
    }
  }
}

void turning_isr()
{
  turning_right_input_value = digitalRead(RIGHT_TURN_SWITCH_INDEX);
  turning_left_input_value = digitalRead(LEFT_TURN_SWITCH_INDEX);

  if (turning_right_input_value == LOW)
  {
    turning_state = TURN_RIGHT;
  }
  else if (turning_left_input_value == LOW)
  {
    turning_state = TURN_LEFT;
  }
  else
  {
    turning_state = TURNING_OFF;
  }
  
  Serial.print("Right ");
  Serial.println(turning_right_input_value);
  Serial.print("Left ");
  Serial.println(turning_left_input_value);
}

void timer_10ms()
{
  timer_10ms_event = 1;
}

ISR(TIMER1_A)
{
  timer_10ms();
}

int get_percentage(int value, int percentage)
{
  return value * percentage / 100;
}
