#include <SPI.h>
#include <Ethernet.h>
#define echoPin  2// Echo Pin
#define trigPin 3 // Trigger Pin

long duration; // Duration used to calculate distance

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xFE, 0xD2 };
IPAddress ip(192, 168, 0 ,109); 
byte gateway[] = { 192,168,0,1 }; 

byte server[] = { 192,168,0,104}; 

byte subnet[]={255,255,255,0};
EthernetClient client;
char url[30];
int val=40;
void setup()
{
Serial.begin(9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
Ethernet.begin(mac, ip, gateway,subnet);
}

void loop()
{
  val=measure_water_level();

  Serial.println(val);
  //sprintf(url,"GET /tank.php?level=%d HTTP/1.1",val);
  //Serial.println(url);
  if (client.connect(server,80)) {  //starts client connection, checks for connection
    sprintf(url,"GET /tank.php?level=%d HTTP/1.1",val);
    Serial.println("connected");
    client.println(url);
    client.println( "Host: localhost");
    client.println(); 
   // delay(10);
    client.stop();
   } 
  else {  
    Serial.println("connection failed"); //error message if no client connect
    Serial.println();
   }
  
}

int measure_water_level()
{
  digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);

float q=map(duration/29/2,0,22,100,0);
//Serial.print("water level value");
//Serial.println(q);
  return q;
}
