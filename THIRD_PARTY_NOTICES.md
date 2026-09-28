# Third-party attribution and license scope

Page Turner is maintained by **FaiyuetCik**. Its target board and display hardware are made by **Seeed Studio**. This is an independent application project, not an official Seeed Studio or Adafruit product.

The root [LICENSE](LICENSE) applies to the original Page Turner application additions and documentation. It does not transfer ownership of the hardware, libraries, fonts, SDK, runtime or upstream examples to the project maintainer. Third-party portions retain their original copyrights and licenses.

## Application example attribution

The BLE advertising setup follows the Adafruit Bluefruit HID keyboard example. The original example, including its required introductory notice and printed text, is preserved in [third_party/reference/adafruit_blehid_keyboard.ino](third_party/reference/adafruit_blehid_keyboard.ino). It is not an additional sketch to upload. Its MIT notice is retained in [Bluefruit-MIT.txt](third_party/licenses/Bluefruit-MIT.txt).

## Build dependencies

This inventory was checked against the local Seeed nRF52 Boards 1.1.13 build and Seeed_GFX2 1.0.0 sources on 2026-09-28. A package-level license does not override a more specific source-file notice.

| Component | Original authors / copyright holders | License and retained notices |
| --- | --- | --- |
| Seeed_GFX2 1.0.0 | Seeed Studio; bundled fonts retain their original authors | [Original license including bundled-component notices](third_party/licenses/Seeed-GFX2.txt) |
| Arduino nRF5 core, SPI and Wire in Seeed's BSP | Arduino LLC, Sandeep Mistry, Adafruit Industries and file-specific contributors; Seeed Studio supplies the board package | LGPL-2.1-or-later for these Arduino portions: [BSP notice](third_party/licenses/Arduino-core-notice.txt), [LGPL-2.1 text](third_party/licenses/LGPL-2.1.txt) |
| Bluefruit52Lib and HID example | Adafruit Industries / Ha Thach and contributors | [Package MIT](third_party/licenses/Bluefruit-MIT.txt); individual service files also carry BSD notices |
| Adafruit TinyUSB wrapper and TinyUSB stack | Ha Thach / Adafruit Industries and file-specific contributors | [MIT wrapper notice](third_party/licenses/Adafruit-TinyUSB.txt); stack notices retained in the source snapshot and source-file notices |
| Adafruit LittleFS and InternalFileSystem | Ha Thach / Adafruit Industries | MIT notices retained in the source-file notices |
| littlefs | Arm Limited and contributors | [BSD notice](third_party/licenses/littlefs.txt) |
| FreeRTOS | Amazon.com, Inc. or affiliates and contributors | [MIT notice](third_party/licenses/FreeRTOS.txt) |
| Nordic nrfx, SDK and SoftDevice interfaces | Nordic Semiconductor ASA | [nrfx notice](third_party/licenses/Nordic-nrfx.txt); SDK/header-specific terms retained in the source snapshot |
| Adafruit nRFCrypto and bundled Arm/Nordic crypto support | Adafruit Industries, Arm and Nordic Semiconductor | [Wrapper MIT](third_party/licenses/Adafruit-nRFCrypto.txt), [Arm object/header terms](third_party/licenses/Arm-nRFCrypto-binary.txt), [Nordic crypto terms](third_party/licenses/Nordic-CryptoCell.txt) |
| CMSIS | Arm and contributors | [Original license](third_party/licenses/CMSIS.txt) |
| GNU Arm toolchain and linked runtime | GNU/toolchain and newlib copyright holders as stated in the supplied notice | [Original distribution licenses, including runtime exception and newlib notices](third_party/licenses/GNU-Arm-toolchain.txt) |
| SEGGER RTT/SystemView files supplied with BSP | SEGGER Microcontroller GmbH | Source-file notices retained; no claim of ownership or endorsement by Page Turner |

The [source-file notices](third_party/licenses/Source-file-notices.txt) preserve additional original copyright and license headers. The [corresponding source archive](third_party/corresponding-source.zip) preserves unmodified source and in-file notices from the installed application dependencies. Its SHA-256 is recorded in [BUILDING.md](BUILDING.md).

## Firmware redistribution and rebuilding

The downloadable `page_turner.ino.zip` contains the DFU files plus the application source, corresponding dependency source, licenses, this attribution file and rebuild instructions. Keep these materials with redistributed firmware. The firmware as a whole is not described as MIT-only; each third-party component retains its own terms. The package is intended for the Nordic nRF52840-based target board.

See [BUILDING.md](BUILDING.md) to rebuild, including with modified LGPL libraries. No additional restriction is imposed by this project on reverse engineering for debugging modifications to LGPL components; separately supplied Nordic/Arm components retain their own terms. The application ZIP does not supply a replacement bootloader or SoftDevice.

## Upstream references

- [Seeed nRF52 Boards 1.1.13 package](https://files.seeedstudio.com/arduino/core/nRF52/Seeed_nRF52_Boards-1.1.13.tar.bz2)
- [Seeed_GFX2](https://github.com/Seeed-Studio/Seeed_GFX2)
- [Adafruit nRF52 Arduino / Bluefruit](https://github.com/adafruit/Adafruit_nRF52_Arduino)
- [Adafruit TinyUSB Arduino](https://github.com/adafruit/Adafruit_TinyUSB_Arduino)
- [LGPL-2.1](https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html)