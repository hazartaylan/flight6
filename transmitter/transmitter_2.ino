#include <VirtualWire.h>
const int numberOfAnalogPins = 4; // how many analog pins to read
int data[numberOfAnalogPins]; // the data buffer
const int dataBytes = numberOfAnalogPins * sizeof(int); 

void setup() {
//   pinMode(13, OUTPUT); //this is needed just to display the indication
// Initialize the IO and ISR
vw_set_ptt_inverted(true); // Required for DR3100
vw_setup(2000); // Bits per sec
}

void loop() {
int values = 0;
// digitalWrite(13, HIGH); 
for(int i=0; i <= numberOfAnalogPins; i++) {
data[i] = analogRead(i); // store the values into the data buffer
}
send((byte*)data, dataBytes);
delay(10); //send every second
//digitalWrite(13, LOW);
}

void send (byte *data, int nbrOfBytes) {
vw_send(data, nbrOfBytes);
vw_wait_tx(); // Wait until the whole message is gone
}
