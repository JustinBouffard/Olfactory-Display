int scentPin1 = 25;
int scentPin2 = 26;
int scentPin3 = 27;
int scentPin4 = 33;

int bitRate = 115200;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(bitRate);

  // Pin Setup
  pinMode(scentPin1, OUPUT);
  pinMode(scentPin2, OUPUT);
  pinMode(scentPin3, OUPUT);
  pinMode(scentPin4, OUPUT);
  digitalWrite(scent, LOW);
}
// Turn on pin, wait 1 second, turn off pin
void activateScent(int scent) {
  digitalWrite(scent, HIGH);
}

void deactivateScent(int scent) {
  digitalWrite(scent, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  if (Serial.available()) {
    // Format "[on/off]:[int scent]"
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    int separator = command.indexOf(':');
    String action = command.substring(0, separator);
    int scent = command.substring(separator + 1).toInt();

    if (action == "on") {
      activateScent(scent);
    }
    else if (action == "off") {
      deactivateScent(scent);
    }
  }
}
