#include <inttypes.h>
#include <lm75.h> // https://github.com/jlz3008/lm75
#include <Ambient.h> // https://ambidata.io/refs/
 
TempI2C_LM75 temp1 = TempI2C_LM75(0x48,TempI2C_LM75::nine_bits);
TempI2C_LM75 temp2 = TempI2C_LM75(0x49,TempI2C_LM75::nine_bits);

const char SSID[] = "***********";
const char PASSWORD[] = "**********";
const int AMBIENT_CHANNEL_ID = 99999;
const char AMBIENT_WRITE_KEY[] = "****************";

WiFiClient client;
Ambient ambient;

void setup()
{
  // シリアル初期化
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Start");

  // Wifi初期化
  WiFi.config(IPAddress(192,168,116,221),IPAddress(192,168,116,254),IPAddress(255,255,255,0),IPAddress(8,8,8,8));
  WiFi.begin(SSID, PASSWORD);

  Serial.print("WiFi connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println(" connected");

  // Ambient初期化
  ambient.begin(AMBIENT_CHANNEL_ID, AMBIENT_WRITE_KEY, &client);
  
  delay(1000);
}
 
void loop()
{
  // 温度計測
  double t1 = temp1.getTemp();
  double t2 = temp2.getTemp();
  Serial.print(t1);
  Serial.print(", ");
  Serial.println(t2);

  // Ambient送信
  ambient.set(1, t1);
  ambient.set(2, t2);
  ambient.send();
  
  delay(60000);
}
