#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST);  // Fast I2C / TWI

const int buttonUpPin = 11;
const int buttonDownPin = 10;
const int buttonSelectPin = 9;
const int buttonBackPin = 8;

// Define your menu items
const char* menuItems[] = {"LFR", "MAZE"};

int currentMenuItem = 0;  // Current menu item index

void setup() {
  // Initialize OLED 
  u8g.begin();

  // Setup buttons as inputs
  pinMode(buttonUpPin, INPUT_PULLUP);
  pinMode(buttonDownPin, INPUT_PULLUP);
  pinMode(buttonSelectPin, INPUT_PULLUP);
  pinMode(buttonBackPin, INPUT_PULLUP);
}

void loop() {
  // Check button presses and navigate the menu
  if (digitalRead(buttonUpPin) == LOW) {
    delay(400);   // Adjust the delay as needed
    currentMenuItem = (currentMenuItem - 1 + sizeof(menuItems) / sizeof(menuItems[0])) % (sizeof(menuItems) / sizeof(menuItems[0]));
  }
  if (digitalRead(buttonDownPin) == LOW) {
    delay(400);   // Adjust the delay as needed
    currentMenuItem = (currentMenuItem + 1) % (sizeof(menuItems) / sizeof(menuItems[0]));
  }

  // Clear the display
  u8g.firstPage();
  do {
    // Center the text horizontally and vertically
    int textWidth = u8g.getStrWidth(menuItems[currentMenuItem]);
    int centerX = (u8g.getWidth() - textWidth) / 2;
    int textHeight = u8g.getFontAscent() - u8g.getFontDescent();
    int centerY = (u8g.getHeight() + textHeight) / 2;

    u8g.setFont(u8g_font_osb21r);  // primary font
    //u8g.setFont(u8g_font_10x20);  // secondary font

    u8g.drawStr(centerX, centerY, menuItems[currentMenuItem]);
  } while (u8g.nextPage());
}
