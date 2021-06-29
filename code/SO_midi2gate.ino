#include <MIDI.h>

// Using the https://github.com/FortySevenEffects/arduino_midi_library/ library
// this means that midi-thru is enabled by default :-)
// @TODO: github link
//

// Settings

// MIDI channel to listen to (1-16, omni is not supported currently).
constexpr byte MIDI_CHANNEL = 10;

// MIDI note to map to the first LED.
constexpr byte FIRST_NOTE = 36;

// Do a quick LED self-test when booting. Set to false to disable.
constexpr bool SELFTEST = false;

constexpr byte GATE01 = 2;
constexpr byte GATE02 = 3;
constexpr byte GATE03 = 4;
constexpr byte GATE04 = 5;
constexpr byte GATE05 = 6;
constexpr byte GATE06 = 7;
constexpr byte GATE07 = 13;
constexpr byte GATE08 = 12;
constexpr byte GATE09 = 11;
constexpr byte GATE10 = 10;
constexpr byte GATE11 = 9;
constexpr byte GATE12 = 8;


byte gates[] = {GATE01, GATE02, GATE03, GATE04, GATE05, GATE06, GATE07, GATE08, GATE09, GATE10, GATE11, GATE12};
byte current_gate;
constexpr int ngates = 12;



uint8_t i;

MIDI_CREATE_DEFAULT_INSTANCE();

void handleNoteOn(byte channel, byte note, byte velocity)
{
    if (channel == MIDI_CHANNEL){
      digitalWrite(gates[note-FIRST_NOTE], HIGH);
    }
}

void handleNoteOff(byte channel, byte note, byte velocity)
{
  if (channel == MIDI_CHANNEL){
      digitalWrite(gates[note-FIRST_NOTE], LOW);
    }
}

void setup()
{
    for( i = 0; i < ngates; ++i ){
      pinMode(gates[i], OUTPUT);
      digitalWrite(gates[i], LOW);
    }

    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);

    // Use OMNI channel here, to midi thru on everything
    // not sure if necessary... @TODO: check!
    MIDI.begin(MIDI_CHANNEL_OMNI);


    if (SELFTEST) {
      for( i = 0; i < ngates; ++i ){
        delay(100);
        digitalWrite(gates[i], HIGH);
      }
      delay(100);
      for( i = 0; i < ngates; ++i ){
        digitalWrite(gates[i], LOW);
      }
    }
}

void loop()
{   MIDI.read();
}
