#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

#define PIN 5
#define MIDDLE_PIN  85

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
	overHeadLight(MIDDLE_PIN + 40, BLUE);
	overHeadLight(MIDDLE_PIN - 40, BLUE);
}

void colorWipe(uint32_t c, uint8_t wait) {
	for (uint16_t i = 0; i<strip.numPixels(); i++) {
		strip.setPixelColor(i, c);
		strip.show();
		delay(wait);
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
			overHeadLight(MIDDLE_PIN + 40, WHITE);
			overHeadLight(MIDDLE_PIN - 40, WHITE);
			incomingString = "";
		}	
		if (incomingString.equals("BLUE")) {
			Serial.write(incomingString.c_str());
			colorFill(BLACK);
			overHeadLight(MIDDLE_PIN + 40, BLUE);
			overHeadLight(MIDDLE_PIN - 40, BLUE);
			incomingString = "";
		}
		if (incomingString.equals("PURPLE")) {
			Serial.write(incomingString.c_str());
			colorFill(BLACK);
			overHeadLight(MIDDLE_PIN + 40, PURPLE);
			overHeadLight(MIDDLE_PIN - 40, PURPLE);
			incomingString = "";
		}
		if (incomingString.equals("GREEN")) {
			Serial.write(incomingString.c_str());
			colorFill(BLACK);
			overHeadLight(MIDDLE_PIN + 40, GREEN);
			overHeadLight(MIDDLE_PIN - 40, PURPLE);
			incomingString = "";
		}
		if (incomingString.equals("RED")) {
			Serial.write(incomingString.c_str());
			colorFill(BLACK);
			overHeadLight(MIDDLE_PIN + 40, RED);
			overHeadLight(MIDDLE_PIN - 40, RED);
			incomingString = "";
		}
		if (incomingString.equals("PINK")) {
			Serial.write(incomingString.c_str());
			colorFill(BLACK);
			overHeadLight(MIDDLE_PIN + 40, PINK);
			overHeadLight(MIDDLE_PIN - 40, PINK);
			incomingString = "";
		}
	}

}


