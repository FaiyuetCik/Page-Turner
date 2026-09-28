/* Page Turner - BLE HID slide remote for XIAO nRF52840 Plus 1.47" display.
 * USR1: previous page (Left Arrow). USR2: next page (Right Arrow).
 * Swipe up/down on the touch screen to send Up/Down Arrow.
 */
#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <bluefruit.h>
#include <Seeed_GFX.h>
#include "board/boards/XIAO_LCD_Board.h"
#include "driver/tft/Driver_JD9853A.h"
#include "panel/Panel_TFT.h"
#include <Wire.h>
#include "touch/Touch_AXS5106L.h"

static constexpr uint8_t BUTTON_PREV = D19;
static constexpr uint8_t BUTTON_NEXT = D15;
static constexpr uint16_t BLACK = 0x0000;
static constexpr uint16_t WHITE = 0xFFFF;
static constexpr uint16_t CYAN = 0x07FF;
static constexpr uint16_t AMBER = 0xFD20;
static constexpr uint16_t DIM = 0x8410;
static constexpr uint32_t DEBOUNCE_MS = 25;

Seeed_GFX display;
Touch_AXS5106L touch(-1, D7, Wire, 172, 320);
BLEDis deviceInfo;
BLEHidAdafruit hid;

struct Button {
  uint8_t pin;
  uint8_t key;
  bool raw;
  bool stable;
  uint32_t changedAt;
};

Button prevButton = {BUTTON_PREV, HID_KEY_ARROW_LEFT, false, false, 0};
Button nextButton = {BUTTON_NEXT, HID_KEY_ARROW_RIGHT, false, false, 0};
volatile bool bleConnected = false;
volatile bool dirty = true;
bool touchReady = false;
bool touchTracking = false;
int32_t touchStartX = 0;
int32_t touchStartY = 0;
int32_t touchLastX = 0;
int32_t touchLastY = 0;
uint32_t lastGestureMs = 0;

static void onConnect(uint16_t) {
  bleConnected = true;
  dirty = true;
}

static void onDisconnect(uint16_t, uint8_t) {
  bleConnected = false;
  dirty = true;
}

static void startAdvertising() {
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(hid);
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
}

static void drawCentered(const char* value, int y, int font, uint16_t color) {
  display.setTextDatum(TL_DATUM);
  display.setTextColor(color);
  int x = (172 - display.textWidth(value, font)) / 2;
  display.drawString(value, x < 0 ? 0 : x, y, font);
}

static void drawScreen() {
  display.fillScreen(BLACK);
  drawCentered("PAGE TURNER", 16, 2, WHITE);
  drawCentered("BLE REMOTE", 42, 2, CYAN);
  display.drawFastHLine(12, 72, 148, DIM);
  drawCentered(bleConnected ? "CONNECTED" : "PAIR VIA BLUETOOTH", 91, 2,
               bleConnected ? CYAN : AMBER);
  drawCentered("USR1  LEFT   RIGHT  USR2", 125, 1, WHITE);
  display.drawRect(10, 145, 152, 58, DIM);
  display.drawRect(10, 211, 152, 58, DIM);
  drawCentered("SWIPE UP  ^", 162, 2, CYAN);
  drawCentered("SWIPE DOWN v", 228, 2, CYAN);
  drawCentered("LEFT / RIGHT: BUTTONS", 290, 1, DIM);
}
static void sendTap(uint8_t key) {
  if (!bleConnected || !Bluefruit.connected()) return;
  uint8_t keys[6] = {key, 0, 0, 0, 0, 0};
  if (!hid.keyboardReport(0, keys)) return;
  delay(35);
  hid.keyRelease();

  dirty = true;
}

static void pollTouch() {
  int32_t x = 0, y = 0;
  const bool down = display.getTouch(&x, &y);
  if (down && !touchTracking) {
    touchTracking = true;
    touchStartX = x;
    touchStartY = y;
    touchLastX = x;
    touchLastY = y;
  } else if (down && touchTracking) {
    touchLastX = x;
    touchLastY = y;
  } else if (!down && touchTracking) {
    touchTracking = false;
    if (millis() - lastGestureMs < 250) return;
    const int32_t dx = touchLastX - touchStartX;
    const int32_t dy = touchLastY - touchStartY;
    if (abs(dy) < 35 || abs(dy) < abs(dx)) return;
    lastGestureMs = millis();
    sendTap(dy < 0 ? HID_KEY_ARROW_UP : HID_KEY_ARROW_DOWN);
  }
}
static void pollButton(Button& button) {
  const bool pressed = digitalRead(button.pin) == LOW;
  if (pressed != button.raw) {
    button.raw = pressed;
    button.changedAt = millis();
  }
  if (pressed != button.stable && millis() - button.changedAt >= DEBOUNCE_MS) {
    button.stable = pressed;
    if (pressed) sendTap(button.key);
  }
}

void setup() {
  pinMode(BUTTON_PREV, INPUT_PULLUP);
  pinMode(BUTTON_NEXT, INPUT_PULLUP);
  Serial.begin(115200);
  delay(200);

  if (!display.begin<Board_XIAO_1inch47_Touch_Display<38, 37>,
                     Config_Seeed_1inch47_Touch_JD9853A>()) {
    Serial.println("Display init failed");
  } else {
    display.panel().setBacklight(160);
    touchReady = display.attachTouch(touch, display.panel().driver().bus());
    drawScreen();
  }

  Bluefruit.begin();
  Bluefruit.setName("Page Turner");
  Bluefruit.setTxPower(4);
  Bluefruit.Periph.setConnectCallback(onConnect);
  Bluefruit.Periph.setDisconnectCallback(onDisconnect);
  deviceInfo.setManufacturer("Desk Pixel contributors");
  deviceInfo.setModel("Page Turner");
  deviceInfo.begin();
  hid.begin();
  startAdvertising();
  Serial.println("Page Turner ready: USR1/USR2=left/right, swipe=up/down");
}

void loop() {
  pollButton(prevButton);
  pollButton(nextButton);
  if (touchReady) pollTouch();
  if (dirty) {
    dirty = false;

    drawScreen();
  }

  delay(5);
}





