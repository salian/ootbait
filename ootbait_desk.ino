/**************************************************************************
  Ootbait standing desk firmware (Arduino)

  Basic features include sit/stand motions and presets.

  Advanced features include automatic sit/stand scheduling and LAN/browser based control.

  Tested to run on an Arduino Uno with ESP8266 Wifi.

  Written by Pranab Salian for personal use, based on code from
  Adafruit, Cytron and others from the open source community.
  BSD license, check license.txt for more information
  All text above must be included in any redistribution.
 **************************************************************************/

//  Display Setup   -------------------------------------------------------

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  // See datasheet or use IIC Scanner to get the screen address

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Joystick Setup  -------------------------------------------------------

#include <Joystick.h>
#include <AxisJoystick.h>

#define SW_PIN 5
#define VRX_PIN A0
#define VRY_PIN A1

Joystick* joystick;

// Delay Timer Setup ---------------------------------------

unsigned long displaySleepTimer = 0;
const unsigned long displayOffDelay = 10000;  // Put the display screen to sleep after this time
bool displayIsOn = false;


// Arduino Initial Setup ---------------------------------------

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with the splash screen.
  display.display();
  delay(3000); // Pause for 2 seconds

  joystick = new AxisJoystick(SW_PIN, VRX_PIN, VRY_PIN);
}

// Main Loop -----------------------------------------------

void loop() {
  // put your main code here, to run repeatedly:

  joystick->singleRead();
  if (joystick->isDown()) {
    goDown();
  }
  if (joystick->isUp()) {
    goUp();
  }
  if (joystick->isLeft()) {
    Serial.println(F("LEFT"));
    //    goLeft();
    char move_direction = 'L';
    navigateMenu(move_direction);
    delay(500);
  }
  if (joystick->isRight()) {
    Serial.println(F("RIGHT"));
    char move_direction = 'R';
    navigateMenu(move_direction);
    delay(500);
  }
  if (joystick->isPress()) {
    Serial.println(F("SELECT"));
    selectMenu();
    delay(500);
  }

  delay(25); // optionally, to delay / debounce - review later.

  // Switch the display off if sufficient time has elapsed since last update
  if (displayIsOn == true) {
    if ((unsigned long)(millis() - displaySleepTimer) > displayOffDelay) {     // delay 5 seconds
      // Show a "sleeping" message before sleeping?
      //display.clearDisplay();
      //display.setTextSize(1);
      //display.setCursor(0, 32);
      //display.println("      sleeping");
      //display.display();
      //delay(200);
      display.clearDisplay();
      display.display();
      displayIsOn = false;
    }
  }
}

// Movement Functions --------------------------------------------

void goDown() {
  Serial.println(F("Command: Move Down"));
  drawMovingArrow(F("DOWN"));
  drawStaticArrow(DIRECTION_DOWN);
  drawMovingArrow(F("DOWN"));
  delay(25);
}

void goUp() {
  Serial.println(F("Command: Move Up"));
  drawMovingArrow(F("UP"));
  drawStaticArrow(DIRECTION_UP);
  drawMovingArrow(F("UP"));
  delay(25);
}


//  State Machine for Screen Selection  ---------------------

int currentScreen = 0;
int totalScreens = 6;  // 0 - 6 = 7 screens

int nextScreen(int currentScreen) {
  if (currentScreen < totalScreens) {
    currentScreen++;
  }
  else if (currentScreen == totalScreens) {
    currentScreen = 0;
  }
  return currentScreen;
}

int previousScreen(int currentScreen) {
  if (currentScreen > 0) {
    currentScreen--;
  }
  else if (currentScreen == 0) {
    currentScreen = totalScreens;
  }
  return currentScreen;
}


void navigateMenu(const char *move_direction) {
  // Serial.println(F("Select Left/Right"));
  // Serial.print("move_direction: "); Serial.println(move_direction);
  // Serial.print("currentScreen: "); Serial.print(currentScreen); Serial.print(" nextScreen: "); Serial.println( nextScreen(currentScreen));
  if (move_direction == 'L') {
    currentScreen =  nextScreen(currentScreen);
  }
  else if (move_direction == 'R') {
    currentScreen =  previousScreen(currentScreen);
  }
  else {
    Serial.println("Err: move_direction did not match L or R");
  }

  //  char Str[32];
  //  Str[1] = (char) nextScreen(currentScreen);
  Serial.print("Updated currentScreen "); Serial.println(currentScreen);
  showScreen();
  delay(50);
}


