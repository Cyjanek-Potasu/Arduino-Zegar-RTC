#include <Wire.h>
#include <FastLED.h>
#include "RTClib.h"
#include <SFE_BMP180.h>


RTC_DS1307 RTC;
SFE_BMP180 bmp180;
#define NUM_LEDS 30
#define DATA_PIN 3

CRGB leds[NUM_LEDS];

CRGB white = (255,150,255);
CRGB black = (0,0,0);
String state = "default";

int aDigit = 0;
int bDigit = 0;
int cDigit = 0;
int dDigit = 0;


CRGB randNumbers[] = {
  CRGB::AliceBlue,
  CRGB::Amethyst,
  CRGB::AntiqueWhite,
  CRGB::Aqua,
  CRGB::Aquamarine,
  CRGB::Azure,
  CRGB::Beige,
  CRGB::Bisque,
  CRGB::Black,
  CRGB::BlanchedAlmond,
  CRGB::Blue,
  CRGB::BlueViolet,
  CRGB::Brown,
  CRGB::BurlyWood,
  CRGB::CadetBlue,
  CRGB::Chartreuse,
  CRGB::Chocolate,
  CRGB::Coral,
  CRGB::CornflowerBlue,
  CRGB::Cornsilk,
  CRGB::Crimson,
  CRGB::Cyan,
  CRGB::DarkBlue,
  CRGB::DarkCyan,
  CRGB::DarkGoldenrod,
  CRGB::DarkGray,
  CRGB::DarkGreen,
  CRGB::DarkKhaki,
  CRGB::DarkMagenta,
  CRGB::DarkOliveGreen,
  CRGB::DarkOrange,
  CRGB::DarkOrchid,
  CRGB::DarkRed,
  CRGB::DarkSalmon,
  CRGB::DarkSeaGreen,
  CRGB::DarkSlateBlue,
  CRGB::DarkSlateGray,
  CRGB::DarkTurquoise,
  CRGB::DarkViolet,
  CRGB::DeepPink,
  CRGB::DeepSkyBlue,
  CRGB::DimGray,
  CRGB::DodgerBlue,
  CRGB::FireBrick,
  CRGB::FloralWhite,
  CRGB::ForestGreen,
  CRGB::Fuchsia,
  CRGB::Gainsboro,
  CRGB::GhostWhite,
  CRGB::Gold,
  CRGB::Goldenrod,
  CRGB::Gray,
  CRGB::Green,
  CRGB::GreenYellow,
  CRGB::Honeydew,
  CRGB::HotPink,
  CRGB::IndianRed,
  CRGB::Indigo,
  CRGB::Ivory,
  CRGB::Khaki,
  CRGB::Lavender,
  CRGB::LavenderBlush,
  CRGB::LawnGreen,
  CRGB::LemonChiffon,
  CRGB::LightBlue,
  CRGB::LightCoral,
  CRGB::LightCyan,
  CRGB::LightGoldenrodYellow,
  CRGB::LightGreen,
  CRGB::LightGrey,
  CRGB::LightPink,
  CRGB::LightSalmon,
  CRGB::LightSeaGreen,
  CRGB::LightSkyBlue,
  CRGB::LightSlateGray,
  CRGB::LightSteelBlue,
  CRGB::LightYellow,
  CRGB::Lime,
  CRGB::LimeGreen,
  CRGB::Linen,
  CRGB::Magenta,
  CRGB::Maroon,
  CRGB::MediumAquamarine,
  CRGB::MediumBlue,
  CRGB::MediumOrchid,
  CRGB::MediumPurple,
  CRGB::MediumSeaGreen,
  CRGB::MediumSlateBlue,
  CRGB::MediumSpringGreen,
  CRGB::MediumTurquoise,
  CRGB::MediumVioletRed,
  CRGB::MidnightBlue,
  CRGB::MintCream,
  CRGB::MistyRose,
  CRGB::Moccasin,
  CRGB::NavajoWhite,
  CRGB::Navy,
  CRGB::OldLace,
  CRGB::Olive,
  CRGB::OliveDrab,
  CRGB::Orange,
  CRGB::OrangeRed,
  CRGB::Orchid,
  CRGB::PaleGoldenrod,
  CRGB::PaleGreen,
  CRGB::PaleTurquoise,
  CRGB::PaleVioletRed,
  CRGB::PapayaWhip,
  CRGB::PeachPuff,
  CRGB::Peru,
  CRGB::Pink,
  CRGB::Plaid,
  CRGB::Plum,
  CRGB::PowderBlue,
  CRGB::Purple,
  CRGB::Red,
  CRGB::RosyBrown,
  CRGB::RoyalBlue,
  CRGB::SaddleBrown,
  CRGB::Salmon,
  CRGB::SandyBrown,
  CRGB::SeaGreen,
  CRGB::Seashell,
  CRGB::Sienna,
  CRGB::Silver,
  CRGB::SkyBlue,
  CRGB::SlateBlue,
  CRGB::SlateGray,
  CRGB::Snow,
  CRGB::SpringGreen,
  CRGB::SteelBlue,
  CRGB::Tan,
  CRGB::Teal,
  CRGB::Thistle,
  CRGB::Tomato,
  CRGB::Turquoise,
  CRGB::Violet,
  CRGB::Wheat,
  CRGB::White,
  CRGB::WhiteSmoke,
  CRGB::Yellow,
  CRGB::YellowGreen
};

