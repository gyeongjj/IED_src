#define PIN_LED 7
unsigned int count, toggle;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200); // Initialize serial port
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  Serial.println("Hello World!");
  count = 0;toggle = 0;
  digitalWrite(PIN_LED, toggle); // turn on LED.
  delay(1000);//wait for 1,000 milliseconds
}

void loop() {
  Serial.println(++count);
  toggle = toggle_state(toggle);// toggle LED value.
  digitalWrite(PIN_LED, toggle);// update LED status.
  if (count==11){
    while(1){} // infinite loop
  }
  delay(100); // wait for 1,00 milliseconds
}

int toggle_state(int toggle) {
  return !toggle; 
}
