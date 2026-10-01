int scentPins[] = {25, 26, 27, 33};

int bitRate = 115200;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(bitRate);

  // Pin Setup
  for (int i = 0; i < sizeof(scentPins); i++) {
    pinMode(scentPins[i], OUPUT);
  }
}
// Turn on pin
void activateScent(int scent) {
  digitalWrite(scent, HIGH);
}

// Turn off pin
void deactivateScent(int scent) {
  digitalWrite(scent, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  if (Serial.available()) {
    // Format "[on/off]:[int scent 1-4]"
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    int separator = command.indexOf(':');
    String action = command.substring(0, separator);
    int scent = command.substring(separator + 1).toInt() - 1;

    if (action == "on") {
      activateScent(scentPins[scent]);
    }
    else if (action == "off") {
      deactivateScent(scentPins[scent]);
    }
  }
}
