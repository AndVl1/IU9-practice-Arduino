#include "GyverTimers.h"
#include <avr/eeprom.h>

#define RUNNING_LIGHTS_SWITCH_PIN_INDEX 13
#define EMERGENCE_SWITCH_PIN_INDEX 4
#define ANALOG_INPUT_PIN_INDEX A0

#define RUNNING_LIGHTS_LED_LEFT 5
#define RUNNING_LIGHTS_LED_RIGHT 6

#define TURN_SIGNAL_LED_LEFT 12
#define TURN_SIGNAL_LED_RIGHT 8

#define STOP_LED 7

#define RIGHT_TURN_SWITCH_INDEX 2
#define LEFT_TURN_SWITCH_INDEX 3

#define ANALOG_READ_MIN 0
#define ANALOG_READ_MAX 1023

#define INTERVAL 1000

#define ON 0
#define OFF 1

#define IO_ENABLED LOW
#define IO_DISABLED HIGH

#define TURNING_OFF 0
#define TURN_LEFT 1
#define TURN_RIGHT 2

#define EEPROM_ADDR 10

#define STOP_PEDAL_STIFFNESS_STEP 50

void turning_isr();
uint32_t get_percentage(int value, int percentage);

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

char inChar;

uint32_t eeprom_addr = EEPROM_ADDR;

uint32_t stop_lower_limit = get_percentage(1023, 30);

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
  
  eeprom_write_dword(&eeprom_addr, stop_lower_limit);

  attachInterrupt(
    0, turning_isr, CHANGE
  );

  attachInterrupt(
    1, turning_isr, CHANGE
  );
  
  Serial.begin(9600, SERIAL_8N1);
}

void loop() {

  stop_lower_limit = eeprom_read_dword(&eeprom_addr);
  
  if (Serial.available() > 0)
  {
    inChar = Serial.read();
    if (inChar == '-')
    {
      if (stop_lower_limit < STOP_PEDAL_STIFFNESS_STEP)
      {
        stop_lower_limit = 0;
      }
      else
      {
        stop_lower_limit -= STOP_PEDAL_STIFFNESS_STEP;
      }
    }
    else if (inChar == '+')
    {
      if (stop_lower_limit > 1023 - STOP_PEDAL_STIFFNESS_STEP)
      {
        stop_lower_limit = 1023;
      }
      else
      {
        stop_lower_limit += STOP_PEDAL_STIFFNESS_STEP;
      }
    }
    eeprom_update_dword(&eeprom_addr, stop_lower_limit);
    Serial.println(stop_lower_limit);
  }

  run_l_switch_state = digitalRead(RUNNING_LIGHTS_SWITCH_PIN_INDEX);
  emergence_switch_state = digitalRead(EMERGENCE_SWITCH_PIN_INDEX);
  stop_input_value = analogRead(ANALOG_INPUT_PIN_INDEX);

  unsigned long current_millis = millis();

  if (stop_lower_limit < stop_input_value) 
  {
    analogWrite(STOP_LED, 0);
    
    analogWrite(RUNNING_LIGHTS_LED_LEFT, 0);
    analogWrite(RUNNING_LIGHTS_LED_RIGHT, 0);
  }
  else 
  {
    analogWrite(STOP_LED, 255);

    if (run_l_switch_state == IO_ENABLED)
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

  if (emergence_switch_state == IO_ENABLED)
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
          digitalWrite(TURN_SIGNAL_LED_RIGHT, IO_DISABLED);
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
          digitalWrite(TURN_SIGNAL_LED_LEFT, IO_DISABLED);
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
          digitalWrite(TURN_SIGNAL_LED_LEFT, IO_DISABLED);
          digitalWrite(TURN_SIGNAL_LED_RIGHT, IO_DISABLED);
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

  if (turning_right_input_value == IO_ENABLED)
  {
    turning_state = TURN_RIGHT;
  }
  else if (turning_left_input_value == IO_ENABLED)
  {
    turning_state = TURN_LEFT;
  }
  else
  {
    turning_state = TURNING_OFF;
  }
  
  Serial.print("Right ");
  Serial.println(turning_right_input_value);
  Serial.print("Left " + turning_left_input_value);
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

uint32_t get_percentage(int value, int percentage)
{
  return (uint32_t) value * percentage / 100;
}
