#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008

#define UDP_TX_PACKET_MAX_SIZE 1500

byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0x01, 0x11 };
IPAddress ip(10, 0, 1, 111);

unsigned int localPort = 9111;
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
//  Serial.println("SAcramant");
  int packetSize = Udp.parsePacket();
  
  if(packetSize)
  {
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
  }
  Serial.println(packetBuffer);
}
