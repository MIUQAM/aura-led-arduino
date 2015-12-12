// Lucas Morgan - www.enviral-design.com //

#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008

#define UDP_TX_PACKET_MAX_SIZE 6020

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10, 0, 1, 155);

unsigned int localPort = 9155;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
//char  ReplyBuffer[] = "acknowledged";       // a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include<FastLED.h>

// ------------ Change these as neccesary -----------//
#define NUM_LEDS_PER_STRIP 100
#define NUM_STRIPS 1

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];
const int numOfBytes = NUM_LEDS_PER_STRIP * NUM_STRIPS * 3;
const int numLeds = NUM_LEDS_PER_STRIP * NUM_STRIPS;
char inputBuffer[numOfBytes];

// ------------------- Setup -------------------- //
void setup() {
  LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
  LEDS.setBrightness(255);
  delay(500);
  Serial.begin(115200);
  Serial.println("INIT");
  Serial.setTimeout(500);
  LEDS.show();
}

// ------------------- Main Loop -------------------- //
void loop() {
  int packetSize = Udp.parsePacket();
//  int colorPacket = 0;
  if(packetSize)
  {
//    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    Udp.read(inputBuffer,UDP_TX_PACKET_MAX_SIZE);
  }
  Serial.print("UDP: ");
  Serial.println(inputBuffer);
//  if(Serial.available() > 0) {
//    Serial.readBytes(inputBuffer, numOfBytes);
//  }
      for (int j = 0; j < numLeds; j++) {
        leds[j] = CRGB(inputBuffer[(j*3)],inputBuffer[(j*3)+1],inputBuffer[(j*3)+2]);
      }
      LEDS.show();
}
