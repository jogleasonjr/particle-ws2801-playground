#include "application.h"
#include "WS2801.h"
#include "Serial_LCD_SparkFun.h"

// A5 (MOSI) Yellow wire on Adafruit Pixels
// A3 (SCK) Green wire on Adafruit Pixels

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply$

const int numPixel = 10;
const int MAX_EXPECTED_PIXELS = 128;

String black = "[000,000,000]";
String white = "[255,255,255]";

Adafruit_WS2801 strip = Adafruit_WS2801(numPixel);
Serial_LCD_SparkFun lcd = Serial_LCD_SparkFun();

//Adafruit_WS2801 strip = Adafruit_WS2801(25, WS2801_GRB);

void setup() {
    Spark.function("color", color);
    Spark.function("length", length);

    strip.begin();
    lcd.clear();

    for (int i=0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 255, 0, 0);
        strip.show();
        delay(50);
    }
}

void loop() {

}

void status(String header)
{
  lcd.clear();
  Serial1.print(header + " " + strip.numPixels());
}

int length(String command)
{
  int len = command.toInt();

  strip.updateLength(MAX_EXPECTED_PIXELS);
  clear();

  strip.updateLength(len);
  color(white);
}

void clear()
{
  for (int i = 0; i < MAX_EXPECTED_PIXELS; i++) {
      strip.setPixelColor(i, 0, 0, 0);
  }

  strip.show();
}

int color(String command) {
    status("color " + command);

    // format is [RRR,GGG,BBB]
    // ie 1st red is [255,000,000]
    int red = command.substring(1,4).toInt();
    int green = command.substring(5,8).toInt();
    int blue = command.substring(9,12).toInt();

    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, red, green, blue);
        strip.show();
        delay(50);
    }
}
