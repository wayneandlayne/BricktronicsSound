# BricktronicsSound API

This library interfaces with LEGO NXT sound sensors. It can be used with the [Bricktronics Shield](https://store.wayneandlayne.com/products/bricktronics-shield-kit.html), [Bricktronics Megashield](https://store.wayneandlayne.com/products/bricktronics-megashield-kit.html), or standalone with the [Bricktronics Breakout Board](https://store.wayneandlayne.com/products/bricktronics-breakout-board.html). For the shield/megashield, use the constructor below with the `BricktronicsSensorSettings` struct, otherwise use the constructor below that accepts the pin numbers.

# Connection with [Bricktronics Shield](https://store.wayneandlayne.com/products/bricktronics-shield-kit.html)

Use the sound sensor with any sensor port on the Bricktronics Shield. For sensor port 3 or 4, use the jumpers to connect pins 2-3 and 4-5.

Constructor usage for Bricktronics Shield
```C++
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <BricktronicsShield.h>
#include <BricktronicsSound.h>
BricktronicsSound s(BricktronicsShield::SENSOR_1);
```

# Connection with [Bricktronics Megashield](https://store.wayneandlayne.com/products/bricktronics-megashield-kit.html)

Use the sound sensor with any sensor port on the Bricktronics Megashield. Use the jumpers to connect pins 2-3 and 4-5.

Constructor usage for Bricktronics Megashield
```C++
#include <BricktronicsMegashield.h>
#include <BricktronicsSound.h>
BricktronicsSound s(BricktronicsMegashield::SENSOR_1);
```

# Connection with [Bricktronics Breakout Board](https://store.wayneandlayne.com/products/bricktronics-breakout-board.html)

* Pin 1 - Connect to any analog input pin (this is `inputPin` below)
* Pin 2 - Connect to Ground
* Pin 3 - Connect to Ground
* Pin 4 - Connect to 5V
* Pin 5 - Connect to any digital pin (this is `dbPin` below)
* Pin 6 - Connect to any digital pin (this is `dbaPin` below)

Constructor usage for Bricktronics Breakout Board:
```C++
#include <BricktronicsSound.h>
BricktronicsSound s(14, 12, 11); // Constructor arguments: inputPin, dbPin, dbaPin
```

# Quick Example

```C++
#include <BricktronicsSound.h>

// Use one of the constructor options listed above.
BricktronicsSound s(14, 12, 11);

void setup()
{
    Serial.begin(115200);
    // If using a Bricktronics Shield, you need to call
    // BricktronicsShield::begin();
    s.begin();
    s.setMode(SOUND_SENSOR_MODE_DBA);
}

void loop()
{
    Serial.println(s.value());
    delay(50);
}
```

# Constructors and `begin()`

#### `BricktronicsSound(uint8_t inputPin, uint8_t dbPin, uint8_t dbaPin);`

Constructor - Simple constructor that accepts the input analog pin number, plus the pin numbers for the two digital outputs that control the sensor mode.

**Parameters**

* `uint8_t inputPin` - The Arduino pin number where the sensor's pin 1 is connected. Must have analog input.
* `uint8_t dbPin` - The Arduino pin number where the sensor's pin 5 is connected. Digital output.
* `uint8_t dbaPin` - The Arduino pin number where the sensor's pin 6 is connected. Digital output.


#### `BricktronicsSound(const BricktronicsSensorSettings &settings)`

Constructor - Advanced constructor that accepts a SensorSettings struct to also override the low-level Arduino functions.

**Parameters**

* `const BricktronicsSensorSettings &settings` - A const reference to the struct containing all the sensor settings. Get these structs from the [BricktronicsShield](https://github.com/wayneandlayne/BricktronicsShield) or [BricktronicsMegashield](https://github.com/wayneandlayne/BricktronicsMegashield) library.

#### `void begin(void)`

Call this function once for each instance during your setup() function.


# Basic sound sensor functions

#### `uint16_t value(void)`

Basic sensor read function. Scale is from 0 (very quiet) to 1023 (very loud), but usually the actual range is about 250 (quiet room) to 980 (next to a loudspeaker).

#### `void setMode(uint8_t mode)`

Change the sound sensor mode between DB and DBA. Function argument is one of the enum values below. DB mode is a raw measure of the sound pressure level ("loudness"). DBA mode applies an adjustment curve to account for the typical frequency response of the human ear. DBA readings will more closely match a human's perception of the sound pressure level than the DB readings.

#### `uint8_t getMode(void)`

Returns the current sound sensor mode. Check for equality with one of the enum values below.


# Enumerations and constants

#### Mode types for `setMode()`

* `SOUND_SENSOR_DB` - Raw, un-adjusted measure of the sound pressure level.
* `SOUND_SENSOR_DBA` - Apply adjustment curve to account for typical human hearing frequency response.

