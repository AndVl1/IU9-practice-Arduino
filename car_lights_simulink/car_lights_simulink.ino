#include "bcm.h"
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

#define TURNING_OFF 0
#define TURN_LEFT 1
#define TURN_RIGHT 2

#define EEPROM_ADDR_STOP_MIN 10
#define EEPROM_ADDR_BLINK_INT 5
#define EEPROM_ADDR_RUNNING_BRIGHT 15

#define STOP_PEDAL_STIFFNESS_STEP 50
#define BRIGHTNESS_STEP_SIZE 11 // 2950 / 255 ~~ 11 || 50 - 3000

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

uint32_t eeprom_addr_stop_min = EEPROM_ADDR_STOP_MIN; 
uint8_t eeprom_addr_blink_int = EEPROM_ADDR_BLINK_INT;
uint8_t eeprom_addr_running_br = EEPROM_ADDR_RUNNING_BRIGHT; 
uint32_t stop_lower_limit = 300; // dword
uint8_t running_brightness = 70; // byte
uint8_t blink_period = 50; // byte
char inChar;


void setup() {
  // put your setup code here, to run once:
  Timer1.setFrequencyFloat(100);
  Timer1.enableISR();

  pinMode(RUNNING_LIGHTS_SWITCH_PIN_INDEX, INPUT_PULLUP);
  pinMode(EMERGENCE_SWITCH_PIN_INDEX, INPUT_PULLUP);

  pinMode(RIGHT_TURN_SWITCH_INDEX, INPUT_PULLUP);
  pinMode(LEFT_TURN_SWITCH_INDEX, INPUT_PULLUP);

  pinMode(ANALOG_INPUT_PIN_INDEX, INPUT);
  
  pinMode(TURN_SIGNAL_LED_RIGHT, OUTPUT);
  pinMode(TURN_SIGNAL_LED_LEFT, OUTPUT);

  pinMode(STOP_LED, OUTPUT);

  bcm_initialize();

  eeprom_write_dword(&eeprom_addr_stop_min, stop_lower_limit);
  eeprom_write_byte(&eeprom_addr_blink_int, blink_period);
  eeprom_write_byte(&eeprom_addr_running_br, running_brightness);

  Serial.begin(115200, SERIAL_8N1);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (timer_10ms_event)
  {
    timer_10ms_event = 0;

    if (Serial.available() > 0)
    {
      // R - running brightness
      // B - blinking rate
      // S - stop min value
      stop_lower_limit = eeprom_read_dword(&eeprom_addr_stop_min);
      inChar = Serial.read();
      if (inChar == 'S')
      {
        stop_lower_limit = Serial.parseInt();
      }
      else if (inChar == 'B')
      {
        blink_period = Serial.parseInt();
        Serial.println(blink_period);
      }
      else if (inChar == 'R') 
      {
        running_brightness = Serial.parseInt();
      }
      
      eeprom_update_dword(&eeprom_addr_stop_min, stop_lower_limit);
      eeprom_update_byte(&eeprom_addr_blink_int, blink_period);
      eeprom_update_byte(&eeprom_addr_running_br, running_brightness);
    }
    
    // inputs
    bcm_U.running_switch = !digitalRead(RUNNING_LIGHTS_SWITCH_PIN_INDEX);
    bcm_U.emergence_switch1 = !digitalRead(EMERGENCE_SWITCH_PIN_INDEX);
    bcm_U.turn_left_switch = !digitalRead(LEFT_TURN_SWITCH_INDEX);
    bcm_U.turn_right_switch = !digitalRead(RIGHT_TURN_SWITCH_INDEX);
    bcm_U.stop_signal_input = analogRead(ANALOG_INPUT_PIN_INDEX);
    bcm_U.stop_min_value = eeprom_read_dword(&eeprom_addr_stop_min);
    bcm_U.intensivity = 5 + eeprom_read_byte(&eeprom_addr_blink_int) * 1.132;
    //magic number :(
    bcm_U.running_intensivity = 255 - eeprom_read_byte(&eeprom_addr_running_br);
    
    bcm_step();

    analogWrite(RUNNING_LIGHTS_LED_LEFT, bcm_Y.running_LED_1);
    analogWrite(RUNNING_LIGHTS_LED_RIGHT, bcm_Y.running_LED_2);
    digitalWrite(STOP_LED, bcm_Y.stop_LED);

    digitalWrite(TURN_SIGNAL_LED_LEFT, bcm_Y.turning_LED_2);
    digitalWrite(TURN_SIGNAL_LED_RIGHT, bcm_Y.turning_LED_1);
  }
}

void timer_10ms()
{
  timer_10ms_event = 1;
}

ISR(TIMER1_A)
{
  timer_10ms();
}
