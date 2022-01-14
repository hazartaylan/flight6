#include <SoftwareServo.h>
#include <SoftwareSerial.h>
#include <VirtualWire.h>
#include <ServoTimer2.h>

//#define DEBUG_MODE

ServoTimer2 myservo1;
SoftwareServo myservo2;
SoftwareServo myservo3;
SoftwareServo myservo4;

const int numberOfAnalogPins = 4; // how many analog integer values to receive
int data[numberOfAnalogPins]; // the data buffer
int value[numberOfAnalogPins];
// the number of bytes in the data buffer
const int dataBytes = numberOfAnalogPins * sizeof(int);
byte msgLength = dataBytes;

void setup() {
  myservo1.attach(9);  //Propeller
  myservo2.attach(10);  //Rudder
  myservo3.attach(8);  // Ailron
  myservo4.attach(12);   // Elevator

  Serial.begin(9600);

#ifdef DEBUG_MODE
  Serial.println("Ready");
#endif

  // Initialize the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000); // Bits per sec
  vw_set_rx_pin(11);  
  vw_rx_start(); // Start the receiver
}


void loop(){

  if (vw_get_message((byte*)data, &msgLength))  {    // Non-blocking

#ifdef DEBUG_MODE  
  Serial.println("Got: ");
#endif

  if(msgLength == dataBytes){
  for (int i = 1; i < numberOfAnalogPins; i++) {

#ifdef DEBUG_MODE    
  Serial.print("pin ");
  Serial.print(i);
  Serial.print("=");
  Serial.println(data[i]);
#endif
  value[0]=map(data[0],0,1023,1000,2000);
  
  value[i]=map(data[i],0,1023,0,179);  // Write into the servo
  }
  
  myservo1.write(value[0]);
  myservo2.write(value[1]);
  myservo3.write(value[2]);
  myservo4.write(value[3]);
  delay(50);
  SoftwareServo::refresh();   //refresh the servo
  }
  else {
#ifdef DEBUG_MODE    
  Serial.print("unexpected msg length of ");
  Serial.println(msgLength);
#endif
  }
#ifdef DEBUG_MODE      
  Serial.println();
#endif
  }
}


