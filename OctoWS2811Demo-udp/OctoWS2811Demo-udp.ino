#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include<FastLED.h>
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

#define NUM_LEDS_PER_STRIP 100
#define NUM_STRIPS 1


CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5

void setup() {
  LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
  LEDS.setBrightness(33);
  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
  Serial.begin(115200);
  Serial.println("INIT");
}

void loop() {
  int packetSize = Udp.parsePacket();
    
  if(packetSize)
  {
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
  //    Udp.read(,UDP_TX_PACKET_MAX_SIZE);
  }
//  Serial.print("packetBuffer: ");
//  Serial.println(packetBuffer[0] + packetBuffer[1] + packetBuffer[2]);
//  static uint8_t hue = 0;
//  for(int i = 0; i < NUM_STRIPS; i++) {
//    for(int j = 0; j < NUM_LEDS_PER_STRIP; j++) {
//      leds[(i*NUM_LEDS_PER_STRIP) + j] = CRGB(0, 0, 255);
//    }
//  }

      for (int j = 0; j < NUM_LEDS_PER_STRIP; j++) {
        leds[j] = CRGB(packetBuffer[(j*3)],packetBuffer[(j*3)+1],packetBuffer[(j*3)+2]);
      }

//  // Set the first n leds on each strip to show which strip it is
//  for(int i = 0; i < NUM_STRIPS; i++) {
//    for(int j = 0; j <= i; j++) {
//      leds[(i*NUM_LEDS_PER_STRIP) + j] = CRGB::Red;
//    }
//  }

//  hue++;
  
  LEDS.show();
  delay(50);
//  LEDS.delay(10);
}