void showScreen() {
  switch (currentScreen) {
    case 0:
      // logo / info screen - change to logo
      display.clearDisplay();
      display.setTextWrap(true);
      display.setTextColor(SSD1306_WHITE);
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.println(F("\n"));
      display.println(F("    Oot Bait Desk"));
      display.println(F(""));
      display.println(F("      (C)  2021"));
      display.println(F("    Pranab Salian"));
      display.println(F("     GPL License"));
      display.display();
      break;
    case 1:
    case 2:
    case 3:
    case 4:
      // Show PRESET N on-screen
      char preset[3];
      itoa(currentScreen, preset, 10);
      showtext(preset);
      break;
    case 5:
      // WIFI SETTINGS
      display.clearDisplay();
      display.setTextWrap(true);
      display.setTextColor(SSD1306_WHITE);
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.print(F("   Wi-Fi"));
      display.display();
      break;
    case 6:
      // PRESETS SETTINGS SCREEN or LAN Access URL
      // const char textLAN[26] = "Access settings on the LAN";
      display.clearDisplay();
      display.setTextColor(SSD1306_WHITE);
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.setTextWrap(true);
      // display.print(F("Access settings on the LAN"));
      display.println(F(" SETTINGS\n"));
      display.setTextSize(1);
      display.println(F("Visit 192.168.255.255"));
      display.println(F("to access settings on"));
      display.println(F("local Wi-Fi."));
      display.display();
      // showtext("Access settings on the LAN");
      break;
    default:
      // unknown selection
      Serial.println("Err: Unknown Screen requested.");
      break;
  }
  // Set up the screen-off timer
  displaySleepTimer = millis();
  displayIsOn = true;
}




void selectMenu() {

  //  // Create a duplicate buffer to save the current screen contents
  //  static uint8_t displayBuffer[(SCREEN_WIDTH * SCREEN_HEIGHT + 7) / 8];
  //  // Copy over the contents of the current display buffer to the duplicate
  //  memcpy(displayBuffer, display.getBuffer(), sizeof(displayBuffer));

  // Note: the above doesn't work, memory challenge?

  switch (currentScreen) {
    case 0:
      // toggle hidden/next info screen
      display.clearDisplay();
      display.setCursor(0, 32);
      display.println(F("  Health is Wealth"));
      display.display();
      break;
    case 1:
      // MOVE TO PRESET 1
      respondPress();
      break;
    case 2:
      // MOVE TO PRESET 2
      respondPress();
      break;
    case 3:
      // MOVE TO PRESET 3
      respondPress();
      break;
    case 4:
      // MOVE TO PRESET 4
      respondPress();
      break;
    case 5:
      // WIFI SETTINGS
      respondPress();
      break;
    case 6:
      // TOGGLE PRESETS SETTINGS SCREEN or LAN Access URL
      respondPress();
      break;
    default:
      // unknown selection
      respondPress();
      Serial.println("Err: Unknown option selected.");
      break;
  }
  //  // Now that the button action is over,
  //  // Copy back from the duplicate buffer
  //  memcpy(display.getBuffer(), displayBuffer, sizeof(displayBuffer));
  //  // and display it to restore the previous screen.
  //  display.display();
}


//  Joystick Press Graphic & Screen Selection  ------------------


void respondPress() {
  //  for (int radius = 64; radius > 2; radius = radius - 5) {
  //    display.clearDisplay();
  //    display.fillCircle(64, 32, radius, WHITE);
  //    display.display();
  //    delay(2);
  //  }
  display.clearDisplay();
  for (int radius = 1; radius < 128; radius = radius + 15) {
    display.fillCircle(64, 32, radius, WHITE);
    display.display();
    delay(1);
  }
  showScreen();  // Show current screen
}

//  Text Display Functions  ------------------

void showtext(const char *preset) {
  const int text_size = 7;
  display.clearDisplay();
  display.setTextWrap(false);
  display.setTextSize(text_size);             // Draw 3X-scale text
  display.setTextColor(SSD1306_WHITE);
  //  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  //  display.println(preset);
  drawCentreString(preset, 0, 0);
  display.display();
  delay(100);
}


void drawCentreString(const char *buf, int x, int y)
{
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(buf, x, y, &x1, &y1, &w, &h); //calc width of new string
  Serial.print(F("Text: ")); Serial.println(buf);
  Serial.print(F("display.width(): ")); Serial.println(display.width());
  Serial.print(F("display.height(): ")); Serial.println(display.height());
  Serial.print(F("x1: ")); Serial.println(x1);
  Serial.print(F("y1: ")); Serial.println(y1);
  Serial.print(F("w: ")); Serial.println(w);
  Serial.print(F("h: ")); Serial.println(h);
  display.setCursor((display.width() - w) / 2, (display.height() - h) / 2);
  display.print(buf);
}


//  Images saved to Flash Memory  ------------------

// Generate these arrays here: http://javl.github.io/image2cpp/