int numColors = sizeof(randNumbers) / sizeof(randNumbers[0]);


long madblack[10] = {
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black
};

double T, P;
int stateCounter;

bool stan = false;

CRGB stillColor = CRGB::White;
CRGB kolor(){
  if(stan){
    return randNumbers[random(0,numColors)];
  }
  else{
    return stillColor;
  }
  
}

void setup () {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    Serial.begin(9600);
    Wire.begin();
    RTC.begin();
    bmp180.begin();
    pinMode(12, INPUT);
    digitalWrite(12, HIGH);
    stateCounter = 0; 
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void dot(bool l0 = false, bool l1 = false) {

leds[15] = (l0) ? kolor() : black;
leds[14] = (l1) ? kolor() : black;
FastLED.show();  
FastLED.delay(100);

}


void loop () {

  stan = digitalRead(12);
  
  DateTime now = RTC.now(); 
  ReadPressure();
  stillColor = randNumbers[random(0,numColors)];

  if(!stan){
    int hour = now.hour();
    int minute = now.minute();
    aDigit = hour / 10;
    bDigit = hour % 10;
    cDigit = minute / 10;
    dDigit = minute % 10;

    writeA(aDigit);
    writeB(bDigit);
    writeC(cDigit);
    writeD(dDigit);


    dot(true, false);
    delay(1000);
    dot(false, true);
    delay(1000);

    if(stateCounter == 10){
      writeA(int(T) / 10);
      writeB(int(T) % 10);
      writeC(12);//degrees mark
      writeD(12);//C letter
      delay(3000);
      writeA(int(P) / 1000 % 10);
      writeB(int(P) / 100 % 10);
      writeC(int(P) / 10 % 10);
      writeD(int(P) % 10);
      delay(2000);
      writeA(13);//H
      writeB(13);//P
      writeC(13);//A
      writeD(100);//clear
      stateCounter = 0;
      delay(1000);
    }
    stateCounter +=1;
    Serial.println(stateCounter);

  }else{
    int hour = now.hour();
    int minute = now.minute();
    aDigit = hour / 10;
    bDigit = hour % 10;
    cDigit = minute / 10;
    dDigit = minute % 10;

    writeA(aDigit);
    writeB(bDigit);
    writeC(cDigit);
    writeD(dDigit);


    dot(true, false);
    delay(50);
    dot(false, true);

  }



}

void ReadPressure(){
    char status;
  
  bool success = false;

  status = bmp180.startTemperature();

  if (status != 0) {
    delay(50);
    status = bmp180.getTemperature(T);

    if (status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);


      }
    }
  }
}



void a(bool l0 = false, bool l1 = false, bool l2 = false, bool l3 = false, bool l4 = false, bool l5 = false, bool l6 = false ) {

leds[3] = (l0) ? kolor() : black;
leds[4] = (l1) ? kolor() : black;
leds[5] = (l2) ? kolor() : black;
leds[0] = (l3) ? kolor() : black;
leds[1] = (l4) ? kolor() : black;
leds[2] = (l5) ? kolor() : black;
leds[6] = (l6) ? kolor() : black;
FastLED.show();  
FastLED.delay(100);

}

void b(bool l0 = false, bool l1 = false, bool l2 = false, bool l3 = false, bool l4 = false, bool l5 = false, bool l6 = false ) {

leds[7] = (l0) ? kolor() : black;
leds[8] = (l1) ? kolor() : black;
leds[9] = (l2) ? kolor() : black;
leds[10] = (l3) ? kolor() : black;
leds[11] = (l4) ? kolor() : black;
leds[12] = (l5) ? kolor() : black;
leds[13] = (l6) ? kolor() : black;
FastLED.show();  
FastLED.delay(100);

}



void c(bool l0 = false, bool l1 = false, bool l2 = false, bool l3 = false, bool l4 = false, bool l5 = false, bool l6 = false ) {

leds[16] = (l0) ? kolor() : black;
leds[17] = (l1) ? kolor() : black;
leds[18] = (l2) ? kolor() : black;
leds[19] = (l3) ? kolor() : black;
leds[20] = (l4) ? kolor() : black;
leds[21] = (l5) ? kolor() : black;
leds[22] = (l6) ? kolor() : black;
FastLED.show();  
FastLED.delay(100);

}

