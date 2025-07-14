#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const int ecgPin = A0;  // ECG OUT from AD8232 to A0

// WiFi Credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ThingSpeak Settings
unsigned long channelID = 2797481;
const char* writeAPIKey = "UDPLLNLWFXZ2WQQL";

WiFiClient client;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  int ecgValue = analogRead(ecgPin);  // Read ECG signal
  Serial.println(ecgValue);           // For Serial Plotter

  // Upload ECG value to ThingSpeak (Field 1)
  ThingSpeak.setField(1, ecgValue);
  int response = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (response == 200) {
    Serial.println("ECG data uploaded to ThingSpeak.");
  } else {
    Serial.print("ThingSpeak error: ");
    Serial.println(response);
  }

  delay(16000);  // Upload every 16 seconds (min allowed by ThingSpeak for free accounts)
}
