#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
// #include <string>
// WIFI Manager ========================
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "SPIFFS.h"

#define RELE_1 25
#define RELE_2 26
#define RELE_ON LOW
#define RELE_OFF HIGH
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
// const char* PARAM_INPUT_3 = "ip";
// const char* PARAM_INPUT_4 = "gateway";


//Variables to save values from HTML form
String ssid;
String pass;
// String ip;
// String gateway;

// File paths to save input values permanently
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
// const char* ipPath = "/ip.txt";
// const char* gatewayPath = "/gateway.txt";

IPAddress localIP;
//IPAddress localIP(192, 168, 1, 200); // hardcoded

// Set your Gateway IP address
IPAddress localGateway;
//IPAddress localGateway(192, 168, 1, 1); //hardcoded
IPAddress subnet(255, 255, 0, 0);

// Timer variables
unsigned long previousMillis = 0;
const long interval = 10000;  // interval to wait for Wi-Fi connection (milliseconds)

// Set LED GPIO
// const int ledPin = 2;
// Stores LED state

String ledState1;
String ledState2;

// Initialize SPIFFS
void initSPIFFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");
}

// Read File from SPIFFS
String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
    return String();
  }
  
  String fileContent;
  while(file.available()){
    fileContent = file.readStringUntil('\n');
    break;     
  }
  return fileContent;
}

// Write file to SPIFFS
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- frite failed");
  }
}

// Initialize WiFi
bool initWiFi() {
  if(ssid == "") {
    Serial.println("Undefined SSID or IP address.");
    return false;
  }

  WiFi.mode(WIFI_STA);
  // localIP.fromString(ip.c_str());
  // localGateway.fromString(gateway.c_str());


  if (!WiFi.config(localIP, localGateway, subnet)){
    Serial.println("STA Failed to configure");
    return false;
  }
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("Connecting to WiFi...");

  unsigned long currentMillis = millis();
  previousMillis = currentMillis;

  while(WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Failed to connect.");
      return false;
    }
  }

  Serial.println(WiFi.localIP());
  return true;
}

// Replaces placeholder with LED state value
String processor(const String& var) {
  if(var == "STATE1") {
    if (digitalRead(RELE_1) == RELE_ON) {
      ledState1 = "ON";
    } else {
      ledState1 = "OFF";
    }
    return ledState1;
  }
  if(var == "STATE2") {
    if (digitalRead(RELE_2) == RELE_ON) {
      ledState2 = "ON";
    } else {
      ledState2 = "OFF";
    }
    return ledState2;
  }
  return String();
}
// WIFI Manager ========================
const char* mqttServer = "mqtt.rzk.com.ua";
const int mqttPort = 1883;
const char* mqttUser = "admin";
const char* mqttPassword = "admin";
const char* mqttTopicRele = "home/rele";
const char* mqttTopicReleStatus = "home/rele/status";
WiFiClient espClient;
PubSubClient client(espClient);
//--------- WIFI -------------------------------------------
// void wifi_connect() {
//   Serial.print("Starting connecting WiFi.");
//   delay(10);
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("WiFi connected");
//   Serial.println("IP address: ");
//   Serial.println(WiFi.localIP());
// }
//------------------ MQTT ----------------------------------
void mqtt_send_lamp_status() {
  char out_str[40] = "";
  int val_1 = digitalRead(RELE_1);
  int val_2 = digitalRead(RELE_2);
  Serial.printf("Sending LAMP_1 status: ");
  if(val_1 == RELE_OFF) {
    Serial.println("OFF");
    strcat(out_str, "OFF");
    // client.publish(mqttTopicRele, "OFF_1");
  } else {
    Serial.println("ON");
    strcat(out_str, "ON");
    //client.publish(mqttTopicRele, "ON_1");
  }
  Serial.printf("Sending LAMP_2 status: ");
  if(val_2 == RELE_OFF) {
    Serial.println("OFF");
    strcat(out_str, ",OFF");
    // client.publish(mqttTopicRele, "OFF_2");
  } else {
    Serial.println("ON");
    strcat(out_str, ",ON");
    //client.publish(mqttTopicRele, "ON_2");
  }
  client.publish(mqttTopicReleStatus, out_str);
}

void callback(char* topic, byte* payload, unsigned int length) {

    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    String byteRead = "";
    Serial.print("Message: ");
    for (int i = 0; i < length; i++) {
        byteRead += (char)payload[i];
    }    
    Serial.println(byteRead);

    if (byteRead == "OFF_1") {
        Serial.println("LAMP_1 OFF");
        digitalWrite(RELE_1, RELE_OFF);
    }

    if (byteRead == "ON_1") {
        Serial.println("LAMP_1 ON");
        digitalWrite(RELE_1, RELE_ON);
    }

    if (byteRead == "OFF_2") {
        Serial.println("LAMP_2 OFF");
        digitalWrite(RELE_2, RELE_OFF);
    }

    if (byteRead == "ON_2") {
        Serial.println("LAMP_2 ON");
        digitalWrite(RELE_2, RELE_ON);
    }
    // update status
    mqtt_send_lamp_status();
    // if (byteRead == "status") {
    //   mqtt_send_lamp_status();
    // }
    Serial.println();
    Serial.println(" — — — — — — — — — — — -");

}

