//CHIAKI-chan
//2017.05.01

#include <mem.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <WiFiUdp.h>
#include <OSCBundle.h>
#include <ESPDMX.h>

DMXESPSerial dmx;

#define __DEBUG_MODE__

#define id 120


#include "color_data.h"
int wifiUse = 0;



//Wifi
WiFiUDP Udp;

#ifdef __DEBUG_MODE__
char ssid[] = "MATHRAX_SUB";     // your network SSID (name)
#else
char ssid[] = "HONBAN";     // your network SSID (name)
#endif
char pass[] = "remokuma";    // your network password


#if (id == 120) //DIAMOND
//自分のアドレスとポート
#ifdef __DEBUG_MODE__
const IPAddress myIP(192, 168, 1, 120);      //固定IP
#else
const IPAddress myIP(192, 168, 11, 120);      //固定IP
#endif
#define maxLED  23
float maxPrescale = 15;
unsigned char minamoMode = 1;

#elif (id == 121) //TSUTA_R
const IPAddress myIP(192, 168, 11, 121);      //固定IP
#define maxLED  23
float maxPrescale = 15;
unsigned char minamoMode = 1;

#elif (id == 122) //TSUTA_L
const IPAddress myIP(192, 168, 11, 122);      //固定IP
#define maxLED  23
float maxPrescale = 15;
unsigned char minamoMode = 1;

#elif (id == 123) //WING_R
const IPAddress myIP(192, 168, 11, 123);      //固定IP
#define maxLED  23
float maxPrescale = 15;
unsigned char minamoMode = 1;

#elif (id == 124) //WING_L
const IPAddress myIP(192, 168, 11, 124);      //固定IP
#define maxLED  23
float maxPrescale = 15;
unsigned char minamoMode = 1;

#elif (id == 125) //OTHER
const IPAddress myIP(192, 168, 11, 125);      //固定IP
#define maxLED  23
float maxPrescale = 15;
unsigned char minamoMode = 1;
#endif


const unsigned int receivePort = 9999;      //こちらで受信するポート

//相手(PC)のアドレスとポート
#ifdef __DEBUG_MODE__
const IPAddress outIp(192, 168, 1, 220);      //相手(PC)のIP
#else
const IPAddress outIp(192, 168, 11, 220);      //相手(PC)のIP
#endif
const unsigned int sendPort = 3333;         //こちらから送信するポート

//ルータのアドレスとサブネットマスク
#ifdef __DEBUG_MODE__
const IPAddress myGateWay(192, 168, 1, 1);
#else
const IPAddress myGateWay(192, 168, 11, 1);
#endif
const IPAddress mySubnet(255, 255, 255, 0);

#define maxBuf (maxLED+1)*3

int count = -1;
unsigned int next_count = 0;
unsigned int prescale;

int count_osc = -1;
float prescale_osc;


unsigned char maxColorCount = 50;

unsigned char maxBright = 200;

unsigned char now_r[maxBuf];
unsigned char now_g[maxBuf];
unsigned char now_b[maxBuf];

unsigned char next_r[maxBuf];
unsigned char next_g[maxBuf];
unsigned char next_b[maxBuf];

float diff_r[maxBuf];
float diff_g[maxBuf];
float diff_b[maxBuf];

float diff_r_osc[maxBuf];
float diff_g_osc[maxBuf];
float diff_b_osc[maxBuf];

unsigned char set_r[maxBuf];
unsigned char set_g[maxBuf];
unsigned char set_b[maxBuf];

unsigned char buf_r[maxBuf];
unsigned char buf_g[maxBuf];
unsigned char buf_b[maxBuf];

unsigned char now_r_osc[maxBuf];
unsigned char now_g_osc[maxBuf];
unsigned char now_b_osc[maxBuf];
unsigned char next_r_osc[maxBuf];
unsigned char next_g_osc[maxBuf];
unsigned char next_b_osc[maxBuf];

unsigned char fadeEnd;
float crossFade;
float fade_d = 0.1;

void setup() {
  int i, j;
  //シリアルポート
  //（USBシリアルでつないだときだけデバッグ用）
  Serial.begin(115200);

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  //Wifiを開始（このプログラムの下の方にあります）
  wifiStart();

  for (i = 0; i < maxBuf; i++) {
    now_r[i] = 0;
    now_g[i] = 0;
    now_b[i] = 0;

    next_r[i] = (color_data[i * maxColorCount] >> 16) & 0xFF;
    next_g[i] = (color_data[i * maxColorCount] >> 8) & 0xFF;
    next_b[i] = (color_data[i * maxColorCount]) & 0xFF;

    if (now_r[i] >= 255)now_r[i] = 254;
    if (now_g[i] >= 255)now_g[i] = 254;
    if (now_b[i] >= 255)now_b[i] = 254;

    if (next_r[i] >= 255)next_r[i] = 254;
    if (next_g[i] >= 255)next_g[i] = 254;
    if (next_b[i] >= 255)next_b[i] = 254;
  }

  Serial.write(255);
  for (i = 0; i < maxLED; i++) {
    for ( j = 0; j < 18; j++) {
      Serial.write(0);
    }
  }

  dmx.init();               // initialization for first 32 addresses by default
  dmx.init(432);           // initialization for complete bus

}



