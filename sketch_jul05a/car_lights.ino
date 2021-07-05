const int BUTTON_PIN_INDEX = 2;
const int BUTTON_RELEASED_STATE = 0;
const int BUTTON_PRESSED_STATE = 1;

int button_state = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_PIN_INDEX, INPUT_PULLUP);
  Serial.begin(9600, SERIAL_8N1);
}

void loop() {
  button_state = digitalRead(BUTTON_PIN_INDEX);

  if (button_state != HIGH)
  {
    Serial.print("Pressed\n");
  } 
  else
  {
    Serial.print("Released\n");
  }
  
  
  delay(100);
}
