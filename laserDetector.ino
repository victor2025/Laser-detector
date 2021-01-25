/***************************************************
    * 1.3TFT  ST7789 IPS SPI display.
  接线
 TFT_DC    8
 TFT_RST   9  
 TFT_SDA   11    
 TFT_SCL 13    
 GND 
 VCC   5V/3.3V 都行
 BLK不用接
    * VL53LXX
  接线
  SCL   A5
  SDA   A4

 ****************************************************/

#include <Wire.h>
#include <VL53L0X.h>
#include <Adafruit_GFX.h>    // Core graphics library by Adafruit
#include <Arduino_ST7789.h> // Hardware-specific library for ST7789 (with or without CS pin)
#include <SPI.h>

#define TFT_DC    8
#define TFT_RST   9 
//#define TFT_CS    10 
#define TFT_MOSI  11  
#define TFT_SCLK  13

int16_t distance;

Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK);
VL53L0X sensor;

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    sensor.setTimeout(100);
    if (!sensor.init())
    {
        Serial.println("Failed to detect and initialize sensor!");
        while (1) {}
    }
    Serial.print("Hello! ST7789 TFT Test");
    tft.init(240, 240);
    tft.fillScreen(BLACK);
    Serial.println("Initialized");
    tft.setCursor(30, 0);
    tft.setTextColor(YELLOW);
    tft.setTextWrap(false);
    tft.print("mm");

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
    sensor.startContinuous();
}

void loop()
{   
    distance = sensor.readRangeContinuousMillimeters();
    
    tft.setCursor(0, 0);
    tft.setTextColor(RED);
    tft.setTextWrap(false);
    tft.fillRect(0,0,28,7,BLACK);
    if(distance>8000){
        // tft.print("Inf");
        Serial.println("Inf");
    }
    else{
        tft.print(distance);
        Serial.println(distance);
        delay(300);
    }
    
}