void loop() {
  int i;

  ArduinoOTA.handle();
  doWifi();


  if (minamoMode == 1) {
    crossFade += fade_d;
    if (crossFade >= 1.0) {
      crossFade = 1.0;
    }
  } else {
    crossFade -= fade_d;
    if (crossFade <= 0) {
      crossFade = 0;
    }
  }


  prescale_osc += fade_d;
  if (prescale_osc > maxPrescale) {
    prescale_osc = maxPrescale;
  }

  prescale ++;
  if (prescale > maxPrescale) {
    prescale = 0;
    count++;
    if (count < maxColorCount - 1) {
      next_count = count + 1;
    } else if (count > maxColorCount - 1) {
      count = 0;
      next_count = 1;
    } else if (count == maxColorCount - 1) {
      next_count = 0;
    }
  }


  for (i = 0; i < maxBuf; i++) {

    now_r[i] = (color_data[i * maxColorCount + count] >> 16) & 0xFF;
    now_g[i] = (color_data[i * maxColorCount + count] >> 8) & 0xFF;
    now_b[i] = (color_data[i * maxColorCount + count]) & 0xFF;

    next_r[i] = (color_data[i * maxColorCount + next_count] >> 16) & 0xFF;
    next_g[i] = (color_data[i * maxColorCount + next_count] >> 8) & 0xFF;
    next_b[i] = (color_data[i * maxColorCount + next_count]) & 0xFF;

    if (now_r[i] >= maxBright)now_r[i] = maxBright;
    if (now_g[i] >= maxBright)now_g[i] = maxBright;
    if (now_b[i] >= maxBright)now_b[i] = maxBright;

    if (next_r[i] >= maxBright)next_r[i] = maxBright;
    if (next_g[i] >= maxBright)next_g[i] = maxBright;
    if (next_b[i] >= maxBright)next_b[i] = maxBright;

    diff_r[i] = next_r[i] - now_r[i];
    diff_g[i] = next_g[i] - now_g[i];
    diff_b[i] = next_b[i] - now_b[i];


    now_r_osc[i] = set_r[i];
    now_g_osc[i] = set_g[i];
    now_b_osc[i] = set_b[i];

    diff_r_osc[i] = next_r_osc[i] - now_r_osc[i];
    diff_g_osc[i] = next_g_osc[i] - now_g_osc[i];
    diff_b_osc[i] = next_b_osc[i] - now_b_osc[i];


    set_r[i] =  ((now_r[i] + prescale * (diff_r[i] / maxPrescale)) * (crossFade)) +
                ((now_r_osc[i] + prescale_osc * (diff_r_osc[i] / maxPrescale)) * (1.0 - crossFade));
    set_g[i] =  ((now_g[i] + prescale * (diff_g[i] / maxPrescale)) * (crossFade)) +
                ((now_g_osc[i] + prescale_osc * (diff_g_osc[i] / maxPrescale)) * (1.0 - crossFade));
    set_b[i] =  ((now_b[i] + prescale * (diff_b[i] / maxPrescale)) * (crossFade)) +
                ((now_b_osc[i] + prescale_osc * (diff_b_osc[i] / maxPrescale)) * (1.0 - crossFade));

    if (set_r[i] > maxBright)set_r[i] = maxBright;
    if (set_g[i] > maxBright)set_g[i] = maxBright;
    if (set_b[i] > maxBright)set_b[i] = maxBright;

  }


  //LED
  for (i = 0; i < maxLED; i++) {
    //OMOTE
    dmx.write(i*18+ 1,set_b[i * 3 + 1]);  //b
    dmx.write(i*18+ 2,set_g[i * 3 + 1]);  //g
    dmx.write(i*18+ 3,set_r[i * 3 + 1]);  //r
    
    dmx.write(i*18+ 4,set_b[i * 3 + 0]);
    dmx.write(i*18+ 5,set_g[i * 3 + 0]);
    dmx.write(i*18+ 6,set_r[i * 3 + 0]);
    
    dmx.write(i*18+ 7,set_b[i * 3 + 2]);
    dmx.write(i*18+ 8,set_g[i * 3 + 2]);
    dmx.write(i*18+ 9,set_r[i * 3 + 2]);

    dmx.write(i*18+ 10,set_b[i * 3 + 4]);
    dmx.write(i*18+ 11,set_g[i * 3 + 4]);
    dmx.write(i*18+ 12,set_r[i * 3 + 4]);
    
    dmx.write(i*18+ 13,set_b[i * 3 + 3]);
    dmx.write(i*18+ 14,set_g[i * 3 + 3]);
    dmx.write(i*18+ 15,set_r[i * 3 + 3]);
    
    dmx.write(i*18+ 16,set_b[i * 3 + 5]);
    dmx.write(i*18+ 17,set_g[i * 3 + 5]);
    dmx.write(i*18+ 18,set_r[i * 3 + 5]);

  }
  dmx.update();           // update the DMX bus

}
