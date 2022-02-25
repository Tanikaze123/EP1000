/*******************************************************************
 * A multi-mode Macro keyboard with Arduino Pro Micro using      
 * row column matrix.
 * This is a blank sketch to understand key layout and assignments. 
 * (c) 2020 Ryan Bates

 *******************************************************************/
// ----------------------------
// Standard Libraries
// ----------------------------

#include "Keyboard.h"
#include <Encoder.h> //Library for simple interfacing with encoders (up to two)
Encoder RotaryEncoderA(A3, A2); //the top encoder (encoder A)
Encoder RotaryEncoderB(A1, A0);  //the bottom encoder (encoder B)
#include <Keypad.h>


const byte ROWS = 5;
const byte COLS = 7;

char keys[ROWS][COLS] = {
  {'1', '2', '3', '4', '5', 'p', 'l'},  // 4th
  {'6', '7', '8', '9', 'A', 'B', 'm'}, //rotary enc bottom
  {'C', 'D', 'E', 'F', 'G', 'H', 'k'},  //rotary enc top
  {'s', 'I', 'J', 'K', 'L' ,'b', 'n'}, //top
  {'a', 'd', 'f', 'g', 'h', 'v', 'M'}, // single
};

// Variables will change:
int modePushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

long positionEncoderA  = -999; //encoderA LEFT position variable
long positionEncoderB  = -999; //encoderB RIGHT position variable

const int ModeButton;    // the pin that the Modebutton is attached to
const int Mode1;
const int Mode2; //Mode status LEDs

byte rowPins[ROWS] = {15, 14, 16, 10, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2,3,4,5,6,7,8}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600); // initialize serial communication:
  Keyboard.begin();
}


void loop() {
char key = keypad.getKey();
      encoderA();
      encoderB();
  
checkModeButton();

  switch (0) { // switch between keyboard configurations:
    case 0:    //  Application Alpha or MODE 0

      digitalWrite(Mode1,LOW); digitalWrite(Mode2,LOW); //indicate what mode is loaded
       if (key) {
    Serial.println(key);
    switch (key) {
      case '1': 
        Keyboard.println("Alpha key1"); break;
      case '2': 
        Keyboard.println("Alpha key2"); break;
      case '3':
        Keyboard.println("Alpha key3"); break;
      case '4':
        Keyboard.println("Alpha key4"); break;
      case '5':
        Keyboard.println("Alpha key5"); break;
      case '6':
        Keyboard.println("Alpha key6"); break;
      case '7':
        Keyboard.println("Alpha key7"); break;
      case '8':
        Keyboard.println("Alpha key8"); break;
      case '9':
        Keyboard.println("Alpha key9"); break;
      case '0':
        Keyboard.println("Alpha key10"); break;
      case 'A': 
        Keyboard.println("Alpha key11"); break;
      case 'B':
        Keyboard.println("Alpha key12"); break;
      case 'C':
        Keyboard.println("Alpha key13"); break;
      case 'D':
        Keyboard.println("Alpha key14"); break;
      case 'E':
        Keyboard.println("Alpha key15"); break;
      case 'F': 
        Keyboard.println("Alpha key16"); break;
    }
    delay(100); Keyboard.releaseAll(); // this releases the buttons 
  }
      break;
  }
  delay(1);  // delay in between reads for stability
}

void checkModeButton(){
  buttonState = digitalRead(ModeButton);
  if (buttonState != lastButtonState) { // compare the buttonState to its previous state
    if (buttonState == LOW) { // if the state has changed, increment the counter
      // if the current state is LOW then the button cycled:
      modePushCounter++;
      Serial.println("pressed");
      Serial.print("number of button pushes: ");
      Serial.println(modePushCounter);
    } 
    delay(50); // Delay a little bit to avoid bouncing
  }
  lastButtonState = buttonState; // save the current state as the last state, for next time through the loop
   if (modePushCounter >3){ //reset the counter after 4 presses (remember we start counting at 0)
      modePushCounter = 0;}
}

void encoderA(){
  long newPos = RotaryEncoderA.read()/4; //When the encoder lands on a valley, this is an increment of 4.
  
  if (newPos != positionEncoderA && newPos > positionEncoderA) {
    positionEncoderA = newPos;
    Serial.println(positionEncoderA);
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.release(KEY_LEFT_ARROW);                      }

  if (newPos != positionEncoderA && newPos < positionEncoderA) {
    positionEncoderA = newPos;
    Serial.println(positionEncoderA);
    Keyboard.press(KEY_RIGHT_ARROW);
    Keyboard.release(KEY_RIGHT_ARROW);                      }
}

void encoderB(){
  long newPos = RotaryEncoderB.read()/4; //When the encoder lands on a valley, this is an increment of 4.
  if (newPos != positionEncoderB && newPos > positionEncoderB) {
    positionEncoderB = newPos;
    Serial.println(positionEncoderB);
    Keyboard.press(KEY_UP_ARROW);
    Keyboard.release(KEY_UP_ARROW);                      }

  if (newPos != positionEncoderB && newPos < positionEncoderB) {
    positionEncoderB = newPos;
    Serial.println(positionEncoderB);
    Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.release(KEY_DOWN_ARROW);                      }
}
