#include "bcm.h"
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


void setup() {
  // put your setup code here, to run once:
  Timer1.setFrequencyFloat(100);
  Timer1.enableISR();

  pinMode(RUNNING_LIGHTS_SWITCH_PIN_INDEX, INPUT_PULLUP);
  pinMode(EMERGENCE_SWITCH_PIN_INDEX, INPUT_PULLUP);

  bcm_initialize();


  Serial.begin(9600, SERIAL_8N1);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (timer_10ms_event)
  {
    timer_10ms_event = 0;
    // inputs
    bcm_U.running_switch = digitalRead(RUNNING_LIGHTS_SWITCH_PIN_INDEX);
    bcm_U.emergence_switch1 = digitalRead(EMERGENCE_SWITCH_PIN_INDEX);
    
    bcm_step();

    analogWrite(RUNNING_LIGHTS_LED_LEFT, bcm_Y.running_LED_1);
    analogWrite(RUNNING_LIGHTS_LED_RIGHT, bcm_Y.running_LED_2);

    digitalWrite(TURN_SIGNAL_LED_LEFT, bcm_Y.emegrence_LED_2);
    digitalWrite(TURN_SIGNAL_LED_RIGHT, bcm_Y.emergence_LED_1);
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
