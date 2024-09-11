extern void experiment();

#include "Arduino.h"

extern "C" {

void _close() {}

void _getpid() {}

void _kill() {}

void _lseek() {}

void _read() {}

void _write() {}

// arduino calls

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);

    experiment();
}

}
