#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

#define PIN 5
#define MID_LED  85
#define LEFT_LED  139
#define RIGHT_LED  30

Adafruit_NeoPixel strip = Adafruit_NeoPixel(180, PIN, NEO_GRB + NEO_KHZ800);

String incomingString = "";


void setup(void) {
	Serial.begin(115200);
	strip.begin();
	strip.setBrightness(100);
	//colorFill(GREEN);
	//fill_from_centre(WHITE, 0);
	//blendToColor(RED);
	colorFill(BLACK);
	fill_from_centre(WHITE, 0);
}

void blendToColor(uint32_t c) {
	uint32_t currentColor = 0;
	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;

	while (red < 255) {
		for (uint16_t i = RIGHT_LED; i<LEFT_LED; i++) {
			currentColor = strip.getPixelColor(i);
			red = currentColor &   0xFF0000;
			//Serial.write(red);
			green = currentColor & 0x00FF00;
			blue = currentColor &  0x0000FF;
			if (blue > 0)
				blue--;
			if (green > 0)
				green--;
			if (red < 255)
				red++;
			strip.setPixelColor(i, strip.Color(red, green, blue));
			strip.show();
		}
	}
}

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
	for (int left_end = LEFT_LED; left_end > MID_LED + 30; left_end--) {
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


