// tutorial link : https://randomnerdtutorials.com/esp8266-nodemcu-date-time-ntp-client-server-arduino/


/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-date-time-ntp-client-server-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>

SoftwareSerial NodeMCU_softserial(D1,D2);// Rx,Tx //

// Replace with your network credentials
const char *ssid     = "Galaxy S21 5G426a";
const char *password = "abir0123";
// how to configure in free wifi

// Define NTP Client to get time
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 21600;//utc +6
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);//need to check

//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  
  }

// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(utcOffsetInSeconds);//utcOffsetInSeconds

  // initiate a nodemcu object to send data to arduino
  NodeMCU_softserial.begin(115200);
}

void loop() {
  timeClient.update();

  time_t epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
  
  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime);  

  int currentHour = timeClient.getHours();
  Serial.print("Hour: ");
  Serial.println(currentHour);  

  int currentMinute = timeClient.getMinutes();
  Serial.print("Minutes: ");
  Serial.println(currentMinute); 
   
  int currentSecond = timeClient.getSeconds();
  Serial.print("Seconds: ");
  Serial.println(currentSecond);  

  String weekDay = weekDays[timeClient.getDay()];
  Serial.print("Week Day: ");
  Serial.println(weekDay);    

  //Get a time structure
  struct tm *ptm = gmtime ((time_t *)&epochTime); 

  int monthDay = ptm->tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);

  int currentMonth = ptm->tm_mon+1;
  Serial.print("Month: ");
  Serial.println(currentMonth);

  String currentMonthName = months[currentMonth-1];
  Serial.print("Month name: ");
  Serial.println(currentMonthName);

  int currentYear = ptm->tm_year+1900;
  Serial.print("Year: ");
  Serial.println(currentYear);

  //Print complete date:
  String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
  Serial.print("Current date: ");
  Serial.println(currentDate);

  Serial.println("");

  // sending data to arduino
  // time
  NodeMCU_softserial.print(currentHour);             NodeMCU_softserial.print("A");
  NodeMCU_softserial.print(currentMinute);           NodeMCU_softserial.print("B");         
  NodeMCU_softserial.print(currentSecond);           NodeMCU_softserial.print("C");

  // day, month, year
  NodeMCU_softserial.print(monthDay);                 NodeMCU_softserial.print("D");
  NodeMCU_softserial.print(currentMonth);            NodeMCU_softserial.print("E");
  NodeMCU_softserial.print(currentYear);             NodeMCU_softserial.print("F");

  NodeMCU_softserial.print(timeClient.getDay());             NodeMCU_softserial.print("G");

  NodeMCU_softserial.print("\n");   

  delay(2000);
}
