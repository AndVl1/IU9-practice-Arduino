// TODO replace with define
// поворотники 4 и 7
#define RUNNING_LIGHTS_SWITCH_PIN_INDEX 2
#define EMERGENCE_SWITCH_PIN_INDEX 13
#define ANALOG_INPUT_PIN_INDEX A0
//#define TURN_LIGHTS_PIN_INDEX A1

#define RUNNING_LIGHTS_LED_LEFT 3
#define RUNNING_LIGHTS_LED_RIGHT 6

#define TURN_SIGNAL_LED_LEFT 12
#define TURN_SIGNAL_LED_RIGHT 8

#define STOP_LED 11

#define RIGHT_TURN_SWITCH_INDEX 4
#define LEFT_TURN_SWITCH_INDEX 7

//#define RIGHT_TURN_STATE 0
//#define LEFT_TURN_STATE 1023

#define ANALOG_READ_MIN 0
#define ANALOG_READ_MAX 1023

int run_l_switch_state = 0;
int emergence_switch_state = 0;
int stop_input_value = 0;
int turning_right_input_value = 0;
int turning_left_input_value = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(RUNNING_LIGHTS_SWITCH_PIN_INDEX, INPUT_PULLUP);
  pinMode(EMERGENCE_SWITCH_PIN_INDEX, INPUT_PULLUP);

  pinMode(RIGHT_TURN_SWITCH_INDEX, INPUT_PULLUP);
  pinMode(LEFT_TURN_SWITCH_INDEX, INPUT_PULLUP);

  pinMode(ANALOG_INPUT_PIN_INDEX, INPUT);
//  pinMode(TURN_LIGHTS_PIN_INDEX, INPUT);
  //  pinMode(RUNNING_LIGHTS_LED_LEFT, OUTPUT);
  //  pinMode(RUNNING_LIGHTS_LED_RIGHT, OUTPUT);
  pinMode(TURN_SIGNAL_LED_RIGHT, OUTPUT);
  pinMode(TURN_SIGNAL_LED_LEFT, OUTPUT);
  Serial.begin(9600, SERIAL_8N1);
}

void loop() {
  run_l_switch_state = digitalRead(RUNNING_LIGHTS_SWITCH_PIN_INDEX);
  emergence_switch_state = digitalRead(EMERGENCE_SWITCH_PIN_INDEX);
  stop_input_value = analogRead(ANALOG_INPUT_PIN_INDEX);

  turning_right_input_value = digitalRead(RIGHT_TURN_SWITCH_INDEX);
  turning_left_input_value = digitalRead(LEFT_TURN_SWITCH_INDEX);
  
//  turning_input_value = analogRead(TURN_LIGHTS_PIN_INDEX);
//  Serial.print(turning_input_value);
  Serial.print("TL ");
  Serial.print(digitalRead(LEFT_TURN_SWITCH_INDEX));
  Serial.print("\n");
  Serial.print("TR ");
  Serial.print(digitalRead(RIGHT_TURN_SWITCH_INDEX));
  Serial.print("\n");

  if (get_percentage(1023, 30) < stop_input_value) 
  {
    analogWrite(STOP_LED, 0);
    Serial.println(stop_input_value);
    // TODO включать габариты на всю
    analogWrite(RUNNING_LIGHTS_LED_LEFT, 0);
    analogWrite(RUNNING_LIGHTS_LED_RIGHT, 0);
  }
  else 
  {
    analogWrite(STOP_LED, 255);

    if (run_l_switch_state == LOW)
    {
      Serial.print("RUNNING Off\n");
      analogWrite(RUNNING_LIGHTS_LED_LEFT, 255);
      analogWrite(RUNNING_LIGHTS_LED_RIGHT, 255);
    }
    else
    {
      Serial.print("RUNNING On\n");    
      analogWrite(RUNNING_LIGHTS_LED_LEFT, 255 - get_percentage(255, 30));
      analogWrite(RUNNING_LIGHTS_LED_RIGHT, 255 - get_percentage(255, 30));
    }
  }

//  analogWrite(STOP_LED, stop_input_value / 4);

  if (emergence_switch_state == LOW)
  {
    Serial.print("EMERGENCE On\n");
    digitalWrite(TURN_SIGNAL_LED_LEFT, HIGH);
    digitalWrite(TURN_SIGNAL_LED_RIGHT, HIGH);
    delay(300);
    digitalWrite(TURN_SIGNAL_LED_LEFT, LOW);
    digitalWrite(TURN_SIGNAL_LED_RIGHT, LOW);
  }
  else
  {
    if (turning_right_input_value == LOW)
    {
      digitalWrite(TURN_SIGNAL_LED_LEFT, HIGH);
      digitalWrite(TURN_SIGNAL_LED_RIGHT, HIGH);
      delay(300);
      digitalWrite(TURN_SIGNAL_LED_RIGHT, LOW);
    }
    else if (turning_left_input_value == LOW)
    {
      digitalWrite(TURN_SIGNAL_LED_RIGHT, HIGH);
      digitalWrite(TURN_SIGNAL_LED_LEFT, HIGH);
      delay(300);
      digitalWrite(TURN_SIGNAL_LED_LEFT, LOW);
    }
    else {
      Serial.print("EMERGENCE Off\n");
      digitalWrite(TURN_SIGNAL_LED_LEFT, HIGH);
      digitalWrite(TURN_SIGNAL_LED_RIGHT, HIGH);
    }
  }


  delay(500);
}

int get_percentage(int value, int percentage)
{
  return value * percentage / 100;
}
