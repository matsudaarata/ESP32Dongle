//Connect PushSwitch to IN connector
//Connect SingleLED to OUT connector
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h> //Blynk by Volodymyr ver.1.2.0

#define ledPin 25
#define on HIGH
#define off LOW

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPL6GeBzyUZj"
#define BLYNK_DEVICE_NAME "ESP32Dongle"
#define BLYNK_AUTH_TOKEN "xxxx"

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxxx";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AP01-01";
char pass[] = "1qaz2wsx";

int  power = 0;
int led = off;
const int SENSOR = 32; //INA33 INB32

struct tm timeInfo;//時刻を格納するオブジェクト
int setTime = 0;
int setHour = 0;
int setMin = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(SENSOR, INPUT);

  Blynk.begin(auth, ssid, pass);

  configTime(9 * 3600L, 0, "ntp.nict.jp");
}

int ledState() {
  if (led == off) {
    Serial.println("LEDオン");
    digitalWrite(ledPin, on); 
    return on;
  
  } else if (led == on) {
    Serial.println("LEDオフ");
    digitalWrite(ledPin, off); 
    return off;
  }   
}


void loop() {
  (getLocalTime(&timeInfo));//tmオブジェクトのtimeInfoに現在時刻を入れ込む
  Serial.print("現在の時刻は ");
  Serial.print(timeInfo.tm_hour);
  Serial.print(":");
  Serial.println(timeInfo.tm_min);
  
  Blynk.run();
  delay(100);

  if (power == 1) {
    if (digitalRead(SENSOR) == on) {
      led = ledState();
      delay(1000);
    }
  } else if(power == 0 && led == on) {
      led = ledState();
  }

  if (setTime == 1) {
    if (led == on && setHour == timeInfo.tm_hour && setMin == timeInfo.tm_min) {
      led = ledState();
      Serial.println("自動消灯します");
    }
  }
}


BLYNK_WRITE(V0)
{ 
  power = param.asInt();
}


BLYNK_WRITE(V1)
{ 
  setTime = param.asInt();
  Serial.println("自動消灯タイマーセット");
}


BLYNK_WRITE(V2) {
  setHour = param.asInt();
}


BLYNK_WRITE(V3) {
  setMin = param.asInt();
}



