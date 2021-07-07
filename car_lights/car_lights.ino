const int RUNNING_LIGHTS_SWITCH_PIN_INDEX = 2;
const int RUNNING_LIGHTS_LED = 4;
const int BUTTON_RELEASED_STATE = 0;
const int BUTTON_PRESSED_STATE = 1;

int r_l_switch_state = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(RUNNING_LIGHTS_SWITCH_PIN_INDEX, INPUT_PULLUP);
  pinMode(RUNNING_LIGHTS_LED, OUTPUT);
  Serial.begin(9600, SERIAL_8N1);
}

void loop() {
  r_l_switch_state = digitalRead(RUNNING_LIGHTS_SWITCH_PIN_INDEX);

  if (r_l_switch_state == LOW)
  {
    Serial.print("On\n");
    digitalWrite(RUNNING_LIGHTS_LED, HIGH);
  } 
  else
  {
    Serial.print("Off\n");
    digitalWrite(RUNNING_LIGHTS_LED, LOW);

  }
  
  
  delay(500);
}
