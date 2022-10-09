#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <Wire.h>           
#include <LiquidCrystal_I2C.h> 


 #define FIREBASE_HOST "voice-based-notice-board-default-rtdb.firebaseio.com"  //Database link
 #define FIREBASE_AUTH "hWhes26LFnakkxeLPDneclih58N9iVLYekMOhzXC"  //Database secrate

 #define WIFI_SSID "IOT_NOTICE"      //Router name
 #define WIFI_PASSWORD "00000000"  //Router password

 FirebaseData loadData;
 FirebaseJson json;

 LiquidCrystal_I2C lcd(0x27,16,2);   


  String getNotice(){
  if (Firebase.getString(loadData, "/Notice")){
      return loadData.stringData();
    }
  }
 
 void setup()  
  {  
   lcd.init();      
   lcd.backlight();  


   pinMode(D4,OUTPUT);
  
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");

   lcd.setCursor(0,0);  
   lcd.print("WiFi Connecting");  
   lcd.setCursor(0,1);  
   lcd.print("Please wait...");

  
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(D4,0);
    Serial.print(".");
    delay(200);
    digitalWrite(D4,1);
    Serial.print(".");
    delay(200);
    
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
 
  }  

  String data="",x="",y="";
  int in=0;
  
 void loop()   
  {  
   
    data=getNotice(); 
    in=data.indexOf('=');
    x=data.substring(0,in);
    y=data.substring(in+1);
    dis("Notice: "+x,y);
    delay(200);
    

  }  


  void dis(String a, String text){
  unsigned int i=0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(a);
 
  lcd.setCursor(0, 1);
  while(text[i]!='\0'){
  lcd.print(text[i]);
   
   if(i>=14)
  {
      lcd.command(0x18); //Scrolling text to Right
  }
   delay(200);
   i++;
   } 
  }
  
