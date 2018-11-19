#include <ESP8266WiFi.h>// valid for both node-mcu and esp8266-01
#include <WiFiClientSecure.h>
 
const char* ssid = "JSN";// Enter the name of Wifi-Router with whom you wanna connect
const char* password = "jsnjsnjsn";// Enter the Router Password to build the connection 
String data1="",data2="",data3="";
const char* host = "maker.ifttt.com"; //if using third party app for developing an applet here using IFTTT.com applets
const int httpsPort = 443; // if data to be sent is under http use 80, or if https then use 443
void setup() {
  
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(1,OUTPUT);
  digitalWrite(1,LOW);
  digitalWrite(2,LOW);
  /*Baud Rate , either 9600 or 115200 but 115200 is preferred as it is faster
  9600 baud rate is used as many HC-05 i.e. bluetooth module are not flashed to work for 115200
  Can be updated using AT commands to 1115200
  */
  while(!Serial.available()){}
      // Send data only when you receive data:
   {
      data1 = Serial.readString();        //Read the incoming data & store into data
      Serial.print(data1);          //Print Value inside data in Serial monitor
      Serial.print("\n");        
      {digitalWrite(2,HIGH);
       delay(100);
       digitalWrite(2,LOW);
       delay(50);
      digitalWrite(2,HIGH);
       delay(100);
       digitalWrite(2,LOW);
       delay(50);
      digitalWrite(2,HIGH);
       delay(100);
       digitalWrite(2,LOW);
       delay(50);
      digitalWrite(2,HIGH);
       delay(100);
       digitalWrite(2,LOW);
       delay(50);
      
       }
          }
     while(!Serial.available()){}
      // Send data only when you receive data:
   {
      data2 = Serial.readString();        //Read the incoming data & store into data
      Serial.print(data2);          //Print Value inside data in Serial monitor
      Serial.print("\n");        
      digitalWrite(2,HIGH);
       delay(100);
       digitalWrite(2,LOW);
       delay(50);
      digitalWrite(2,HIGH);
       delay(100);
       digitalWrite(2,LOW);
       delay(50);
      digitalWrite(2,HIGH);
       delay(100);
       digitalWrite(2,LOW);
       delay(50);
      digitalWrite(2,HIGH);
       delay(100);
       digitalWrite(2,LOW);
       delay(50);
       
      }
while(!Serial.available()){}
      // Send data only when you receive data:
   {
      data3 = Serial.readString();        //Read the incoming data & store into data
      Serial.print(data3);          //Print Value inside data in Serial monitor
      Serial.print("\n");        
      digitalWrite(2,HIGH);
       delay(100);
       digitalWrite(2,LOW);
       delay(50);
      digitalWrite(2,HIGH);
       delay(100);
       digitalWrite(2,LOW);
       delay(50);
      digitalWrite(2,HIGH);
       delay(100);
       digitalWrite(2,LOW);
       delay(50);
      digitalWrite(2,HIGH);
       delay(100);
       digitalWrite(2,LOW);
       delay(50);
       
          }
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  digitalWrite(2,HIGH);
  delay(100);
  digitalWrite(2,LOW);
  
  String url = "/trigger/test_data/with/key/oMUA5XRBNlATGHt7Ig_3RnUl3a-10jNyQC4C5D5GAwm";//here give the link of your resource of applet
  
  // Usually of the form /trigger/test_data/with/key/oMUA5XRBNlATGHt7Ig_3RnUl3a-1kkayQC4C5D5GAwm 
  //(Key is not correct, given to just explain the syntax)
  Serial.print("requesting URL: ");
  
  Serial.println(url);
  String jsonObject = String("{\"value1\":\"") + data1 + "\",\"value2\":\"" 
                      + data2 + "\",\"value3\":\"" + data3 + "\"}";
  //for free acoount values to be passed at once limited to three
  //you may replicate the query to other records
  digitalWrite(2,HIGH);
  client.println(String("POST ") + url + " HTTP/1.1"); //not be changed, it is to be kept at HTTP/1.1 for both http and https
  client.println(String("Host: ") + host); 
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);            
  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  if(!!!client.available()) {
    Serial.println("No response...");
  }
  while(client.available()){
    Serial.write(client.read());//Gives the status after passing the values to website i.e. output shown on website
  }
  delay(50);
  digitalWrite(2,LOW);
  delay(50);
  digitalWrite(2,HIGH);
  delay(50);
  digitalWrite(2,LOW);
  delay(50);
  digitalWrite(2,HIGH);
  Serial.println("closing connection");
}
void loop() {
}
