#include <SPI.h>
#include <Ethernet.h>

// replace the MAC address below by the MAC address printed on a sticker on the Arduino Shield 2
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetClient client;

int HTTP_PORT = 80;
String HTTP_METHOD = "GET";  // or POST
char HOST_NAME[] = "wm02.vercel.app";
String PATH_NAME = "/api/distance";
int i = 100;
String string_distance = String(i);
String serial_number = String("ttWsroMenra2e53b76d879228026fc41aff0b19a67502930dc0536017c550a0dd8f772281d46dWM222");

void setup() {
  delay(250);
  Serial.begin(9600);
  // initialize the Ethernet shield using DHCP:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1);  // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to configure using IP address instead of DHCP:
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  delay(1000);
  Serial.print("connecting to ");
  Serial.print(HOST_NAME);
  Serial.println("...");
  // connect to web server on port 80:
  if (client.connect(HOST_NAME, HTTP_PORT)) {
    // if connected:
    Serial.print("Connected to server: ");
    Serial.println(client.remoteIP());
    // make a HTTP request:
    // send HTTP header
    client.println(HTTP_METHOD + " "  + PATH_NAME + "?distance=" + string_distance + "&serialNumber=" + serial_number + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println();  // end HTTP header

    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  } else {  // if not connected:
    Serial.println("connection failed");
  }
}

void loop() {
}
