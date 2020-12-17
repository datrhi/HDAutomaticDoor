#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
const int sen1 = 9;
const int sen2 = 3;
const int sen3 = 5;
const int sen4 = 10;

const int diVao = 1;
const int diRa = 2;
int count=0;
int check=0;
int tt=0;
#define IN1  7
#define IN2 6

#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0
void setup()
{
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(13,OUTPUT);
  lcd.init();                    
  lcd.backlight();
}

void motor_1_Dung() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
 

void motor_1_Mo(int speed) { //speed: từ 0 - MAX_SPEED
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED
  digitalWrite(IN1, HIGH);// chân này không có PWM
  analogWrite(IN2, 255 - speed);
}
 
void motor_1_Dong(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED
  digitalWrite(IN1, LOW);// chân này không có PWM
  analogWrite(IN2, speed);
}

void detectHuman() {
  if(count>0)
  {
    digitalWrite(13,HIGH);
  }
  else
  {
    digitalWrite(13,LOW);
  }
  lcd.print("Person In Room:");
  lcd.setCursor(15,1);
  lcd.print(count);
}
void loop()
{
  int val1 = digitalRead(sen1); 
  int val2 = digitalRead(sen2); 
  int val3 = digitalRead(sen3); 
  int val4 = digitalRead(sen4);
  

  if(val1==HIGH && val2==HIGH && val3==HIGH && val4==HIGH) 
  {
    if(check==diVao && tt==2)
    {
      count++;
      check=0;
      tt=0;
    }
    else if(check==diRa && tt==2)
    {
      count--;
      check=0;
      tt=0;
    }
    lcd.clear();
    detectHuman();
    motor_1_Dong(MAX_SPEED);
    delay(1000);
    motor_1_Dung();

  }
  else if(val1==HIGH && val2==LOW && val3==LOW) 
  {
    //dira
    check=diRa;
    detectHuman();
    motor_1_Mo(MAX_SPEED);
    delay(1000);
    motor_1_Dung();
    
  }
  else if(val1==LOW && val2==HIGH && val3==LOW) 
  {
    //divao
    check=diVao;
    detectHuman();
    motor_1_Mo(MAX_SPEED);
    delay(1000);
    motor_1_Dung();
    
  }
  else if(val1==LOW && val2==LOW && val3==LOW) 
  {
    detectHuman();
    motor_1_Mo(MAX_SPEED);
    delay(1000);
    motor_1_Dung();
    
  }
  else if(val1==HIGH && val2==LOW && val3==HIGH)
  {
    
    if(check==diVao)
    {
      tt=2;
    }
    else if(check==diRa)
    {
      tt=1;
    }
    detectHuman();
  }
  else if(val1==LOW && val2==HIGH && val3==HIGH)
  {
    if(check==diVao)
    {
      tt=1;
    }
    else if(check==diRa)
    {
      tt=2;
    }
    detectHuman();
  }
  else
  {
    detectHuman();
  }
  
}
