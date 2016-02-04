#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include<FastLED.h>
// Lucas Morgan - www.enviral-design.com //

#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008

//#define UDP_TX_PACKET_MAX_SIZE 6020
#define UDP_TX_PACKET_MAX_SIZE 10000

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10, 0, 1, 111);

//unsigned int champiPort1 = 9151;      // Plafond part 1
//unsigned int champiPort2 = 9152;      // Plafond part 1
//unsigned int champiPort3 = 9153;      // Plafond part 1
unsigned int plafondPort1 = 9111;      // Plafond part 1
unsigned int plafondPort2 = 9112;      // Plafond part 2

// buffers for receiving and sending data
//char packetBufferC1[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char packetBuffer2[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
//char  ReplyBuffer[] = "acknowledged";       // a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
//EthernetUDP tabarnac;
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
//  tabarnac.begin(champiPort1);
  UdpP1.begin(plafondPort1);
  UdpP2.begin(plafondPort2);
  Serial.begin(115200);
  Serial.println("INIT");
}

void loop() {
//  int fuckYou = UdpC1.parsePacket()
  int packetSize = UdpP1.parsePacket();
  int packetSize2 = UdpP2.parsePacket();
  if(packetSize)
  {
    UdpP1.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
  }
  if(packetSize2)
  {
    UdpP2.read(packetBuffer2,UDP_TX_PACKET_MAX_SIZE);
  }
  Serial.println(packetBuffer);
  for(int i = 0; i < NUM_STRIPS; i++) {
    for(int j = 0; j < NUM_LEDS_PER_STRIP; j++) {
//      leds[(i*NUM_LEDS_PER_STRIP) + j] = CRGB(255, 255 ,255);
     
      if(j < 490)
        leds[(i*NUM_LEDS_PER_STRIP) + j] = CRGB(packetBuffer[(j*3)],packetBuffer[(j*3)+1],packetBuffer[(j*3)+2]);
      else
        leds[(i*NUM_LEDS_PER_STRIP) + j] = CRGB(packetBuffer2[(j*3) - UDP_TX_PACKET_MAX_SIZE],packetBuffer2[((j*3)+1) - UDP_TX_PACKET_MAX_SIZE],packetBuffer2[((j*3)+2) - UDP_TX_PACKET_MAX_SIZE]);
    }
  }
  LEDS.show();
  delay(50);
}
