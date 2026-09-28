# Building Page Turner

## Versions and source

- Arduino board package: Seeed nRF52 Boards **1.1.13**.
- Board/FQBN: **Seeed XIAO nRF52840 Plus** / `Seeeduino:nrf52:xiaonRF52840Plus`.
- Display/touch library: Seeed_GFX2 **1.0.0**.
- GNU Arm compiler: **9-2019q4**, supplied as a BSP tool dependency.
- CMSIS: **5.7.0**, supplied as a BSP tool dependency.
- Sketch: `firmware/page_turner/page_turner.ino`.

Install the board package using Seeed's Board Manager index, then the display library. Open the sketch, select the board and compile. Compilation produces a DFU `.zip` for this board. The bootloader and SoftDevice remain the versions provided by the board/BSP.

The exact dependency sources used for the packaged build are in `third_party/corresponding-source.zip`, with their original licenses. To use or modify those sources, extract the archive and follow its `README.md`: use the supplied core/board/library source with the installed matching BSP and tool dependencies, and use the supplied Seeed_GFX2 library. Arduino recompiles and relinks these sources with the application. No application object file is required because the complete application source is supplied under MIT.

## Arduino CLI example

Use a sketch path without spaces if the BSP's compiler recipe fails on a path containing spaces. Substitute your own library and build paths:

```text
arduino-cli compile --fqbn Seeeduino:nrf52:xiaonRF52840Plus --library /path/to/Seeed_GFX2 --build-path /path/to/build /path/to/page_turner
```

The source snapshot is limited to the actual application dependency trees, rather than every board, unrelated library, example asset or host-side tool from the BSP. Build tools are installed separately using the versions above. The source snapshot also contains package recipes and licenses for reference.

## Packaged build verification

The current build was compiled on 2026-09-28 after explicitly omitting the optional BLE Manufacturer Name characteristic. The paired device name and model remain `Page Turner`. This build has not been flashed or hardware-tested; README compatibility results describe prior hardware tests.

Source SHA-256: 50431205b4e34cad7a171b7dc29a40e995a6120fecf905c2faef3fb7dc3f8a96

Corresponding dependency source archive SHA-256: 39cc1d67b9a7cf6d2cc6217c9058d5f8290704f525a50f249d1ed94bba54e41f

The DFU ZIP includes `manifest.json`, `page_turner.ino.bin`, `page_turner.ino.dat`, the application source, `THIRD_PARTY_NOTICES.md`, `BUILDING.md`, the root `LICENSE`, the complete dependency source ZIP and `third_party/licenses/`. License/source additions leave the DFU manifest's application entries unchanged.

For redistribution, retain the source, notices and licenses alongside the DFU payload. Rebuild and retest after changing libraries or firmware behavior.