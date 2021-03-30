#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10
  mySwitch.enableTransmit(12);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);
  
  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);
  Serial.println("init rcswitch");
}

void loop() {

  /* Same switch as above, but using binary code */
  mySwitch.send("os3: hello world!");

  delay(1000);
}
