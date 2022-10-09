#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>



#define FIREBASE_HOST "voiceautomation-8d4cc-default-rtdb.asia-southeast1.firebasedatabase.app"  
#define FIREBASE_AUTH "jPTXvHEUTM1BnCgglW65n3hRwcUg1PbVuFfmjPXB"

#define WIFI_SSID "IOT_Voice"     
#define WIFI_PASSWORD "11111111" 


FirebaseData firebaseData,loadData;
FirebaseJson json;



//Receiving data
String readData(String field){
if (Firebase.getString(loadData, "/Load/"+field)){
    return loadData.stringData();
  }
}



void initFire(){
  pinMode(D4,OUTPUT);
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
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














void setup() {
  
  Serial.begin(9600);
  pinSet();
  initFire();

}



void pinSet(){
  pinMode(D6,OUTPUT);//Light
  pinMode(D7,OUTPUT);
  
}




void loop() {

  
    if(readData("Light")=="1"){
      
      Serial.print("Light is on ");
      digitalWrite(D7,1);
      
    }else{

      Serial.print("Light is off ");
      digitalWrite(D7,0);
      
    }


      
    if(readData("Pump")=="1"){
      
      Serial.println("Pump is on");
      digitalWrite(D6,1);
      
    }else{

      Serial.println("Pump is off");
      digitalWrite(D6,0);
      
    }


   
  
}
