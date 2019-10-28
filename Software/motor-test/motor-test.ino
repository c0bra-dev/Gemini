#include <SoftPWM.h>
#include <SoftPWM_timer.h>

#define E1 0
#define E2 8
#define E3 1
#define E4 9
#define UART_TX 4
#define UART_RX 10
#define WIFI_RX 11
#define WIFI_TX_def MISO
#define WIFI_TX_opt UART_TX
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


int speed_var = 0;
int fadeAmount = 1;


int cycle = 0;
void setup() {
  Serial.begin(115200);
  pinMode (M1_PWM, OUTPUT);
  pinMode (M1_A, OUTPUT);
  pinMode (M1_B, OUTPUT);
  pinMode (M2_PWM, OUTPUT);
  pinMode (M2_A, OUTPUT);
  pinMode (M2_B, OUTPUT);
  while (!Serial);
  Serial.println("GEMINI MOTOR TEST begin");

  SoftPWMBegin();

  SoftPWMSet(M1_PWM, 0);
  SoftPWMSet(M2_PWM, 0);
  digitalWrite(M2_A, 1);
  digitalWrite(M2_B, 0);

}

void loop() {

  switch (cycle) {
    case 0:
      if (speed_var == 0) {
        Serial.println("Motore 1 direzione 1");  
        SoftPWMSetPercent(M2_PWM, 0);
        digitalWrite(M1_A, 1);
        digitalWrite(M1_B, 0);
      }
      SoftPWMSetPercent(M1_PWM, speed_var);
    break;    
    case 1:
      if (speed_var == 0) {
        Serial.println("Motore 1 direzione 2");
        SoftPWMSetPercent(M2_PWM, 0);
        digitalWrite(M1_A, 0);
        digitalWrite(M1_B, 1);
      }
      SoftPWMSetPercent(M1_PWM, speed_var);
    break;    
    case 2:
      if (speed_var == 0) {
        Serial.println("Motore 2 direzione 1");
        SoftPWMSetPercent(M1_PWM, 0);
        digitalWrite(M2_A, 1);
        digitalWrite(M2_B, 0);
      }
      SoftPWMSetPercent(M2_PWM, speed_var);
    break;    
    case 3:
      if (speed_var == 0) {
        Serial.println("Motore 2 direzione 2");
        SoftPWMSetPercent(M1_PWM, 0);
        digitalWrite(M1_A, 0);
        digitalWrite(M1_B, 1);
      }
      SoftPWMSetPercent(M2_PWM, speed_var);
      break;
    default:
      cycle = 0;
      break;
  }

  speed_var += fadeAmount;
  if (speed_var <= 0 || speed_var >= 100) {
    fadeAmount = -fadeAmount;
    if (speed_var == 0)cycle++;
  }
  delay(30);

}
