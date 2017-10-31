/*---------------------------------------------------------------------------------------------

  Open Sound Control (OSC) library for the ESP8266/ESP32

  Example for sending messages from the ESP8266/ESP32 to a remote computer
  The example is sending "hello, osc." to the address "/test".

  This example code is in the public domain.

--------------------------------------------------------------------------------------------- */
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>
//////////////
//char data[10];
//////////////
char ssid[] = "KuroThesis";          // your network SSID (name)
char pass[] = "HOILAMGI";                    // your network password
String str;
char rangeValue[] = "00000";
char rxValue[] = "00000";
int k; //State for sending message
WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(192,168,0,3);        // remote IP of your computer
const unsigned int outPort = 12000;          // remote port to receive OSC
const unsigned int localPort = 8888;        // local port to listen for OSC packets (actually not used for sending)

void setup() {
    Serial.begin(115200);

    // Connect to WiFi network
//    Serial.println();
//    Serial.println();
//    Serial.print("Connecting to ");
//    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
#ifdef ESP32
    Serial.println(localPort);
#else
    Serial.println(Udp.localPort());
#endif
    delay(5000);
}

void loop() 
{
  int i = 0;
  int b = 0;
      if (Serial.available()>0) 
      {
        //Read string from Pro mini
        str = Serial.readStringUntil('\n');
        //Serial.println(str.charAt(str.length()-1));
        //Set address pattern for osc message
        if (str.charAt(0) == '1')
          k = 1;
        else 
          k = 0;
        //Ranging value
        
        while (str.charAt(i+1) != '-')
        {
          rangeValue[i] = str.charAt(i+1);
          //Serial.println(rangeValue[i]);
          i++;
        }

        //Rx value
        Serial.println(rangeValue);
        for (i;i< str.length();i++)
        {
          rxValue[b] = str.charAt(i+1); 
          b++;
        }
        Serial.println(rxValue);
      }
      if(k == 1)
      {
        OSCMessage msg("/Anchor1");
        msg.add(rangeValue);
        msg.add(rxValue);
        Udp.beginPacket(outIp, outPort);
        msg.send(Udp);
        Udp.endPacket();
        msg.empty();
        delay(500);
      }
}      
//        OSCMessage msg("/test");
//        int i =0 ;
//        while (str.charAt(i) != '*')
//        {
//          msg.add(str.charAt(i));
//          i++;          
//        }
//        
//        //msg.add(Serial.read());
//        Udp.beginPacket(outIp, outPort);
//        msg.send(Udp);
//        Udp.endPacket();
//        //msg.getString(0, str, 20);
//        //Serial.println(str);
//        msg.empty();
//        delay(500);
