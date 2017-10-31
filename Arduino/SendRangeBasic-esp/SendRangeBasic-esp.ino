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
int cc = 50;
//////////////
char ssid[] = "KuroThesis";          // your network SSID (name)
char pass[] = "HOILAMGI";                    // your network password
char str[8];
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
        //Serial.print(".");
    }
//    Serial.println("");
//
//    Serial.println("WiFi connected");
//    Serial.println("IP address: ");
//    Serial.println(WiFi.localIP());

//    Serial.println("Starting UDP");
    Udp.begin(localPort);
//    Serial.print("Local port: ");
//#ifdef ESP32
//    Serial.println(localPort);
//#else
//    Serial.println(Udp.localPort());
//#endif

}

void loop() {
    if(Serial.available())
    {
      cc = Serial.read();
    }
    OSCMessage msg("/test");
    
    msg.add(cc);
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.getString(0, str, 20);
    //Serial.println(str);
    msg.empty();
    delay(500);
}
