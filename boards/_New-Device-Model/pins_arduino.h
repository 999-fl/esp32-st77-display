#ifndef Pins_Arduino_h
#define Pins_Arduino_h

// This toolchain (toolchain-xtensa-esp-elf, GCC 14.2) force-includes the
// board's pins_arduino.h via a command-line -include as part of its normal
// variant-loading mechanism - this happens before its own internal stdint.h
// chain is fully set up. Pulling in <stdint.h> here (or using typed
// `static const uint8_t` declarations, which need it) breaks that chain
// (a gcc `-include` + `#include_next` interaction). Plain #define avoids
// the problem entirely since it needs no type/header at all.

#define USB_VID 0x303a
#define USB_PID 0x1001

#define TX 1
#define RX 3

#define SDA 21
#define SCL 22

// Required by the core SD/Wire/SPI libraries even though this board has no
// SD slot - they use these as default parameter values. -1 means "not used".
#define SS   -1
#define MOSI -1
#define MISO -1
#define SCK  -1

#define G0  0
#define G1  1
#define G2  2
#define G3  3
#define G4  4
#define G5  5
#define G12 12
#define G13 13
#define G14 14
#define G15 15
#define G16 16
#define G17 17
#define G18 18
#define G19 19
#define G21 21
#define G22 22
#define G23 23
#define G25 25
#define G26 26
#define G27 27
#define G32 32
#define G33 33
#define G34 34
#define G35 35

#define ADC1 34
#define ADC2 35

// --- Buttons: 3-button scheme, no physical buttons onboard - wire your own ---
// SEL = select/confirm, UP = previous (long-press = ESC), DW = next
#define HAS_BTN 1
#define SEL_BTN 26
#define UP_BTN  25
#define DW_BTN  27
#define BTN_ALIAS "\"Ok\""
#define BTN_ACT LOW

#define TXLED -1
#define LED_ON  HIGH
#define LED_OFF LOW

// No CC1101/NRF24 radio module wired to this board
#define CC1101_GDO0_PIN -1
#define CC1101_SS_PIN   -1
#define CC1101_MOSI_PIN SPI_MOSI_PIN
#define CC1101_SCK_PIN  SPI_SCK_PIN
#define CC1101_MISO_PIN SPI_MISO_PIN

#define NRF24_CE_PIN   -1
#define NRF24_SS_PIN   -1
#define NRF24_MOSI_PIN SPI_MOSI_PIN
#define NRF24_SCK_PIN  SPI_SCK_PIN
#define NRF24_MISO_PIN SPI_MISO_PIN

#define FP 1
#define FM 1
#define FG 2

#define HAS_SCREEN 1
#define ROTATION 1

// --- Battery voltage sense (2x 100k resistor divider -> GPIO34) ---
// GPIO34 is ADC1, input-only, free on this board - ideal for analog sensing
// (ADC2 pins can't be used reliably here since WiFi uses ADC2 internally).
#define ANALOG_BAT_PIN 34

// --- No SD card slot on this board - fully disabled ---
#define SDCARD_CS   -1
#define SDCARD_SCK  -1
#define SDCARD_MISO -1
#define SDCARD_MOSI -1

#define GROVE_SDA 21
#define GROVE_SCL 22

// Generic SPI bus reference - not physically used (TFT uses its own
// dedicated pins set via TFT_* build flags in ideaspark-esp32.ini)
#define SPI_SCK_PIN  -1
#define SPI_MISO_PIN -1
#define SPI_MOSI_PIN -1
#define SPI_SS_PIN   -1

#endif /* Pins_Arduino_h */