// 'arrow_down', 32x32px
const unsigned char epd_bitmap_arrow_down [] PROGMEM = {
  0xc0, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f,
  0xfe, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x01, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xc0, 0x07, 0xfe,
  0x3f, 0xf0, 0x1f, 0xfc, 0x1f, 0xf8, 0x3f, 0xf0, 0x0f, 0xfc, 0x7f, 0xe0, 0x07, 0xff, 0xff, 0xc0,
  0x81, 0xff, 0xff, 0x83, 0xe0, 0xff, 0xfe, 0x07, 0xf0, 0x7f, 0xfc, 0x1f, 0xf8, 0x3f, 0xf8, 0x3f,
  0xfc, 0x0f, 0xf0, 0x7f, 0xff, 0x07, 0xc0, 0xff, 0xff, 0x83, 0x83, 0xff, 0xff, 0xc0, 0x07, 0xfe,
  0x7f, 0xe0, 0x0f, 0xfc, 0x3f, 0xf8, 0x1f, 0xf8, 0x0f, 0xfc, 0x7f, 0xf0, 0x07, 0xfe, 0xff, 0xc0,
  0x03, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xfc, 0x00, 0x00, 0x3f, 0xf8, 0x00,
  0x00, 0x1f, 0xf0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00
};
// 'arrow_up', 32x32px
const unsigned char epd_bitmap_arrow_up [] PROGMEM = {
  0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x0f, 0xf8, 0x00,
  0x00, 0x1f, 0xfc, 0x00, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0xc0,
  0x03, 0xff, 0x7f, 0xe0, 0x0f, 0xfe, 0x3f, 0xf0, 0x1f, 0xf8, 0x1f, 0xfc, 0x3f, 0xf0, 0x07, 0xfe,
  0x7f, 0xe0, 0x03, 0xff, 0xff, 0xc1, 0xc1, 0xff, 0xff, 0x03, 0xe0, 0xff, 0xfe, 0x0f, 0xf0, 0x3f,
  0xfc, 0x1f, 0xfc, 0x1f, 0xf8, 0x3f, 0xfe, 0x0f, 0xe0, 0x7f, 0xff, 0x07, 0xc1, 0xff, 0xff, 0x81,
  0x03, 0xff, 0xff, 0xe0, 0x07, 0xfe, 0x3f, 0xf0, 0x0f, 0xfc, 0x1f, 0xf8, 0x3f, 0xf8, 0x0f, 0xfc,
  0x7f, 0xe0, 0x03, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0x80, 0x00, 0xff, 0xfe, 0x00, 0x00, 0x7f,
  0xfc, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x03
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 288)
const int epd_bitmap_allArray_LEN = 2;
const unsigned char* epd_bitmap_allArray[2] = {
  epd_bitmap_arrow_down,
  epd_bitmap_arrow_up
};


#define ARROW_WIDTH 32
#define ARROW_HEIGHT 32
const int8_t step_height = 7;
const int8_t frame_count = 6;
int8_t bitmap_height;

void drawStaticArrow(int arrowDirection) {
  display.clearDisplay();
  switch (arrowDirection) {
    case DIRECTION_UP:
      display.drawBitmap((display.width()  - ARROW_WIDTH ) / 2, (display.height() - ARROW_HEIGHT) / 2, epd_bitmap_arrow_up, ARROW_WIDTH, ARROW_HEIGHT, 1);
      break;
    case DIRECTION_DOWN:
      display.drawBitmap((display.width()  - ARROW_WIDTH ) / 2, (display.height() - ARROW_HEIGHT) / 2, epd_bitmap_arrow_down, ARROW_WIDTH, ARROW_HEIGHT, 1);
      break;
    default:
      break;
  }
  display.display();
}

void drawMovingArrow(String direction) {
  display.clearDisplay();
  //Serial.println(direction);
  if (direction == "UP") {
    //Serial.println(F("ARROW UP"));
    for (int8_t frame = frame_count; frame > 0; frame--) {
      bitmap_height = display.height() - ARROW_HEIGHT + (frame * step_height);  // offset the position by (frame * step_height) which reduces in every iteration
      display.drawBitmap((display.width()  - ARROW_WIDTH ) / 2, bitmap_height / 2, epd_bitmap_arrow_up, ARROW_WIDTH, ARROW_HEIGHT, 1);
      display.display();  // Show the buffer
      delay(50);
      display.clearDisplay();
    }
    delay(100);
  } else if (direction == "DOWN") {
    //Serial.println(F("ARROW DOWN"));

    for (int8_t frame = frame_count; frame > 0; frame--) {
      bitmap_height = display.height() - ARROW_HEIGHT - (frame * step_height);
      display.drawBitmap((display.width()  - ARROW_WIDTH ) / 2, bitmap_height / 2, epd_bitmap_arrow_down, ARROW_WIDTH, ARROW_HEIGHT, 1);
      display.display();  // Show the buffer
      delay(50);
      display.clearDisplay();
    }
    delay(50);
  }
  display.clearDisplay();  // Clear the buffer
  display.display();  // Show the empty buffer (clear the screen)
}
