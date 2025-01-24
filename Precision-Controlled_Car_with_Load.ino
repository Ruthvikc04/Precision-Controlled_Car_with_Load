#define BLYNK_TEMPLATE_ID "TMPL3ZcdUIMjz"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "b4oomuJY7TazB4hPUMopz9q3LuNXBNzl"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Motor PINs
#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5

bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;
bool metre=0;

// Constants for wheel and car geometry
const float tireCircumference = 0.21; // in meters (22.1cm)
const float distanceToTravel = 1.0;    // in meters

char auth[] = "b4oomuJY7TazB4hPUMopz9q3LuNXBNzl"; // Enter your Blynk application auth token
char ssid[] = ".";                  // Enter your WIFI name
char pass[] = ".";           // Enter your WIFI password

void setup()
{
  // Initialize the serial monitor
  Serial.begin(9600);
  // Set the motor pins as the output pin
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // Initialize the Blynk communication
  Blynk.begin(auth, ssid, pass);
}

// Get values from the widgets
BLYNK_WRITE(V0)
{
  forward = param.asInt();
}

BLYNK_WRITE(V1)
{
  backward = param.asInt();
}

BLYNK_WRITE(V2)
{
  left = param.asInt();
}

BLYNK_WRITE(V3)
{
  right = param.asInt();
}
BLYNK_WRITE(V4)
{
  metre = param.asInt();
}
// Check widget values using the IF condition
void smartcar()
{
  if (forward == 1)
  {
    Forward();
    Serial.println("Forward");
  }
  else if (backward == 1)
  {
    Backward();
    Serial.println("Backward");
  }
  else if (left == 1)
  {
    Left();
    Serial.println("Left");
  }
  else if (right == 1)
  {
    Right();
    Serial.println("Right");
  }
  else if (forward == 0 && backward == 0 && left == 0 && right == 0)
  {
    Stop();
    Serial.println("Stop");
  }
}

// Move the car 1m forward
void moveOneMeter()
{
  Serial.println("1metre");
  int numRevolutions = distanceToTravel / tireCircumference;
  for (int i = 0; i < numRevolutions; i++)
  {
    Forward();
    delay(1300); // Assuming it takes 1.3 second to complete one revolution
  }
  Stop();
}

void loop()
{
  // Run the Blynk library
  Blynk.run();
  smartcar();

  // Check if the button is pressed
  if (metre == 1)
  {
    moveOneMeter();
    Blynk.virtualWrite(V4, 0); // Reset the button state to OFF
  }
}
// Motor control functions
void Forward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Backward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void Left()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Right()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void Stop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
