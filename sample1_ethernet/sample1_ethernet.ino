#if ARDUINO > 18
#include <SPI.h> // needed for Arduino versions later than 0018
#endif
#include <Ethernet.h>
byte mac[] = {  0A-00-27-00-00-00 };
byte ip[] = { 175,101,67,191 }; // change to a valid address for your network
byte server[] = { 64, 233, 187, 99 }; // Google
// see text for more on IP addressing
Client client(server, 80);
void setup()
{
Ethernet.begin(mac, ip); // start ethernet using the mac and IP address
Serial.begin(9600); // start the serial library:
delay(1000); // give the ethernet hardware a second to initialize
Serial.println("connecting...");
if (client.connect()) {
Serial.println("connected");
client.println("GET /search?q=arduino HTTP/1.0"); // the HTTP request
client.println();
} else {
Serial.println("connection failed");
}
}
15.1 Setting Up the Ethernet Shield | 453
www.it-ebooks.info
void loop()
{
if (client.available()) {
char c = client.read();
Serial.print(c); // echo all data received to the Serial Monitor
}
if (!client.connected()) {
Serial.println();
Serial.println("disconnecting.");
client.stop();
for(;;)
;
}
