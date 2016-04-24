#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

#define PIN 5
#define MID_LED  85
#define LEFT_PIN  139
#define RIGHT_PIN  30

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(180, PIN, NEO_GRB + NEO_KHZ800);


String incomingString = "";


void overHeadLight(uint16_t midPoint, uint32_t c) {
	for (uint16_t i = 0; i<15; i++) {
		strip.setPixelColor(midPoint + i, c);
		strip.setPixelColor(midPoint - i, c);
	}
	strip.show();
}

void runHereToThere(uint16_t startPoint, uint16_t endPoint, uint32_t c, uint8_t wait) {
	for (uint16_t i = startPoint; i<endPoint; i++) {
		strip.setPixelColor(i, c);
		strip.show();
		delay(wait);
		strip.setPixelColor(i, BLACK);
	}
	strip.setPixelColor(endPoint, c);
	strip.show();
}


void colorFill(uint32_t c) {
	for (uint16_t i = 0; i<strip.numPixels(); i++) {
		strip.setPixelColor(i, c);
	}
	strip.show();
}

void setup(void) {
	Serial.begin(115200);
	strip.begin();
	strip.setBrightness(100);
	colorFill(BLACK);
	fill_from_centre(WHITE, 0);
}

void colorWipe(uint32_t c, uint8_t wait) {
	for (uint16_t i = 0; i<strip.numPixels(); i++) {
		strip.setPixelColor(i, c);
		strip.show();
		delay(wait);
	}
}

void fill_from_centre(uint32_t c, uint8_t wait) {
	int l = 0;
	int r = 0;
	for (int left_end = LEFT_PIN; left_end > MID_LED + 30; left_end--) {
		int counter = 0;
		for (int count = MID_LED; count < left_end; count++) {
			l = count;
			counter++;
			r = MID_LED - counter;
			strip.setPixelColor(l, c);
			strip.setPixelColor(r, c);
			strip.show();
			delay(wait);
			strip.setPixelColor(l, BLACK);
			strip.setPixelColor(r, BLACK);
			strip.show();
		}
		strip.setPixelColor(l, c);
		strip.setPixelColor(r, c);
		strip.show();
	}
}


void loop(void) {
	char incomingByte;
	if (Serial.available()) {
		incomingByte = Serial.read();
		incomingString = incomingString + incomingByte;
		incomingString.trim();
		if (incomingString.length() > 20) {
			Serial.write(incomingString.c_str());
			incomingString = "";
		}
		if (incomingString.equals("OFF")) {
			Serial.write(incomingString.c_str());
			colorFill(BLACK);
			incomingString = "";
		}
		if (incomingString.equals("ON")) {
			Serial.write(incomingString.c_str());
			colorFill(BLACK);
			fill_from_centre(WHITE, 0);
			incomingString = "";
		}	
		if (incomingString.equals("BLUE")) {
			Serial.write(incomingString.c_str());
			colorFill(BLACK);
			fill_from_centre(BLUE, 0);
			incomingString = "";
		}
		if (incomingString.equals("PURPLE")) {
			Serial.write(incomingString.c_str());
			colorFill(BLACK);
			fill_from_centre(PURPLE, 0);
			incomingString = "";
		}
		if (incomingString.equals("GREEN")) {
			Serial.write(incomingString.c_str());
			colorFill(BLACK);
			fill_from_centre(GREEN, 0);
			incomingString = "";
		}
		if (incomingString.equals("RED")) {
			Serial.write(incomingString.c_str());
			colorFill(BLACK);
			fill_from_centre(RED, 0);
			incomingString = "";
		}
		if (incomingString.equals("PINK")) {
			Serial.write(incomingString.c_str());
			colorFill(BLACK);
			fill_from_centre(PINK, 0);
			incomingString = "";
		}
	}

}


