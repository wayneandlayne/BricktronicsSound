// Bricktronics Example: SoundSensorBricktronicsBreakoutBoard
// http://www.wayneandlayne.com/bricktronics
//
// Sound sensor readings are taken as fast a possible and used to generate a
// simple bar graph printed out over the serial console. Be sure to set
// your serial console to 115200 baud. The sound sensor library reports the
// measured sound value with a unitless value between 0 (very quiet) and
// 1023 (very loud).
//
// The sound sensor is described by LEGO as a "sound pressure level" sensor,
// that has two modes: dB and dBA. dB mode measures all frequencies equally,
// while dBA mode (A = "adjusted") tries to mimic human ear sensitivity, by
// ignoring frequencies outside the normal limits of human hearing.
//
// Hardware used:
// * Wayne and Layne Bricktronics Breakout Board
//   https://store.wayneandlayne.com/products/bricktronics-breakout-board.html
// * LEGO NXT Sound Sensor
//
// Software libraries used:
// * Wayne and Layne BricktronicsSound library
//   https://github.com/wayneandlayne/BricktronicsSound
//
// Written in 2016 by Matthew Beckler and Adam Wolf for Wayne and Layne, LLC
// To the extent possible under law, the author(s) have dedicated all
//   copyright and related and neighboring rights to this software to the
//   public domain worldwide. This software is distributed without any warranty.
// You should have received a copy of the CC0 Public Domain Dedication along
//   with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 


// Include the BricktronicsSound library
#include <BricktronicsSound.h>


// Connect these pins on the Bricktronics Breakout board:
//  Pin 1 - Connect to any analog input pin (inputPin)
//  Pin 2 - Connect to Ground
//  Pin 3 - Connect to Ground
//  Pin 4 - Connect to 5V
//  Pin 5 - Connect to any digital pin (dbPin)
//  Pin 6 - Connect to any digital pin (dbaPin)
//
// The BricktronicsSound() arguments are:
//      inputPin (pin 1), dbPin (pin 5), dbaPin (pin 6)
// There is one consideration for pin assignments:
// A. inputPin needs to be an analog pin
//
BricktronicsSound s(14, 12, 11);


void setup()
{
  // Be sure to set your serial console to 115200 baud
  Serial.begin(115200);

  // Initialize the sound sensor connections
  s.begin();
}

// This function draws a nice bar graph for displaying sound levels.
void printLine(uint16_t val, char dot)
{
  #define BUF_LEN 30
  char buffer[BUF_LEN];
  uint8_t x = (val * (uint16_t) BUF_LEN) / 1023;
  for (uint8_t i = 0; i < BUF_LEN; i++)
  {
    buffer[i] = ((i < x) ? dot : ' ');
  }
  buffer[BUF_LEN - 1] = '\0';
  Serial.println(buffer);
}

long switchTime;

void loop()
{
  // Spend 5 seconds in db mode
  Serial.println("----- Switching to DB mode -----");
  s.setMode(SOUND_SENSOR_MODE_DB);
  switchTime = millis() + 5000;
  while (millis() < switchTime)
  {
    printLine(s.value(), '*');
  }

  // Spend 5 seconds in dba mode
  Serial.println("----- Switching to DBA mode -----");
  s.setMode(SOUND_SENSOR_MODE_DBA);
  switchTime = millis() + 5000;
  while (millis() < switchTime)
  {
    printLine(s.value(), 'a');
  }
}

