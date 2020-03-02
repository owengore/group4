/* Module 1 Program  
 *  
 *  Any changes made should be mirrored across the other 3 files.
 */

//Includes
#include <SPI.h>
#include <LoRa.h>
//Includes

//Definitions
#define uS_to_S_factor 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define sleep_duration  5  /* Time ESP32 will go to sleep (in seconds) */ 
//3600 secs = 1 h,  1800 secs = 30 mins
//Definitions

//Constants

//Constants


//Global Variables (sorry james)
int counter = 0;
//Global Variables 


void initialiseSleep() { //Function for deep sleep mode
  Serial.begin(115200);
  delay(500); //Take some time to open up the Serial Monitor


  esp_sleep_enable_timer_wakeup(sleep_duration * uS_to_S_factor); //Wake up after defined number of seconds
  Serial.println("ESP32 to sleep for every " + String(sleep_duration) + " Seconds"); //Print how long the sleep is for

  Serial.println("Going to sleep now");
  Serial.flush();
  esp_deep_sleep_start();

}

void initialiseLora (){ //Function to setup LoRa in the correct way
  
  while (!Serial);
  
  LoRa.setPins(18,14,26); //Need to put the relevant pins (May beed to be changed) (ss,reset,dio0)
  if (!LoRa.begin(868E6)) { //Start LoRa at 868MHz
    Serial.println("Starting LoRa failed!"); //If this fails write it to serial monitor
    while (1);
 
}
   LoRa.setTxPower(20); //MAX POWER
}

void sendPacket() { //This is just for testing purposes (must be changed to take actual values)
   Serial.print("Sending packet: "); //Print this to the 
   Serial.println(counter);
    // Packet to be sent
   LoRa.beginPacket();
   LoRa.print("Testing");
   LoRa.print(counter);
   LoRa.endPacket();
   counter++;
   // Increase our counter by 1
   delay(5000); //5 second delay
  }


void receivePacket() {
    // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());

    delay(5000); //5 second delay
  }
}


void setup() {

  Serial.begin(9600);
  initialiseLora(); //Call the initialisation function
  

}

void loop() {

  Serial.print("RECEIVING MODE");
  receivePacket(); //Call function to receive data
  delay(500);
  

  Serial.print("TRANSMISSION MODE");
  sendPacket(); //Call function to send test packet
  delay(500);
  

  Serial.print("SLEEP MODE");
  initialiseSleep(); //Call deep sleep function

}
