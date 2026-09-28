# Page Turner

A Bluetooth presentation clicker for the Seeed XIAO nRF52840 Plus 1.47-inch display. This is a separate successor to the Desk Pixel weather-clock prototype; the original is retained for rollback.

## Controls

| Board control | HID key | Use |
| --- | --- | --- |
| USR1 (D19) | Left Arrow | Previous slide/page |
| USR2 (D15) | Right Arrow | Next slide/page |
| Swipe up on the touchscreen | Up Arrow | Action depends on the focused app |
| Swipe down on the touchscreen | Down Arrow | Action depends on the focused app |

Each physical button sends one key tap per press; holding a button does not repeat. Touch gestures are evaluated when you lift your finger. Swipes can start anywhere on the touchscreen: the two outlined areas are visual hints, not separate active zones. A swipe must travel at least 35 pixels vertically, with vertical movement at least as large as horizontal movement. Gestures recognized within 250 ms of the previous accepted gesture are ignored.

The screen shows the project name, Bluetooth connection state (`CONNECTED` or `PAIR VIA BLUETOOTH`), button labels, and swipe hints. The current firmware has no timer, click counter, slide number, or battery indicator. Key reports are sent only while Bluetooth is connected.

## Compatibility

Page Turner acts as a Bluetooth Low Energy (BLE) HID keyboard. The current firmware sends only Left, Right, Up, and Down Arrow keys, using the fixed controls listed above. No companion app is required.

### Tested device and app combinations

Hardware tests reported by the project owner on 2026-09-28:

| Device | App | Confirmed operation | Result |
| --- | --- | --- | --- |
| iPad Air 11-inch (M3) | Apple Books | Left / Right page turning | Passed |
| iPhone 13 | Apple Books | Left / Right page turning | Passed |
| Lenovo ThinkBook 16 G7+ IAH (21TL), Windows 11 Home China 25H2 | Microsoft PowerPoint | Left / Right / Up / Down control | Passed |

The computer model and OS were read from the tested machine: Lenovo ThinkBook 16 G7+ IAH (21TL), Windows 11 Home China 25H2, build 26200.9457. PowerPoint, iOS, iPadOS, and Apple Books versions were not recorded. Up / Down operation in Apple Books was not reported as tested. These results confirm the listed combinations and operations, rather than every app on those devices.

### Requirements and limits

For another device or app to work:

- The device and operating system must support pairing with a BLE HID keyboard (HID over GATT). Bluetooth availability or a Bluetooth version number alone does not guarantee compatibility.
- The target app must accept the arrow keys sent by this firmware for the desired action. It must have focus and be in the appropriate reading or presentation mode.
- Apps or readers that require Page Up / Page Down, touch gestures, or a different remote protocol are outside the current input support unless they also accept arrow keys. The firmware has no selectable key mappings.

Other device/app combinations, including Android, macOS, other reading or presentation apps, and dedicated e-readers, have not been verified for this project. Their compatibility should be tested individually.

## Connection

1. Power the board through USB-C. For cordless use, connect a compatible 3.7 V LiPo cell to the board's JST 2.0 battery connector, following Seeed's polarity guidance.
2. In the target device's Bluetooth settings, pair **Page Turner** as a keyboard. See the compatibility section above for tested device/app combinations. If this board was previously paired as **Desk Pixel**, remove that older pairing first, since the BLE address is unchanged but the service has changed.
3. Focus a presentation or PDF and enter its presentation mode. USR1 sends Left Arrow; USR2 sends Right Arrow; swipe up or down on the touchscreen to send Up or Down Arrow. The effect of each arrow key depends on the focused app. There is no companion app or weather service.

The board does not include a laser emitter or a 2.4 GHz USB receiver. The USB-C cable currently supplies power and serial only; slide control is via Bluetooth.

## Build

Install Seeed nRF52 Boards 1.1.13 and Seeed_GFX2 1.0.0. Open `firmware/page_turner/page_turner.ino` in Arduino IDE, select **Seeed XIAO nRF52840 Plus**, and upload. Bluefruit and TinyUSB come with the board package.

## Verification status

Previously recorded verification: the four-direction HID firmware was compiled and flashed, and the board was discovered over BLE as `Page Turner` on Windows. The current source tracks the last touch coordinates before finger release for swipe-direction detection.

Reconnection behavior and battery runtime still need testing. The current firmware has no idle backlight dimming or application-level sleep logic.

The `page_turner.ino.zip` file contains a firmware binary, a `.dat` file, and a manifest; it is not an archive of the Arduino source. Its correspondence to the current source has not been verified. Use `firmware/page_turner/page_turner.ino` for source-based builds.

## Why Bluetooth HID?

Commercial presenters commonly use a USB 2.4 GHz receiver, Bluetooth, or both. Standard HID arrow keys let this board control presentations, PDFs, browsers, and e-reader apps without a custom computer program. Arrow-key support depends on the target app or reader; some readers require Page Up/Page Down or a model-specific remote protocol. This board already has BLE and two physical keys, but has no matching 2.4 GHz receiver.

Product references: [Logitech R500s](https://www.logitech.com/pt-br/shop/p/r500s-laser-presentation-remote), [Logitech Spotlight](https://www.logitech.com/en-gb/shop/p/spotlight-presentation-remote.910-004861), [Seeed button and hardware guide](https://wiki.seeedstudio.com/getting_started_1.47_inch_touch_display_nrf52840/), [Seeed BLE HID guide](https://wiki.seeedstudio.com/XIAO-BLE-Sense-Bluetooth_Usage/).

## License

MIT; see [LICENSE](LICENSE). Copyright 2026 FaiyuetCik.
