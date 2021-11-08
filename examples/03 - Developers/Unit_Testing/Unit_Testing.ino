/*----------------------------------------------------------------------------

  Pixie Chroma | Unit_Test.ino
  by Connor Nishijima Nov. 2021
  -----------------------------

  This sketch is for development use only, and runs automated units tests
  of several PixieChroma class functions. The result should always be
  "PASS", any other results should be opened as an issue here:

  https://github.com/connornishijima/Pixie_Chroma/issues/new?labels=bug&template=bug_report.md&title=Unit%20Test%20Fail

  Results will appear on the Serial Monitor (Ctrl+Shift+M) after upload.

----------------------------------------------------------------------------*/

#include "Pixie_Chroma.h" // ... Include library
PixieChroma pix; // ............ Get class object

bool result = false; // Test result stored here

void setup() {
  delay(250);
  Serial.begin(250000); // Open Serial connection

  Serial.println(F("\n\n******** PIXIE CHROMA UNIT TEST REPORT ********\n"));
  result = pix.unit_tests(); // Run all unit tests

  pix.set_animation(ANIMATION_NULL); // Allow manual coloring
  pix.set_brightness(255);
  pix.clear();
}

void loop() {
  // Print results indefinitely
  if(result == true){
    pix.clear();
    pix.color(CRGB(0,255,0));
    pix.print("PASS");
    pix.show();
    delay(500);
    
    pix.clear();
    pix.show();
    delay(500);
  }
  else if(result == false){
    pix.clear();
    pix.color(CRGB(255,0,0));
    pix.print("FAIL");
    pix.show();
    delay(500);
    
    pix.clear();
    pix.show();
    delay(500);
  }
}