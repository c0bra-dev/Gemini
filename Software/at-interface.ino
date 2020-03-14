#include <SoftwareSerial.h>

/*
ERRATA: WIFI_RX is left unconnected
Connect the jumper up (to UART TX) and run a wire from WIFI RX to MISO

*/

#define E1 0
#define E2 8
#define E3 1
#define E4 9
#define UART_TX 4
#define UART_RX 10
#define SCLpin 3
#define SDApin 2
#define M1_PWM 12
#define M1_A A4
#define M1_B A5
#define M1_CS A0
#define M1_SEL 6
#define M2_PWM 5
#define M2_A A2
#define M2_B A3
#define M2_CS A1
#define M2_SEL 7

SoftwareSerial wifi_serial(MISO, UART_TX); // RX, TX

void setup() {
  Serial.begin(115200);
  wifi_serial.begin(115200);
  while (!Serial);
  Serial.println("Serial ESP_01 interface");
}
void loop() {
  if (Serial.available())wifi_serial.write(Serial.read());
  if (wifi_serial.available())Serial.write(wifi_serial.read());

}
