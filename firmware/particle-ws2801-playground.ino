#include "application.h"
#include "WS2801.h"

// A5 (MOSI) Yellow wire on Adafruit Pixels
// A3 (SCK) Green wire on Adafruit Pixels

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply$

const int numPixel = 10;

Adafruit_WS2801 strip = Adafruit_WS2801(numPixel);

//Adafruit_WS2801 strip = Adafruit_WS2801(25, WS2801_GRB);

void setup() {
    Spark.function("color", color);
    strip.begin();

    for (int i=0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 255, 0, 0);
        strip.show();
        delay(50);
    }
}

void loop() {

}

int color(String command) {
    // format is [RRR,GGG,BBB]
    // ie 1st red is [255,000,000]
    int red = command.substring(1,4).toInt();
    int green = command.substring(5,8).toInt();
    int blue = command.substring(9,12).toInt();
    int i;

    for (i=0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, red, green, blue);
        strip.show();
        delay(50);
    }
}
