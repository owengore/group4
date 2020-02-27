//RTC_DATA_ATTR int bootCount = 0; //Print this before a variable that needs to stay active through deep sleep

#define uS_to_S_factor 1000000ULL  /* Conversion factor for micro seconds to seconds */

//To be changed to 1 hour or 30 mins after testing
#define sleep_duration  5  /* Time ESP32 will go to sleep (in seconds) */
//3600 secs = 1 h,  1800 secs = 30 mins

void initialiseSleep() {
  Serial.begin(115200);
  delay(500); //Take some time to open up the Serial Monitor


  esp_sleep_enable_timer_wakeup(sleep_duration * uS_to_S_factor); //Wake up after defined number of seconds
  Serial.println("ESP32 to sleep for every " + String(sleep_duration) + " Seconds"); //Print how long the sleep is for

  Serial.println("Going to sleep now");
  Serial.flush();
  esp_deep_sleep_start();

}

void setup() {
  initialiseSleep();
}



void loop() {
  //This is not going to be called
}
