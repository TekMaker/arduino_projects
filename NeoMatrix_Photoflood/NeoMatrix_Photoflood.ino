/// Neomatrix Photoflood by R.Beardmore 11 December 2020
/// This is designed to light a whole RGB Addressable NeoMatrix LED panel (WS2812)
/// by varing the intensity of the brightness, red, green and blue values
/// to create a variable and controllablelighting system for photography
/// and videography shooting. It is based on the Adafruit NeoMatrix library
/// feel free to modify this code and learn from it. *** Merry Christmas ***
/// TekMaker.co.uk

/// this is the photoflood only version. There is also a photoflood message version
/// which requires and additional push button. This will allow different messages to be displayed too.

/// Load AdadFruit Libraries
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#definde PSTR // Make Arduino Due Happy
#endif

# define DATA_PIN 7  // the datapin used to connect to the WS2812 on UNO

// define the analog input pins for the variable resisitors
const int brightINPUT = 14;
const int redINPUT = 15;
const int greenINPUT = 16;
const int blueINPUT = 17;

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
// ------------------------------------------------------------------------------

// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, DATA_PIN,
                            NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);

/// *** you may need to play around with the above values as mentioned in the video ***
/// *** as not all WS2812/NeoMatrix displays have the same orientation, see the manufacturer's specs ***

const uint16_t colors[] = { matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

// photoflood declaration
#define NUM_LEDS 256 // number of LEDs to eb controlled
#define COLOR_ORDER RGB // we want to program the leds in that order

void setup() {
  Serial.begin(9600);
  Serial.println("Setup ran..");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(brightINPUT, INPUT);
  pinMode(redINPUT, INPUT);
  pinMode(greenINPUT, INPUT);
  pinMode(blueINPUT, INPUT);
  pinMode(DATA_PIN, OUTPUT);

  // matrix
  matrix.begin();
  matrix.clear();
  matrix.setTextWrap(false);
  matrix.setTextColor(colors[0]);
  matrix.setBrightness(25);
  matrix.fillScreen(matrix.Color(255, 255, 255));// test leds
  matrix.show();
  delay(1000);
  matrix.fillScreen(matrix.Color(0, 0, 0));// then clear leds
  matrix.show();
  delay(50);
}

int x = matrix.width();
int pass = 0;

void loop()  // fill the screen with a single color
{
  // these print commands are for Serial debugging in development
  Serial.println("bright=" + String(analogRead(brightINPUT)));
  Serial.println("red=" + String(analogRead(redINPUT)));
  Serial.println("green=" + String(analogRead(greenINPUT)));
  Serial.println("blue=" + String(analogRead(blueINPUT)));

  int brightLEVEL = analogRead(brightINPUT) / 4;
  matrix.setBrightness(brightLEVEL);
  int redLEVEL = analogRead(redINPUT) / 4;
  int greenLEVEL = analogRead(greenINPUT) / 4;
  int blueLEVEL = analogRead(blueINPUT) / 4;
  matrix.clear();
  // lights the whole screen in one go, fastest way ever!
  matrix.fillScreen(matrix.Color(redLEVEL, greenLEVEL, blueLEVEL));
  matrix.show();

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
}