void mqtt_setup() {
  client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
    Serial.println("Connecting to MQTT…");
    while (!client.connected()) {        
        String clientId = "ESP32Client-";
        clientId += String(random(0xffff), HEX);
        if (client.connect(clientId.c_str(), mqttUser, mqttPassword)) {
          Serial.println("connected");
        } else {
          Serial.print("failed with state  ");
          Serial.println(client.state());
          delay(2000);
        }
    }
    mqtt_send_lamp_status();
    client.subscribe(mqttTopicRele);
    // client.subscribe(mqttTopicReleStatus);
}

void setup_ios() {
  pinMode(RELE_1, OUTPUT);
  pinMode(RELE_2, OUTPUT);
  digitalWrite(RELE_1, RELE_OFF);
  digitalWrite(RELE_2, RELE_OFF);
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  // wifi manager
  initSPIFFS();

  // Set GPIO 2 as an OUTPUT
  // pinMode(ledPin, OUTPUT);
  // digitalWrite(ledPin, LOW);
  
  // Load values saved in SPIFFS
  ssid = readFile(SPIFFS, ssidPath);
  pass = readFile(SPIFFS, passPath);
  // ip = readFile(SPIFFS, ipPath);
  // gateway = readFile (SPIFFS, gatewayPath);
  Serial.println(ssid);
  Serial.println(pass);
  // Serial.println(ip);
  // Serial.println(gateway);

  if(initWiFi()) {
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });
    server.serveStatic("/", SPIFFS, "/");
    
    // Route to set GPIO state to HIGH
    server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
      digitalWrite(RELE_1, RELE_ON);
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });

    server.on("^\\/rele\\/([0-9]+)\\/on$", HTTP_GET, [] (AsyncWebServerRequest *request) {
      String releNumber = request->pathArg(0);
      digitalWrite(releNumber.toInt(), RELE_ON);
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });

    server.on("^\\/sensor\\/([0-9]+)\\/action\\/([a-zA-Z0-9]+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String sensorNumber = request->pathArg(0);
        String action = request->pathArg(1);
        request->send(200, "text/plain", "Hello, sensor: " + sensorNumber + ", with action: " + action);
    });

    server.onNotFound(notFound);

    // Route to set GPIO state to LOW
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
      digitalWrite(RELE_1, RELE_OFF);
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });
    server.begin();
  } else {
    // Connect to Wi-Fi network with SSID and password
    Serial.println("Setting AP (Access Point)");
    // NULL sets an open Access Point
    WiFi.softAP("ESP-WIFI-MANAGER", NULL);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP); 

    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/wifimanager.html", "text/html");
    });
    
    server.serveStatic("/", SPIFFS, "/");
    
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
      int params = request->params();
      for(int i=0;i<params;i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->isPost()){
          // HTTP POST ssid value
          if (p->name() == PARAM_INPUT_1) {
            ssid = p->value().c_str();
            Serial.print("SSID set to: ");
            Serial.println(ssid);
            // Write file to save value
            writeFile(SPIFFS, ssidPath, ssid.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_INPUT_2) {
            pass = p->value().c_str();
            Serial.print("Password set to: ");
            Serial.println(pass);
            // Write file to save value
            writeFile(SPIFFS, passPath, pass.c_str());
          }
          // HTTP POST ip value
          // if (p->name() == PARAM_INPUT_3) {
          //   ip = p->value().c_str();
          //   Serial.print("IP Address set to: ");
          //   Serial.println(ip);
          //   // Write file to save value
          //   writeFile(SPIFFS, ipPath, ip.c_str());
          // }
          // // HTTP POST gateway value
          // if (p->name() == PARAM_INPUT_4) {
          //   gateway = p->value().c_str();
          //   Serial.print("Gateway set to: ");
          //   Serial.println(gateway);
          //   // Write file to save value
          //   writeFile(SPIFFS, gatewayPath, gateway.c_str());
          // }
          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      request->send(200, "text/plain", "Done. ESP will restart, connect to your router " + ssid);
      delay(3000);
      ESP.restart();
    });
    server.begin();
  }
  setup_ios();
  // wifi_connect();
  mqtt_setup();
}

void loop() {
  client.loop();
  unsigned long currentMillis = millis();
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
}