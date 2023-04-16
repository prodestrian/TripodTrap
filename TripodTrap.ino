#include "HT16K33.h"
#include "TimedAction.h"

HT16K33 bargraph = HT16K33();

int currentPixel = 0;
int numPixels = 10;
bool isForward = true;

TimedAction bargraphTimer = TimedAction(30, []() {
    for (size_t i = 0; i < numPixels; i++) {
        int pixelState = (i == currentPixel) ? 1 : 0;
        if (!isForward) {
            pixelState = (i == (numPixels - 1 - currentPixel)) ? 1 : 0;
        }
        bargraph.setPixel(i, 0, pixelState);
    }
    bargraph.write();

    currentPixel++;
    if (currentPixel > numPixels) {
        currentPixel = 0;
        // Flip direction
        isForward = !isForward;
    }
});

#define FLASHER_PIN_0 6
#define FLASHER_PIN_1 7

int currentFlasher = 0;
TimedAction flasherTimer = TimedAction(300, []() {

    digitalWrite(FLASHER_PIN_0, (currentFlasher == 0));
    digitalWrite(FLASHER_PIN_1, (currentFlasher == 1));

    currentFlasher = (currentFlasher == 0) ? 1 : 0;
});

// must be a PWM pin
#define ANALOG_METER_PIN 5
int currentLevel = 0;
TimedAction gaugeTimer = TimedAction(200, []() {
    analogWrite(ANALOG_METER_PIN, currentLevel);

    currentLevel = currentLevel + random(-25, 25);
    // minimum 50
    currentLevel = (currentLevel < 50) ? 50 : currentLevel;
    currentLevel = (currentLevel > 255) ? 255 : currentLevel;
    gaugeTimer.setInterval(random(400, 3000));
});

const int ANTENNA_PINS[3] = {8,9,10};

int currentAntenna = 0;
TimedAction antennaTimer = TimedAction(250, []() {
    for (size_t i = 0; i < 3; i++)
    {
        digitalWrite(ANTENNA_PINS[i], (i != currentAntenna));
    }

    currentAntenna = (currentAntenna == 2) ? 0 : currentAntenna+1;
});

bool isStartup = true;
void setup()
{
    bargraph.init(0x70);
    bargraph.setBrightness(15);
    delay(300);

    pinMode(FLASHER_PIN_0, OUTPUT);
    pinMode(FLASHER_PIN_1, OUTPUT);

    for (size_t i = 0; i < 3; i++)
    {
        pinMode(ANTENNA_PINS[i], OUTPUT);
    }

    //Serial.begin(9600);
}


void loop()
{
    if (isStartup) {
        // Startup sequence
        //Serial.println("Startup");
        for (size_t i = 0; i < numPixels; i++) {
            bargraph.setPixel(i, 0, 1);
            bargraph.write();
            analogWrite(ANALOG_METER_PIN, (i+1) * 25);
            // Serial.print(millis());
            // Serial.print(' : ');
            // Serial.println(i);
            delay(500);
        }


        //Serial.println("Ready");
        delay(3000);

        bargraph.clear();
        bargraph.write();
        delay(1000);

        isStartup = false;
        // Start analog meter in the middle
        currentLevel = 125;
        return;
    }

    //Serial.println("Loop");

    // Standard loop
    bargraphTimer.check();
    flasherTimer.check();
    gaugeTimer.check();
    antennaTimer.check();
}
