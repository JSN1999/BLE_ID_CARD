#include <ESP8266WiFi.h>// valid for both node-mcu and esp8266-01
#include <WiFiClientSecure.h>
/* Only required for ESp8266-01
#include <SoftwareSerial.h>
SoftwareSerial mySerial(GPIO0,GPIO2); //TX.RX */ 
const char* ssid = "WIFI_NAME";// Enter the name of Wifi-Router with whom you wanna connect
const char* password = WIFI_Password";// Enter the Router Password to build the connection 
char rx_byte1=0,rx_byte2=0,rx_byte3=0;
String value1="",value2="",value3="";
const char* host = "maker.ifttt.com"; //if using third party app for developing an applet here using IFTTT.com applets
const int httpsPort = 443; // if data to be sent is under http use 80, or if https then use 443


// SHA1 fingerprint of the certificate
const char* fingerprint = "aa 75 cb 41 2e d5 f9 97 ff 5d a0 8b 7d ac 12 21 08 4b 00 8c";//Unique for every page this for example
//Not necessary in code but just for verifying that it is connected to the right link
void setup() {
  
  Serial.begin(9600);
  /*Baud Rate , either 9600 or 115200 but 115200 is preferred as it is faster
  9600 baud rate is used as many HC-05 i.e. bluetooth module are not flashed to work for 115200
  Can be updated using AT commands to 1115200
  */
  while(!mySerial){} //for node mcu use Serial only , other one not required
  while(mySerial.available()){
    while(rx_byte1="/0"){
    rx_byte1=mySerial.read();
    value1+=r_byte1;}    
    Serial.write(value1));}
  while(!mySerial){}
  while(mySerial.available()){
    while(rx_byte2="/0"){
    rx_byte2=mySerial.read();
    value2+=r_byte2;}    
    Serial.write(value2));}
    while(!mySerial){}
  while(mySerial.available()){
    while(rx_byte3="/0"){
    rx_byte3=mySerial.read();
    value3+=r_byte1;}    
    Serial.write(value3));}
    
    
  while(!Serial){}
  Serial.println();
  Serial.print("connecting to ");
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

  if (client.verify(fingerprint, host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }

  String url = "/trigger/{event_name}/with/key/{Key}";//here give the link of your resource of applet
  
  // Usually of the form /trigger/test_data/with/key/oMUA5XRBNlATGHt7Ig_3RnUl3a-1kkayQC4C5D5GAwm 
  //(Key is not correct, given to just explain the syntax)
  Serial.print("requesting URL: ");
  
  Serial.println(url);

  String jsonObject = String("{\"value1\":\"") + value1 + "\",\"value2\":\"" 
                      + value2 + "\",\"value3\":\"" + value3 + "\"}";
  //for free acoount values to be passed at once limited to three
  //you may replicate the query to other records
  
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
  
  Serial.println("closing connection");
}

void loop() {
}
