#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

#define PIN 5
#define MID_LED  85
#define LEFT_LED  139
#define RIGHT_LED  30
#define MAX_LED  179

Adafruit_NeoPixel strip = Adafruit_NeoPixel(180, PIN, NEO_GRB + NEO_KHZ800);

String incomingString = "";
int Brightness = 100;


void setup(void) {
	randomSeed(millis());
	Serial.begin(115200);
	strip.begin();
	strip.setBrightness(Brightness);
	//colorFill(GREEN);
	//fill_from_centre(WHITE, 0);
	//blendToColor(RED);
	colorFill(BLACK);
	//random_colors();
	//top(WHITE);
	//sides(WHITE);
	desk(WHITE, -1);
}

void sides(uint32_t c) {
	for (uint16_t i = LEFT_LED; i<LEFT_LED+23; i++) {
		strip.setPixelColor(i, c);
	}
	for (uint16_t i = 7; i<RIGHT_LED; i++) {
		strip.setPixelColor(i, c);
	}
	strip.show();
	
}

void top(uint32_t c) {
	for (uint16_t i = LEFT_LED + 23; i<MAX_LED; i++) {
		strip.setPixelColor(i, c);
	}
	for (uint16_t i = 0; i<8; i++) {
		strip.setPixelColor(i, c);
	}
	strip.show();

}


void random_colors() {
	uint32_t c = 0;
	uint16_t led = 0;
	while (!Serial.available()) {
		led =  random(RIGHT_LED+30, LEFT_LED-30);
		c = strip.Color(random(255), random(255), random(255));
		strip.setPixelColor(led, c);
		strip.show();
		delay(10);
	}
	
}

void colorFill(uint32_t c) {
	for (uint16_t i = 0; i<strip.numPixels(); i++) {
		strip.setPixelColor(i, c);
	}
	strip.show();
}


void desk(uint32_t c, int8_t wait) {
	int l = 0;
	int r = 0;
	if (wait < 0) {
		for (uint16_t i = LEFT_LED; i >= MID_LED + 30; i--) {
			strip.setPixelColor(i, c);
		}
		for (uint16_t i = MID_LED -  30; i >= RIGHT_LED; i--) {
			strip.setPixelColor(i, c);
		}
		strip.show();
		return;
	}
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
	bool slide = false;
	uint32_t color = 0;

	if (Serial.available()) {
		incomingByte = Serial.read();
		incomingString = incomingString + incomingByte;
		incomingString.trim();
		if (incomingString.length() > 25) {
			Serial.write(incomingString.c_str());
			incomingString = "";
		}
		if (incomingString.indexOf("{") < 0) {
			return; // waiting for START of command }
		}
		if (incomingString.indexOf("}") < 0) {
			return; // waiting for end of command }
		}
		slide = incomingString.indexOf("SLIDE") >= 0;
		color = BLACK;
		if (incomingString.indexOf("WHITE") >= 0)
			color = WHITE;
		if (incomingString.indexOf("BLUE") >= 0)
			color = BLUE;
		if (incomingString.indexOf("PURPLE") >= 0)
			color = PURPLE;
		if (incomingString.indexOf("GREEN") >= 0)
			color = GREEN;
		if (incomingString.indexOf("RED") >= 0)
			color = RED;
		if (incomingString.indexOf("PINK") >= 0)
			color = PINK;
		if (incomingString.indexOf("BLACK") >= 0)
			color = BLACK;
		if (incomingString.indexOf("YELLOW") >= 0)
			color = YELLOW;

		if (incomingString.indexOf("RANDOM") >=0) {
			Serial.write(incomingString.c_str());
			incomingString = "";
			random_colors();
			return;			
		}
		if ( incomingString.indexOf("DESK") >= 0)  {			
			Serial.write(incomingString.c_str());
			if (color == BLACK)
				slide = false;
			if (slide)
				desk(color, 0);
			else
				desk(color, -1);			
		}	
		if (incomingString.indexOf("SIDES") >= 0) {
			Serial.write(incomingString.c_str());
			sides(color);
		}
		if (incomingString.indexOf("TOP") >= 0) {
			Serial.write(incomingString.c_str());
			top(color);
		}
		if ((incomingString.indexOf("{B=") >= 0) && (incomingString.indexOf("}") >= 0)) {			
			int _from = incomingString.indexOf("=")+1;
			int _to = incomingString.indexOf("}");
			String bvalue = incomingString.substring(_from, _to);
			Serial.write(bvalue.c_str());
			if (bvalue.toInt() == 0)
				return;
			Brightness = bvalue.toInt();
			strip.setBrightness(Brightness);
			strip.show();
		}
		int indexOfNewBeginning = incomingString.lastIndexOf("{");
		if (indexOfNewBeginning >= 0)
			incomingString = incomingString.substring(indexOfNewBeginning,255);
		else
			incomingString = "";
		
	}
	else {
		delay(10);
	}

}


