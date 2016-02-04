#include <SPI.h>         // needed for Arduino versions later than 0018
#include <EthernetV2_0.h>
#include <EthernetUdpV2_0.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008

// UDP library from: bjoern@cs.stanford.edu 12/30/2008

#define UDP_TX_PACKET_MAX_SIZE 6020

byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10, 0, 1, 151);

unsigned int localPort = 9157;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;
void setup() {
  
  // disable SD SPI
//  pinMode(9,OUTPUT);
//  digitalWrite(9,HIGH);

  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
  Serial.begin(9600);
  Serial.println("INIT");
}

void loop() {
  int packetSize = Udp.parsePacket();
    
  if(packetSize)
  {
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
  }
  Serial.println(packetBuffer);
}
