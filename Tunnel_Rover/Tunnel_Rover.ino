#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <Hash.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#error "Board not found"
#endif
#include <Servo.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

// ip--> 192.168.4.1


int cam=0;

//Pins

#define IN_1  15  //GPIO 15 == D8        // L298N in1 motors Right           GPIO15(D8)
#define IN_2  13  //GPIO 13 == D7        // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2   //GPIO 02 == D4        // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0   //GPIO 00 == D3        // L298N in4 motors Left            GPIO0(D3)


#define ServoPort3 D5 //GPIO 14 == D5
#define ServoPort4 D6 //GPIO 12 == D6
#define ServoPort1 D2 //GPIO 04 == D2   //cam


#define led D0 //GPIO 16 == D0

#define DHTTYPE    DHT11 
#define DHTPIN   D1   //GPIO 05 == D1 




const char* PARAM_INPUT_1 = "value";
String sliderValue_1 ="0";

/*
const char* PARAM_INPUT_2 = "value";
String sliderValue_2 ="0";

const char* PARAM_INPUT_3 = "value";
String sliderValue_3 ="0";
*/

//----------------------------------------------------------------

int temp=90;

int pos=0;

Servo servo1,servo2,servo_cam;
//----------------------------------------------------------------

DHT dht(DHTPIN, DHTTYPE);
float t = 0.0;
float h = 0.0;
unsigned long previousMillis = 0;    //we store last time DHT was updated


const long interval = 10; // Updates DHT readings every 10 seconds
//----------------------------------------------------------------

#include "web_html.h"



#include <ESPAsyncWebServer.h>

AsyncWebServer server(80); // server port 80 // sending like http // if we use 435 we can use html in https

void notFound(AsyncWebServerRequest *request){
  request->send(404, "text/plain", "Page Not found");
}



String processor(const String& var){
  //Serial.println(var);
  if (var == "Suspension"){
    return sliderValue_1;
  }
  else if(var == "TEMPERATURE"){
    return String(t);
  }
  else if(var == "HUMIDITY"){
    return String(h);
  }
  return String();


}

//------------------------------------SSID & PASSWORD-------------------------------------------------------------------------------------------
const char* ssid     = "Lambogini";
const char* password = "ojith@1234";



//----------------------------------------------------------------------setup-------------------------------------------------------------------
void setup(void){
  Serial.begin(115200);
  
  dht.begin();
  
  pinMode(IN_1,OUTPUT);
  pinMode(IN_2,OUTPUT);
  pinMode(IN_3,OUTPUT);
  pinMode(IN_4,OUTPUT);

  pinMode(led,OUTPUT);


  servo1.attach(ServoPort3);
  servo2.attach(ServoPort4);
  servo_cam.attach(ServoPort1);

   servo1.write(0);
  servo2.write(0);
  
  WiFi.softAP(ssid, password);
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());Serial.print("Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");

/*
  if (MDNS.begin("ESP")) { //esp.local/
    Serial.println("MDNS responder started");
  }
*/
//----------------------------------------------------------------------main_page-------------------------------------------------------------------
  server.on("/", [](AsyncWebServerRequest * request){ 
   
  request->send_P(200, "text/html", webpage);
  });
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", webpage, processor);
  });

//----------------------------------------------------------------------forward-------------------------------------------------------------------
   server.on("/forward", HTTP_GET, [](AsyncWebServerRequest * request){
     
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      Serial.println("Forward");
  
  request->send_P(200, "text/html", webpage);
  });

//----------------------------------------------------------------------right-------------------------------------------------------------------  
  server.on("/right", HTTP_GET, [](AsyncWebServerRequest * request){

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      Serial.println("Right");
    
  request->send_P(200, "text/html", webpage);
  });

//----------------------------------------------------------------------left-------------------------------------------------------------------
    server.on("/left", HTTP_GET, [](AsyncWebServerRequest * request){ 
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      Serial.println("Left");    
  
  request->send_P(200, "text/html", webpage);
  });

//----------------------------------------------------------------------backward-------------------------------------------------------------------
 
  server.on("/backward", HTTP_GET, [](AsyncWebServerRequest * request){ 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      Serial.println("backward");
  
  request->send_P(200, "text/html", webpage);
  });

//----------------------------------------------------------------------stop-------------------------------------------------------------------
 
  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest * request){
     
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      Serial.println("Stop");
     request->send_P(200, "text/html", webpage);
  });

//-----------------------cam_adjesment---------------------------------------------------------------------------------------------------------------

server.on("/cam00", HTTP_GET, [](AsyncWebServerRequest * request){

     servo_cam.write(0);
     cam=0;
     Serial.println(cam);
      
     request->send_P(200, "text/html", webpage);
  });

server.on("/cam15", HTTP_GET, [](AsyncWebServerRequest * request){

     servo_cam.write(15);
     cam=15;
     Serial.println(cam);
     request->send_P(200, "text/html", webpage);
  });

server.on("/cam30", HTTP_GET, [](AsyncWebServerRequest * request){

     servo_cam.write(30);
     cam=30;
      Serial.println(cam);
     request->send_P(200, "text/html", webpage);
  });

server.on("/cam45", HTTP_GET, [](AsyncWebServerRequest * request){

     servo_cam.write(45);
     cam=45; 
     Serial.println(cam);
     request->send_P(200, "text/html", webpage);
  });
