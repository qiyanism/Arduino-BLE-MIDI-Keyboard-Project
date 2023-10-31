#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32.h>

// BLEMIDI_CREATE_DEFAULT_INSTANCE()
BLEMIDI_CREATE_INSTANCE("SOMETHING WEIRD!!", MIDI)

const int buttonPins[] = {4, 16, 17, 5, 18, 19, 21, 22, 12, 14, 27, 26, 25, 32};
const byte midiNotes[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77 , 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127};
const char *musicalNotes[] = { "C -1", "C# -1", "D -1", "Eb -1", "E -1", "F -1", "F# -1", "G -1", "Ab -1", "A -1", "Bb -1", "B -1", "C 0", "C# 0", "D 0", "Eb 0", "E 0", "F 0", "F# 0", "G 0", "Ab 0", "A 0", "Bb 0", "B 0", "C 1", "C# 1", "D 1", "Eb 1", "E 1", "F 1", "F# 1", "G 1", "Ab 1", "A 1", "Bb 1", "B 1", "C 2", "C# 2", "D 2", "Eb 2", "E 2", "F 2", "F# 2", "G 2", "Ab 2", "A 2", "Bb 2", "B 2", "C 3", "C# 3", "D 3", "Eb 3", "E 3", "F 3", "F# 3", "G 3", "Ab 3", "A 3", "Bb 3", "B 3", "C 4", "C# 4", "D 4", "Eb 4", "E 4", "F 4", "F# 4", "G 4", "Ab 4", "A 4", "Bb 4", "B 4", "C 5",  "C 5", "C# 5", "D 5", "Eb 5", "E 5", "F 5", "F# 5", "G 5", "Ab 5", "A 5", "Bb 5", "B 5",  "C 6", "C# 6", "D 6", "Eb 6", "E 6", "F 6", "F# 6", "G 6", "Ab 6", "A 6", "Bb 6", "B 6",  "C 7", "C# 7", "D 7", "Eb 7", "E 7", "F 7", "F# 7", "G 7", "Ab 7", "A 7", "Bb 7", "B 7",  "C 8", "C# 8", "D 8", "Eb 8", "E 8", "F 8", "F# 8", "G 8", "Ab 8", "A 8", "Bb 8", "B 8",  "C 9", "C# 9", "D 9", "Eb 9", "E 9", "F 9", "F# 9", "G 9", "dummy"};
int octave = 0;
int pitch = 0;
const int ledPin = 13;
const int octaveUp = 32;
const int octaveDown = 34;
const int pitchUp = 23;
const int pitchDown = 2; 


bool noteSent[] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
bool octaveUpFlag =  false;
bool octaveDownFlag =  false;
bool pitchUpFlag =  false;
bool pitchDownFlag =  false;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 13; i++) {
    pinMode(buttonPins[i], INPUT);
  }
  pinMode(ledPin, OUTPUT);
  pinMode(octaveUp, INPUT);
  pinMode(octaveUp, INPUT);
  pinMode(octaveDown, INPUT);
  pinMode(pitchUp, INPUT);
  pinMode(pitchDown, INPUT);

  MIDI.begin();
}

void loop() {

   digitalWrite(ledPin, HIGH);


  for (int i = 0; i < 13; i++) {
    bool btnState = digitalRead(buttonPins[i]);

    if (btnState == HIGH && !noteSent[i]) {
      MIDI.sendNoteOn(midiNotes[i + 60 + (octave * 12) + pitch], 127, 1);
      Serial.print(musicalNotes[i+ 60 + (octave * 12) + pitch]);
      Serial.println(" played!");
      noteSent[i] = true;
      
    } else if (btnState == LOW && noteSent[i]) {
      noteSent[i] = false; // Reset the flag only when the button is released
      MIDI.sendNoteOff(midiNotes[i + 60 + (octave * 12) + pitch], 0, 1);
      
    }

  /// octave up///
  if (digitalRead(octaveUp) == HIGH && !octaveUpFlag) {
    octave = octave + 1;
    Serial.print("octave ");
    Serial.println(octave);
    octaveUpFlag = true;
    }
  else if (digitalRead(octaveUp) == LOW && octaveUpFlag) {
    octaveUpFlag = false;
    }

  /// octave down///
  if (digitalRead(octaveDown) == HIGH && !octaveDownFlag) {
    octave = octave - 1;
    Serial.print("octave ");
    Serial.println(octave);
    octaveDownFlag = true;
    }
  else if (digitalRead(octaveDown) == LOW && octaveDownFlag) {
    octaveDownFlag = false;
    }
  
  
  /// pitch up///
  if (digitalRead(pitchUp) == HIGH && !pitchUpFlag) {
    pitch = pitch + 1;
    Serial.print("pitch ");
    Serial.println(pitch);
    pitchUpFlag = true;
    }
  else if (digitalRead(pitchUp) == LOW && pitchUpFlag) {
    pitchUpFlag = false;
    }
 

  }

  /// pitch down///
  if (digitalRead(pitchDown) == HIGH && !pitchDownFlag) {
    pitch = pitch - 1;
    Serial.print("pitch ");
    Serial.println(pitch);
    pitchDownFlag = true;
    }
  else if (digitalRead(pitchDown) == LOW && pitchDownFlag) {
    pitchDownFlag = false;
    }
    
  
}