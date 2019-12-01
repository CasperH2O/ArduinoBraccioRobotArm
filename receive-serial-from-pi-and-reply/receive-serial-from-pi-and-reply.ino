int previncomingByte = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  SerialUSB.begin(19200);
}

void loop() {
  // By default, the last intialized port is listening.
  // when you want to listen on a port, explicitly select it:
  //SerialUSB.read();
  
  // while there is data coming in, read it
  // and send to the hardware serial port:
  while (SerialUSB.available() > 0) {
    int incomingByte = SerialUSB.read();
    
    // Check if this value is different from before
    if(incomingByte != previncomingByte){
        // say what you got:
        Serial.print("I received: ");
        Serial.println(incomingByte, DEC);
        previncomingByte = incomingByte;
    }
    
  }

  // blank line to separate data from the two ports:
  //Serial.println("From Arduino to Programming Serial");

  //delay(3000);
}