void d(bool l0 = false, bool l1 = false, bool l2 = false, bool l3 = false, bool l4 = false, bool l5 = false, bool l6 = false ) {

leds[23] = (l0) ? kolor() : black;
leds[24] = (l1) ? kolor() : black;
leds[25] = (l2) ? kolor() : black;
leds[26] = (l3) ? kolor() : black;
leds[27] = (l4) ? kolor() : black;
leds[28] = (l5) ? kolor() : black;
leds[29] = (l6) ? kolor() : black;
FastLED.show();  
FastLED.delay(100);

}


void writeA(int number){
  switch(number){
    case 0:
      a(true, true, true, true, true, true, false);
      break;
    case 1:
      a(false, true, true, false, false, false, false);
      break;
    case 2:
      a(true, true, false, true, true, false, true);
      break;
    case 3:
      a(true, true, true, true, false, false, true);
      break;
    case 4:
      a(false, true, true, false, false, true, true);
      break;
    case 5:
      a(true, false, true, true, false, true, true);
      break;
    case 6:
      a(true, false, true, true, true, true, true);
      break;
    case 7:
      a(true, true, true, false, false, false, false);
      break;
    case 8:
      a(true, true, true, true, true, true, true);
      break;
    case 9:
      a(true, true, true, true, false, true, true);
      break;
    case 11:
      a(true, true, true, false, false, false, false);
      break;
    case 13: // h letter
      a(false, true, true, false ,true ,true, true);
  }
}

void writeB(int number){
  switch(number){
    case 0:
      b(true, true, true, true, true, true, false);
      break;
    case 1:
      b(false, true, true, false, false, false, false);
      break;
    case 2:
      b(true, true, false, true, true, false, true);
      break;
    case 3:
      b(true, true, true, true, false, false, true);
      break;
    case 4:
      b(false, true, true, false, false, true, true);
      break;
    case 5:
      b(true, false, true, true, false, true, true);
      break;
    case 6:
      b(true, false, true, true, true, true, true);
      break;
    case 7:
      b(true, true, true, false, false, false, false);
      break;
    case 8:
      b(true, true, true, true, true, true, true);
      break;
    case 9:
      b(true, true, true, true, false, true, true);
      break;
    case 11:
      b(false, true, true, true, true, false, true);
      break;
    case 13://P
      b(true, true, false, false, true, true, true);
      break;
    case 100:
      b(false, false, false, false, false, false, false);
  }
}

void writeC(int number){
  switch(number){
    case 0:
      c(true, true, true, true, true, true, false);
      break;
    case 1:
      c(false, true, true, false, false, false, false);
      break;
    case 2:
      c(true, true, false, true, true, false, true);
      break;
    case 3:
      c(true, true, true, true, false, false, true);
      break;
    case 4:
      c(false, true, true, false, false, true, true);
      break;
    case 5:
      c(true, false, true, true, false, true, true);
      break;
    case 6:
      c(true, false, true, true, true, true, true);
      break;
    case 7:
      c(true, true, true, false, false, false, false);
      break;
    case 8:
      c(true, true, true, true, true, true, true);
      break;
    case 9:
      c(true, true, true, true, false, true, true);
      break;
    case 10:
      c(true, true, false, false ,false ,true ,true);
      break;
    case 11:
      c(true, true, true, true, true, true, true);
    case 100:
      c(false, false, false, false, false, false, false);
    case 12:
      c(true, true, false, false, false ,true ,true);
      break;
    case 13://A
      c(true, true, true, false, true, true, true);
      break;
      }
}

void writeD(int number){
  switch(number){
    case 0:
      d(true, true, true, true, true, true, false);
      break;
    case 1:
      d(false, true, true, false, false, false, false);
      break;
    case 2:
      d(true, true, false, true, true, false, true);
      break;
    case 3:
      d(true, true, true, true, false, false, true);
      break;
    case 4:
      d(false, true, true, false, false, true, true);
      break;
    case 5:
      d(true, false, true, true, false, true, true);
      break;
    case 6:
      d(true, false, true, true, true, true, true);
      break;
    case 7:
      d(true, true, true, false, false, false, false);
      break;
    case 8:
      d(true, true, true, true, true, true, true);
      break;
    case 9:
      d(true, true, true, true, false, true, true);
      break;
    case 10:
      d(false, false, false, false, false ,false ,false);
      break;
    case 12:
      d(true, false, false, true, true, true ,false);
      break;
    case 100:
      d(false, false, false, false, false, false, false);
  }
}