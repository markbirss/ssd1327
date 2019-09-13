#ifndef __SSD1327__
#define __SSD1327__
#define FONT_NORMAL 0
#define FONT_LARGE 1
#define FONT_SMALL 2

enum {
OLED_128x128 = 0, // SSD1327
OLED_256x64	  // SSD1322
};

#if defined(_LINUX_) && defined(__cplusplus)
extern "C" {
#endif
//
// Initializes the OLED controller into "page mode" on I2C
// If SDAPin and SCLPin are not -1, then bit bang I2C on those pins
// Otherwise use the Wire library
//
void ssd1327Init(int iType, int iAddr, int bFlip, int bInvert, int iSDAPin, int iSCLPin, int32_t iSpeed);
//
// Initialize an SPI version of the display
//
void ssd1327SPIInit(int iType, int iDC, int iCS, int iReset, int bFlip, int bInvert, int32_t iSpeed);
//
// Sets the brightness (0=off, 255=brightest)
//
void ssd1327SetContrast(unsigned char ucContrast);

//
// Sends a command to turn off the OLED display
//
void ssd1327Shutdown();
//
// Power up/down the display
// useful for low power situations
//
void ssd1327Power(unsigned char bOn);
//
// Draw a string of normal (8x8), small (6x8) or large (16x32) characters
// At the given col+row with the given foreground (MSN) and background (LSN) colors
//
void ssd1327WriteString(uint8_t x, uint8_t y, char *szMsg, uint8_t iSize, int ucFGColor, int ucBGColor);
//
// Fill the frame buffer with a color
// e.g. black (0x00) or white (0xf)
//
void ssd1327Fill(unsigned char ucColor);

// non-AVR MCUs have enough RAM to support a 8k back buffer
// and additional functions that require it
#ifndef __AVR__
//
// Set an individual pixel to a specific color
// The pixel is only set in the back buffer and some time
// later the display buffer will need to be dumped to the physical display
//
void ssd1327SetPixel(int x, int y, unsigned char ucColor);
//
// Copy part or whole of the backbuffer to the physical display
//
void ssd1327ShowBuffer(int x, int y, int w, int h);
//
// Return a pointer to the back buffer for direct manipulation
//
uint8_t * ssd1327GetBackbuffer(void);
//
// Draw a Bresenham line from point 1 to point 2
//
void ssd1327DrawLine(int x1, int y1, int x2, int y2, uint8_t ucColor);

#endif // __AVR__

#if defined(_LINUX_) && defined(__cplusplus)
}
#endif
#endif // __SSD1327__
