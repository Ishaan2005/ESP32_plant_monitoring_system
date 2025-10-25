#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <BlynkSimpleEsp32.h>

#define WIFI_SSID "hotspot123"
#define WIFI_PASSWORD "1234"
#define MQTT_BROKER "ip address"
#define MQTT_PORT 1883
#define MQTT_TOPIC "sensor/data"

#define DHTPIN 33
#define DHTTYPE DHT11
#define SOIL_PIN 34

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32Client")) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" trying again in 5 seconds");
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");

    client.setServer(MQTT_BROKER, MQTT_PORT);
    Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);

    dht.begin();
    delay(2000);
}

float getTemperature() {
    float temp;
    for (int i = 0; i < 3; i++) {
        temp = dht.readTemperature();
        if (!isnan(temp)) return temp;
        delay(100);
    }
    return 26.0;
}

float getHumidity() {
    float hum;
    for (int i = 0; i < 3; i++) {
        hum = dht.readHumidity();
        if (!isnan(hum)) return hum;
        delay(100);
    }
    return 30.0;
}

void publishSensorData(float temp, float humidity, float soilMoisture) {
    char msg[50];
    snprintf(msg, sizeof(msg), "temperature:%.1f,humidity:%.1f,soil_moisture:%.1f", temp, humidity, soilMoisture);

    client.publish(MQTT_TOPIC, msg);
    Serial.println("Published to MQTT: " + String(msg));
}

void loop() {
    Blynk.run();
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    float temp = getTemperature();
    float humidity = getHumidity();
    int rawSoilMoisture = analogRead(SOIL_PIN);
    float soilMoisture = map(rawSoilMoisture, 4095, 1500, 0, 100);
    soilMoisture = constrain(soilMoisture, 0, 100);

    Blynk.virtualWrite(V0, temp);
    Blynk.virtualWrite(V1, humidity);
    Blynk.virtualWrite(V2, soilMoisture);

    publishSensorData(temp, humidity, soilMoisture);

    delay(5000); 
}
