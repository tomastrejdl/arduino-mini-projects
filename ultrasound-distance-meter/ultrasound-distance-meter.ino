#include "U8g2lib.h"

U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, D3, D4);

const int pTrig = D5;
const int pEcho = D6;
const int buzzer = D8;

long odezva, vzdalenost;
 
void setup() {
  pinMode(pTrig, OUTPUT);
  pinMode(pEcho, INPUT);
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(9600);
  u8g2.begin();
}

void loop()
{
  u8g2.firstPage();
  do {
    readDistance();
    u8g2.setFont(u8g2_font_ncenB14_tr);
    String text = "d = " + String(vzdalenost) + " cm";
    u8g2.drawStr(0,15,text.c_str());
  } while ( u8g2.nextPage() );  
}

int readDistance() {
  digitalWrite(pTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pTrig, HIGH);
  delayMicroseconds(5);
  digitalWrite(pTrig, LOW);

  odezva = pulseIn(pEcho, HIGH);
  
  vzdalenost = odezva / 58.31;
  Serial.print("Vzdalenost je ");
  Serial.print(vzdalenost);
  Serial.println(" cm.");
}
