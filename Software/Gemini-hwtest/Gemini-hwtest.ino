/*
Gemini board hardware test code

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
/*
  #define M1_PWM 11
  #define M1_A A4
  #define M1_B A5
  #define M1_CS A0
  #define M1_SEL 7
*/
#define ENCODER_1 3
#define ENCODER_0 0

#define led 13
#define ma_len 20

#define M2_PWM 9
#define M2_A A2
#define M2_B A3
#define M2_CS A1
#define M2_SEL 8




int brightness = 0;
int fadeAmount = 1;

bool state = 0;

bool en_0_status;
bool en_1_status;
long encodercount = 0;
bool dir_en;
void en_0_ISR() {
  en_0_status = digitalRead(ENCODER_0);
  encodercount++;
  if((en_0_status && en_1_status) || (!en_0_status && !en_1_status))dir_en=0;
  else dir_en=1;
}

void en_1_ISR() {
  en_1_status = digitalRead(ENCODER_1);
  encodercount++;  
  if((en_0_status && en_1_status) || (!en_0_status && !en_1_status))dir_en=1;
  else dir_en=0;

}


void setup() {
  Serial.begin(115200);
  while (!Serial);
  //pinMode (M1_PWM, OUTPUT);
  pinMode (M1_A, OUTPUT);
  pinMode (M1_B, OUTPUT);
  pinMode (led, OUTPUT);
  pinMode (M1_SEL, OUTPUT);
  pinMode (ENCODER_1, INPUT);
  pinMode (ENCODER_0, INPUT);
  digitalWrite(M1_A, state);
  digitalWrite(M1_B, !state);
  digitalWrite(led, state);
  Serial.print("GEMINI MOTOR TEST begin");
  digitalWrite(M1_SEL, !state);
  en_0_status = digitalRead(ENCODER_0);
  attachInterrupt(digitalPinToInterrupt(ENCODER_0), en_0_ISR, CHANGE);
  en_1_status = digitalRead(ENCODER_1);
  attachInterrupt(digitalPinToInterrupt(ENCODER_1), en_1_ISR, CHANGE);
}
int ma_olds[ma_len];
int ma;
int index = 0;
int nval;



double Kp=0.9;
double Kd=0.05;
double Ki=0.2;

double setpoint_value;
double deriv=0;
double integr=0;

void pid_setpoint(int value){
  setpoint_value=value;
  }

double pid_calc(int newval){   //assuming time_interval constant
  double error=setpoint_value-newval;

  double Pval = Kp * error;
  double Dval = Kd * (error - deriv);
  deriv=error;

  integr+=error;

  double Ival = Ki * integr;

  double PID = Pval + Dval + Ival;

  return PID;
  }


void loop() {

  

//  digitalWrite(M1_SEL, dir_en);
  pid_setpoint(brightness);
  
  int result=pid_calc(map(encodercount,0,310,0,255));
 
  int outm = result+brightness;
  if(outm>255)outm=255;
  if(outm<0)outm=0;
  

  brightness = brightness + fadeAmount;

  
  delay(25);
}
