const int RUNNING_LIGHTS_SWITCH_PIN_INDEX = 2;
const int EMERGENCE_SWITCH_PIN_INDEX = 13;
const int ANALOG_INPUT_PIN_INDEX = A0;
const int TURN_LIGHTS_PIN_INDEX = A1;

const int RUNNING_LIGHTS_LED_LEFT = 3;
const int RUNNING_LIGHTS_LED_RIGHT = 6;

const int TURN_SIGNAL_LED_LEFT = 12;
const int TURN_SIGNAL_LED_RIGHT = 8;

const int STOP_LED = 11;

const int BUTTON_RELEASED_STATE = 0;
const int BUTTON_PRESSED_STATE = 1;

const int RIGHT_TURN_STATE = 0;
const int LEFT_TURN_STATE = 1023;

int run_l_switch_state = 0;
int emergence_switch_state = 0;
int stop_input_value = 0;
int turning_input_value = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(RUNNING_LIGHTS_SWITCH_PIN_INDEX, INPUT_PULLUP);
  pinMode(EMERGENCE_SWITCH_PIN_INDEX, INPUT_PULLUP);

  pinMode(ANALOG_INPUT_PIN_INDEX, INPUT);
  pinMode(TURN_LIGHTS_PIN_INDEX, INPUT);
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
  turning_input_value = analogRead(TURN_LIGHTS_PIN_INDEX);
  Serial.print(turning_input_value);

  analogWrite(STOP_LED, stop_input_value / 4);

  if (run_l_switch_state == LOW)
  {
    Serial.print("RUNNING Off\n");
    analogWrite(RUNNING_LIGHTS_LED_LEFT, 255);
    analogWrite(RUNNING_LIGHTS_LED_RIGHT, 255);
  }
  else
  {
    Serial.print("RUNNING On\n");
    analogWrite(RUNNING_LIGHTS_LED_LEFT, 142);
    analogWrite(RUNNING_LIGHTS_LED_RIGHT, 142);
  }

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
    if (turning_input_value == RIGHT_TURN_STATE)
    {
      digitalWrite(TURN_SIGNAL_LED_RIGHT, HIGH);
      delay(300);
      digitalWrite(TURN_SIGNAL_LED_RIGHT, LOW);
    }
    else if (turning_input_value == LEFT_TURN_STATE)
    {
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
