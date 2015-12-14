#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include<FastLED.h>
// Lucas Morgan - www.enviral-design.com //

#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008

#define UDP_TX_PACKET_MAX_SIZE 1522

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10, 0, 1, 155);

unsigned int plafondPort1 = 9155;      // local port to listen on
unsigned int plafondPort2 = 9165;      // local port to listen on

// buffers for receiving and sending data
char packetBufferP1[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char packetBufferP2[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP UdpP1;
EthernetUDP UdpP2;

#define NUM_LEDS_PER_STRIP 504
#define NUM_STRIPS 4

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5

void setup() {
  LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
  LEDS.setBrightness(33);
  
  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  UdpP1.begin(plafondPort1);
  UdpP2.begin(plafondPort2);
  Serial.begin(115200);
  Serial.println("INIT");
}

void loop() {
  int packetSizeP1 = UdpP1.parsePacket();
  int packetSizeP2 = UdpP2.parsePacket();
  if(packetSizeP1)
  {
    UdpP1.read(packetBufferP1,UDP_TX_PACKET_MAX_SIZE);
  }
  if(packetSizeP2)
  {
    UdpP2.read(packetBufferP2,UDP_TX_PACKET_MAX_SIZE);
  }
  Serial.println(packetBufferP1);
  
  for(int i = 0; i < NUM_STRIPS; i++) {
    for(int j = 0; j < NUM_LEDS_PER_STRIP; j++) {
      if(i == 3) {
        if(j < 490)
          leds[(i*NUM_LEDS_PER_STRIP) + j] = CRGB(packetBufferP1[(j*3)],packetBufferP1[(j*3)+1],packetBufferP1[(j*3)+2]);
        else
          leds[(i*NUM_LEDS_PER_STRIP) + j] = CRGB(packetBufferP2[(j*3)],packetBufferP2[(j*3)+1],packetBufferP2[(j*3)+2]);
      }
      else
        leds[(i*NUM_LEDS_PER_STRIP) + j] = CRGB(0, 255, 0);
    }
  }
      
  LEDS.show();
  delay(50);
//  LEDS.delay(10);
}
