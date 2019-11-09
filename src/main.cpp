/*
 * Copyright (c) 2018, circuits4you.com
 * All rights reserved.
 * Create a TCP Server on ESP8266 NodeMCU. 
 * TCP Socket Server Send Receive Demo
*/

#include <ESP8266WiFi.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "HelloArduino.h"

#define SendKey 0 //Button to send data Flash BTN on NodeMCU

int port = 8888; //Port number
WiFiServer server(port);

int count = 0;
bool isConnected = false;
//=======================================================================
//                    Power on setup
//=======================================================================
void setup()
{
  Serial.begin(115200);
  pinMode(SendKey, INPUT_PULLUP); //Btn to send data
  Serial.println();
  Serial.println(getHelloArduino());

  WiFiManager wifiManager;

  isConnected = wifiManager.autoConnect("NodeMCU", "nopassword");

  if (!isConnected)
    return;

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.print("Open Telnet and connect to IP:");
  Serial.print(WiFi.localIP());
  Serial.print(" on port ");
  Serial.println(port);
}
//=======================================================================
//                    Loop
//=======================================================================

void loop()
{
  if (!isConnected)
    return;

  WiFiClient client = server.available();

  if (client)
  {
    if (client.connected())
    {
      Serial.println("Client Connected");
    }

    while (client.connected())
    {
      while (client.available() > 0)
      {
        // read data from the connected client
        Serial.write(client.read());
      }
      //Send Data to connected client
      while (Serial.available() > 0)
      {
        client.write(Serial.read());
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
//=======================================================================