server.on("/cam60", HTTP_GET, [](AsyncWebServerRequest * request){

     servo_cam.write(60);
     cam=60;
      Serial.println(cam);
     request->send_P(200, "text/html", webpage);
  });
server.on("/cam75", HTTP_GET, [](AsyncWebServerRequest * request){

     servo_cam.write(75);
     cam=75;
     Serial.println(cam);
     request->send_P(200, "text/html", webpage);
  });
server.on("/cam90", HTTP_GET, [](AsyncWebServerRequest * request){

     servo_cam.write(90);
     cam=90;
     Serial.println(cam);
     request->send_P(200, "text/html", webpage);
  });
server.on("/cam105", HTTP_GET, [](AsyncWebServerRequest * request){

     servo_cam.write(105);
     cam=105; 
     Serial.println(cam);
     request->send_P(200, "text/html", webpage);
  });
  server.on("/cam120", HTTP_GET, [](AsyncWebServerRequest * request){

     servo_cam.write(120);
      cam=120;
      Serial.println(cam);
     request->send_P(200, "text/html", webpage);
  });
   server.on("/cam135", HTTP_GET, [](AsyncWebServerRequest * request){

     servo_cam.write(135);
     cam=135;
     Serial.println(cam);
     request->send_P(200, "text/html", webpage);
  });
   server.on("/cam150", HTTP_GET, [](AsyncWebServerRequest * request){

     servo_cam.write(150);
     cam=150; 
     Serial.println(cam);
     request->send_P(200, "text/html", webpage);
  });
  server.on("/cam165", HTTP_GET, [](AsyncWebServerRequest * request){

     servo_cam.write(165);
      cam=165;
     Serial.println(cam);
     request->send_P(200, "text/html", webpage);
  });
   server.on("/cam180", HTTP_GET, [](AsyncWebServerRequest * request){

     servo_cam.write(180);
     cam=180;
     Serial.println(cam);
      
     request->send_P(200, "text/html", webpage);
  });
//--------------------------------------------------------------------------light----------------------------------------------------------------

server.on("/lightoff", HTTP_GET, [](AsyncWebServerRequest * request){

     digitalWrite(led, HIGH);
     Serial.println("LED ON");
      
     request->send_P(200, "text/html", webpage);
  });
  
server.on("/lighton", HTTP_GET, [](AsyncWebServerRequest * request){

     digitalWrite(led, LOW);
      Serial.println("LED OFF");
     request->send_P(200, "text/html", webpage);
  });
  
//----------------------------------------------------------------------DHT_11-------------------------------------------------------------------
server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(t).c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(h).c_str());
  });

//----------------------------------------------------------------------servo_1(Suspension)-------------------------------------------------------------------
server.on("/slider_1", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage_1;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage_1 = request->getParam(PARAM_INPUT_1)->value();
      sliderValue_1 = inputMessage_1;
      
      int input=sliderValue_1.toInt();
      Serial.print("suspention val ");
      Serial.println(input);
      suspention(input); 
      
      Serial.println("");
    }else {
      inputMessage_1 = "No message sent";
    }
    Serial.println(inputMessage_1);
    request->send(200, "text/plain", "OK");
  });



//----------------------------------------------------------------------webserver-------------------------------------------------------------------
  server.onNotFound(notFound);

  server.begin();  // starting webserver
}

void loop(void){
    unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    float newT = dht.readTemperature();
    
    if (isnan(newT)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      t = newT;
      Serial.println(t);
    }
    // Read Humidity
    float newH = dht.readHumidity();
    // if humidity read failed, don't change h value 
    if (isnan(newH)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      h = newH;
      Serial.println(h);
    }
  }
}

void suspention(int input){
  /*
  if(temp<input){
    Serial.println("suspention up");
    for(int i=0;i<=input;i++){

      
      servo1.write(i);
      
      Serial.print("servo 1 -----> ");
      Serial.println(i);
      
      pos=180-i;
      
      
     
      servo2.write(pos);
      
      Serial.print("servo 2 ----> ");
      Serial.println(pos);
      delay(200);
    }  

    temp=input;
    Serial.print("temp val --------->");
      Serial.println(temp);
      
  } else if(temp>input){
    Serial.println("suspention down");
    for(int j=input;j>=0;j--){
    
    servo1.write(j);

    Serial.print("servo 1 =");
    Serial.println(j);
      
    servo2.write(pos);
    Serial.print("servo 2 =");
    Serial.println(pos);
    pos+=1;
    delay(200);
    }
      temp=input;
      Serial.print("temp val =");
      Serial.println(temp);
    
  }
  */

    if(temp<input){
    Serial.println("suspention up");
    {  
      servo1.write(input);
      
      Serial.print("servo 1 -----> ");
      Serial.println(input);
      
      pos=180-input;
      
      servo2.write(pos);
      
      Serial.print("servo 2 ----> ");
      Serial.println(pos);
      delay(200);
    }  

    temp=input;
    Serial.print("temp val --------->");
      Serial.println(temp);
      
  } else if(temp>input){
    Serial.println("suspention down");
    {
    servo1.write(input);

    Serial.print("servo 1 =");
    Serial.println(input);
      
    servo2.write(pos);
    Serial.print("servo 2 =");
    Serial.println(pos);
    pos+=1;
    delay(200);
    }
      temp=input;
      Serial.print("temp val =");
      Serial.println(temp);
    
  }

}
