
#include "ESP8266WiFi.h"
const int RSSI_MAX =-50;// define maximum strength of signal in dBm
const int RSSI_MIN =-100;// define minimum strength of signal in dBm


// start of settings for LCD1602 with I2C
#include <LiquidCrystal.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal lcd(D6, D5, D1, D2, D3, D4); 
// end of settings for LCD1602 with I2C

int count =0;

int scanDelayTime = 1000;
int wiFiDisplayTime = 3000;
#define LED D0 
void setup() {
  // Set WiFi to station mode and 
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();//disconnect from an AP if it was previously connected
    
  lcd.begin(16, 2);  
  lcd.print("NodeMCU ESP 8266");
  lcd.setCursor(0,1);
  lcd.print("Initiate AP Scan");  
  delay(2000); 
}


void loop() {

  int n = WiFi.scanNetworks();
  lcd.clear();// clear previous values from screen
  lcd.print("scan done");     
  if (n == 0) {
    lcd.print("No WiFI found");   
  } else {
    lcd.setCursor(0,1);
    lcd.print(n);
    lcd.print( " AP found");
    for (int i = 0; i < n; ++i) {

      // Print SSID and RSSI for each network found
      lcd.clear();// clear previous values from screen
      lcd.setCursor(0,0);
      lcd.print(i+1);      
      lcd.print(":"); 
      lcd.print(WiFi.SSID(i));     
      lcd.setCursor(0,1);        
      lcd.print("Signal: ");      
      lcd.print(dBmtoPercentage(WiFi.RSSI(i))); 
      lcd.print("%"); 
      delay(wiFiDisplayTime);
    }
  }  

  delay(scanDelayTime); 
}// loop end

int dBmtoPercentage(int dBm)
{
  int quality;
    if(dBm <= RSSI_MIN)
    {
        quality = 0;
    }
    else if(dBm >= RSSI_MAX)
    {  
        quality = 100;
    }
    else
    {
        quality = 2 * (dBm + 100);
   }

     return quality;
         digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500); // wait for 1 second.
}//dBmtoPercentage
 
