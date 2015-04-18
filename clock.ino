#include <Adafruit_NeoPixel.h>

#define PIN 10

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(120, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(255);
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  /*colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127,   0,   0), 50); // Red
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);*/
  
  time(1, 5);//5);
}

void time(uint8_t bs, uint8_t wait) {
  uint32_t millisecond = strip.Color(150, 150, 150);
  uint32_t second      = strip.Color(255, 255, 0);
  uint32_t minute      = strip.Color(0, 255, 255);
  uint32_t hour        = strip.Color(255, 0, 255);
  int stars[5];
 
  for(uint16_t h=0; h<strip.numPixels()/2; h++) {
    
    // Hours
    if (h>=bs) {
      strip.setPixelColor(h-bs, 0);
    } else {
      strip.setPixelColor(strip.numPixels()-bs+h, 0);
    }
    
    for(uint16_t m=0; m<strip.numPixels()/2; m++) {
     
      // Minutes
      if (m>=bs) {
        strip.setPixelColor((m-1)*2, 0);
        strip.setPixelColor((m-1)*2-1, 0);
      } else {
        strip.setPixelColor(strip.numPixels()-bs+m, 0);
        strip.setPixelColor(strip.numPixels()-bs+m-1, 0);
      }
      
      for(uint16_t s=0; s<strip.numPixels()/2; s++) {
        
        // Seconds
        if (s>=bs) {
          strip.setPixelColor((s-1)*2, 0);
          strip.setPixelColor((s-1)*2-1, 0);
        } else {
          strip.setPixelColor(strip.numPixels()-bs+s, 0);
          strip.setPixelColor(strip.numPixels()-bs+s-1, 0);
        }
        
        for(uint16_t ms=0; ms<strip.numPixels(); ms++) {
   
          for (uint8_t i=0; i<5; i=i+1) {
            strip.setPixelColor(stars[i], 0);
            stars[i] = random(0,120);
            strip.setPixelColor(stars[i], strip.Color(0, 0, 150));
            //strip.setPixelColor(stars[i], Wheel( (ms*2) % 255));
          }
          
          //Milliseconds
          if (ms>=bs) {
            strip.setPixelColor(ms-bs, 0);
          } else {
            strip.setPixelColor(strip.numPixels()-bs+ms, 0);
          }
          
          strip.setPixelColor(h*2, hour);
          strip.setPixelColor(h*2-1, hour);
          
          strip.setPixelColor(m*2, minute);
          strip.setPixelColor(m*2-1, minute);
          
          strip.setPixelColor(s*2, second);
          strip.setPixelColor(s*2-1, second);
          
          strip.setPixelColor(ms, millisecond);
          
          
          strip.show();
          delay(wait);
          
        }
        
      }
      
    }
    
  }
       
}
/*
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}
*/

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

