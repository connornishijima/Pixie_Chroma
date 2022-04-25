/*----------------------------------------------------------------------------

  Pixie Chroma | Twitter_Follower_Count.ino
  by Connor Nishijima Apr. 2022
  with JSON cheat discovered by https://github.com/Fardenco

  Original post:
  https://github.com/witnessmenow/arduino-twitter-api/issues/2
  -------------------------------------

  This sketch will take your Twitter username, and using an undocumented
  JSON endpoint will pull your live Twitter Follower count down to your
  displays!

  This hacky method does not use the Twitter API, and may be subject to
  future failure if the URL is broken by changes.
  
----------------------------------------------------------------------------*/
#define TWITTER_USERNAME "lixielabs" // Change this to your own, if you want!
/*----------------------------------------------------------------------------
  
  This demo uses WiFiManager.h, which means you'll need to configure your WiFi
  credentials at runtime. Upon boot, if WiFiManager does not have credentials
  saved it will open up an access point called "Pixie_Chroma_AP". Connect to
  this temporary network with your phone, and go to http://192.168.4.1/ in your
  phone's browser. Here, you'll see a configuration menu where you can tell your
  microcontroller what your WiFi settings are, and it will remember them! After
  entering credentials, the ESP will reboot and attempt to run this code again.

----------------------------------------------------------------------------*/

#include "Pixie_Chroma.h" // ... Include library
PixieChroma pix; // ............ Get class object

#define DATA_PIN  5  // GPIO to use for Pixie Chroma data line
#define PIXIES_X  2  // Total amount and arrangement
#define PIXIES_Y  1  // of Pixie PCBs = 2 x 1

// Include classes ------------------------
#if defined(ESP8266)
  #include <ESP8266HTTPClient.h>
#elif defined(ESP32)
  #include <HTTPClient.h>
#endif

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h> // ArduinoJSON for parsing results
// ----------------------------------------

void setup() {
  Serial.begin(115200); // Open Serial

  // Initializes the displays, and sets things
  // like the default power budget for you.
  pix.begin( DATA_PIN, PIXIES_X, PIXIES_Y );

  // Set color animation to a RAINBOW shifting LEFT at half speed:
  pix.set_palette(RAINBOW);
  pix.set_color_animation(ANIMATION_PALETTE_SHIFT_LEFT);
  pix.set_color_animation_speed(0.5);

  pix.set_brightness(32); // 0 - 255

  pix.clear();
  pix.print("....");
  pix.show();

  // Connect to WiFi
  init_wifi();
}

void loop() {
  static int32_t follower_count; // "static" keeps this around when loop() starts over
  static uint32_t next_check = millis(); // Check immediately on first loop

  if(millis() >= next_check){ // If it's time to check follower count again:
    next_check += 30000; // Set the next check 30s from now
    follower_count = get_follower_count(TWITTER_USERNAME); // Fetch new count

    // Print debug to Serial
    Serial.print('@');
    Serial.print(TWITTER_USERNAME);
    Serial.print(" followers: ");
    Serial.println(follower_count);
  }

  // This part below is run on every loop() to run animation smoothly

  pix.clear(); // Clear the display buffer
  // pix.print("Followers: ");
  pix.print(follower_count); // Print follower count
  pix.show(); // Send updated frame to displays
}

void init_wifi() {
  Serial.println("CONNECTING TO WIFI...");
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  wm.setWebServerCallback(config_mode);
  if (!wm.autoConnect("Pixie_Chroma_AP")) {
    Serial.println("Failed to connect!");
    delay(1000);
    ESP.restart();
  }
  else { // Connected
    Serial.println("WIFI CONNECTED");
  }
}

int32_t get_follower_count(String username) {
  WiFiClient client;
  HTTPClient http;

  // Get JSON data about a user from Twitter cheat:
  http.begin(client, "http://cdn.syndication.twimg.com/widgets/followbutton/info.json?screen_names=" + username);
  int http_code = http.GET();

  if (http_code <= 0) {
    Serial.println("Error : no HTTP code");
    return -1;
  }

  // Get String of response
  String answer = http.getString();
  http.end();

  // Removing brackets [] around the json as they're making it not readable by the parser
  answer.remove(0, 1);
  answer.remove(answer.length() - 1, 1);

  // Parse JSON
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, answer);
  JsonObject root = doc.as<JsonObject>();

  // Pull count
  if (root.containsKey("followers_count"))
  {
    return root["followers_count"].as<long>();
  }

  Serial.println("Incompatible JSON");
  return -1;
}

void config_mode(){
  Serial.println("Entered config mode @ Pixie_Chroma_AP");
  pix.clear();
  pix.print("WIFI");
  pix.show();
}
