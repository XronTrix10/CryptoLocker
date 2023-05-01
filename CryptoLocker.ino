#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <Keypad.h>
#include <Servo.h>

const char *ssid = ""; // <==== Your Wifi Access Point SSID Goes Here =====>
const char *password = ""; // <==== Your Wifi Access Point Password Goes Here =====>
const char *serverURL = "http://<IP>:3000/get_otp"; // <== Rplace <IP> with your local server IP address

constexpr uint8_t SignalLED = 16; // On Board LED pin
constexpr uint8_t ledPin = 12;    // External LED pin
constexpr uint8_t servoPin = D0;  // Servo Motor Pin

constexpr byte ROWS = 4;
constexpr byte COLS = 4;

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {D1, D2, D3, D4};
byte colPins[COLS] = {D5, D6, D7, D8};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Servo servoMotor;

void setup()
{
  pinMode(SignalLED, OUTPUT);
  pinMode(ledPin, OUTPUT);     // Set the LED pin as output
  servoMotor.attach(servoPin); // Attach the servo motor to the servo pin
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

int getOtpFromServer()
{
  int otp = -1;
  String error;

  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    WiFiClient client;
    http.begin(client, serverURL);

    int httpResponseCode = http.GET();

    if (httpResponseCode > 200)
    {
      Serial.print("Server Refused to give OTP ! HTTP Status ");
      Serial.print(httpResponseCode);
      Serial.println("\nPlease Wait for 15 minutes and try again !");
      otp = -1;
    }
    else if (httpResponseCode == 200)
    {
      String receivedJson = http.getString();
      StaticJsonDocument<256> jsonBuffer;

      DeserializationError error = deserializeJson(jsonBuffer, receivedJson);
      if (!error)
        otp = jsonBuffer["otp"];
    }

    http.end();
  }

  return otp;
}

void openLock()
{
  servoMotor.write(180); // Rotate servo motor to 180 degrees
  delay(1000);           // Wait for one second
}

void closeLock()
{
  servoMotor.write(0); // Rotate servo motor to 0 degrees
  delay(1000);          // Wait for one second
}

void loop()
{
  Serial.println("Entered void loop()");
  digitalWrite(SignalLED, HIGH);
  digitalWrite(ledPin, LOW); // Turn off the LED by default

  int otp = -1;

  while (otp == -1)
  {
    if (keypad.getKey() == '*')
    {
      Serial.println("'*' Was pressed !");
      otp = getOtpFromServer();
    }
    delay(50);
  }

  Serial.print("\nReceived OTP : ");
  Serial.println(otp);

  String user_otp = "";
  Serial.println("Entering while loop...");
  int Attempts = 0;
  while (Attempts < 3)
  {
    char key = keypad.getKey();
    if (key != NO_KEY)
    {
      Serial.print("KEY PRESS: ");
      Serial.println(key);
    }

    if (key != NO_KEY && isdigit(key))
    {
      user_otp += key;
      Serial.print("Updated User ENTERED OTP: ");
      Serial.println(user_otp);
    }
    else if (key == 'D')
    {
      user_otp = user_otp.substring(0, user_otp.length() - 1);
      Serial.print("Eliminated Last Key ! OTP: ");
      Serial.println(user_otp);
      continue;
    }

    if (user_otp.length() == 6)
    {
      if (user_otp.toInt() == otp)
      {
        Serial.println("OTP match! Access granted.");
        digitalWrite(ledPin, HIGH); // Turn on LED
        digitalWrite(SignalLED, LOW);
        openLock();    // Rotate servo motor and glow LED
        user_otp = ""; // Reset user_otp
        while (keypad.getKey() != '#')
        {
          delay(50); // Check for '*' key press
        }
        Serial.println("\n'#' Pressed, Now closing Door and Turning off LED");
        closeLock(); // Rotate servo motor and glow LED
        digitalWrite(SignalLED, HIGH);
        digitalWrite(ledPin, LOW); // Turn off LED
        Serial.println("Exiting while loop...");
        break;
      }
      else
      {
        user_otp = ""; // Reset user_otp
        Attempts++;
        Serial.print(Attempts);
        Serial.print(" Wrong Attempt ! Access Denied !\n");
      }
    }

    if (Attempts == 3)
    {
      Serial.println("\nAll 3 Attempts Reached ! Try to get a new OTP !\n");
    }

    delay(50);
  }
}