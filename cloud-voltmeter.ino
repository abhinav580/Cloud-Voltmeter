#include <SoftwareSerial.h>
SoftwareSerial mySerial(12, 13); // RX, TX

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"          //https://github.com/tzapu/WiFiManager

int count=0,i,m,j,k;
int data;
int outputpin= A0;//ds18b20 


//////////////////////////////////////// ALL DECLARATIONS for CLOUD //////////////////////////////
const char* host = "api.thingsio.ai";                                 // OR host = devapi2.thethingscloud.com
const char* post_url = "/devices/deviceData";       // OR /api/v2/thingscloud2/_table/data_ac
const char* time_server = "baas.thethingscloud.com";             //this is to convert timestamp
const int httpPort = 80;

char timestamp[10];

WiFiClient client;
  

/////////////////////////////////////// TIMESTAMP CALCULATION function///////////////////////////////////////
int GiveMeTimestamp()
{
  unsigned long timeout = millis();

  while (client.available() == 0)
  {
    if (millis() - timeout > 50000)
    {
      client.stop();
      return 0;
    }
  }

while (client.available())
      {
        String line = client.readStringUntil('\r');                    //indexOf() is a funtion to search for smthng , it returns -1 if not found
        int pos = line.indexOf("\"timestamp\"");                       //search for "\"timestamp\"" from beginning of response got and copy all data after that , it'll be your timestamp
        if (pos >= 0)                                                     
        {
          int j = 0;
          for(j=0;j<10;j++)
          {
            timestamp[j] = line[pos + 12 + j];
          }
        }
      }
}  
////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{
  Serial.begin(115200);     //(19200,SERIAL_8E1) - data size = 8 bits , parity = Even , stop bit =  1bit
mySerial.begin(115200);
  WiFiManager wifiManager;
   WiFi.begin("abhi","abhi@8051");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

} 


void loop() 
{
  int analogValue = analogRead(outputpin);
{
 
  
/////////////////////////////////////// SEND THE QUERY AND RECEIVE THE RESPONSE///////////////////////  



        data=(analogValue/1024.0) *3300;
        Serial.print("volt: ");
        Serial.println(data);


  Serial.print("connecting to ");
  Serial.println(host);                          //defined upside :- host = devapi2.thethingscloud.com or 139.59.26.117

///////////////////////////////////// TIMESTAMP CODE SNIPPET /////////////////////////
Serial.println("inside get timestamp\n");
  if (!client.connect(time_server, httpPort)) 
  {
    return;                                                        //*-*-*-*-*-*-*-*-*-*
  }

  client.println("GET /api/timestamp HTTP/1.1");                            //Whats this part doing, i didnt get
  client.println("Host: baas.thethingscloud.com");
  client.println("Cache-Control: no-cache");
  client.println("Postman-Token: ea3c18c6-09ba-d049-ccf3-369a22a284b8");
  client.println();

GiveMeTimestamp();                        //it'll call the function which will get the timestamp response from the server
Serial.println("timestamp receieved");
Serial.println(timestamp);
///////////////////////////////////////////////////////////////////////////////

// Use WiFiClient class to create TCP connections
  if (!client.connect(host, httpPort))            //host = devapi2.thethingscloud.com , port = 80
  {
    Serial.println("connection failed");                  // *-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-
    return;
  }
  
  client.print("Content-Length: ");
  client.println(); 

  unsigned long timeout = millis();
  while (client.available() == 0) 
  {
    if (millis() - timeout > 50000) 
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  Serial.println("***********************************************");
  Serial.println();
  Serial.println("closing connection");

  Serial.println("inside ThingsCloudPost");

 
  String PostValue = "{\"device_id\": 1234573, \"slave_id\": 2";
         PostValue = PostValue + ",\"dts\":" +timestamp;
   PostValue = PostValue +",\"data\":{\"mvolt\":" + data +"}"+"}";
  
  
  Serial.println(PostValue);

//////////////////////////////// try to connect to server again and POST the data on the cloud //////////////////////////
  if (!client.connect(host, httpPort)) 
  {
    return;
  }

  client.print("POST ");
  client.print(post_url);               /// POST api/device-datas         HTTP/1.1     Host: baas.thethingscloud.com      Content-Type: application/json        Cache-Control: no-cache
  client.println(" HTTP/1.1");           //Authorization:          Content-Length: 
  client.print("Host: ");
  client.println(host);
  client.println("Content-Type: application/json");
  client.println("Cache-Control: no-cache");
  client.print("Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.IjViZWM0Y2JhNDAyYjlkNGI5MDdjNGYyZiI.k1p_-PZXEEJd4EBgPth3I2UQTkTRsEaXEiBl-hAsASo");
  client.println();
  client.print("Content-Length: ");
  client.println(PostValue.length());
  client.println();
  client.println(PostValue);
  
//////////////////////////////////POSTING the data on to the cloud is done and now get the response form cloud server//////////////////
  while (client.available() == 0) 
  {
    if (millis() - timeout > 50000) 
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  Serial.println("Response From Server");
  while(client.available())
  { 
    String line2 = client.readStringUntil('\r');   
    Serial.print(line2);
    
  }
    
Serial.println("//////////////////////    THE END     /////////////////////");
delay(3000);
}
}
          
