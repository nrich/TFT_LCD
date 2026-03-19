// Copyright 2026 Neil Richardson (nrich@neiltopia.com). All rights reserved.
//
// Licensed under the MIT License.
// See LICENSE for details.

#ifndef ILI9225_H_
#define ILI9225_H_

#include <SPI.h>

#include <cstdint>
#include <array>
#include <vector>
#include <exception>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <utility>

#define ILI9225_LCD_WIDTH   176
#define ILI9225_LCD_HEIGHT  220

#define R2L_BottomUp    0
#define BottomUp_R2L    1
#define L2R_BottomUp    2
#define BottomUp_L2R    3
#define R2L_TopDown     4
#define TopDown_R2L     5
#define L2R_TopDown     6
#define TopDown_L2R     7

std::array<std::array<int, 8>, 4> modeTab ={{
    {R2L_BottomUp, BottomUp_R2L, L2R_BottomUp, BottomUp_L2R, R2L_TopDown, TopDown_R2L, L2R_TopDown, TopDown_L2R},
    {BottomUp_L2R, L2R_BottomUp, TopDown_L2R, L2R_TopDown, BottomUp_R2L, R2L_BottomUp, TopDown_R2L, R2L_TopDown},
    {L2R_TopDown, TopDown_L2R, R2L_TopDown, TopDown_R2L, L2R_BottomUp, BottomUp_L2R, R2L_BottomUp, BottomUp_R2L},
    {TopDown_R2L, R2L_TopDown, BottomUp_R2L, R2L_BottomUp, TopDown_L2R, L2R_TopDown, BottomUp_L2R, L2R_BottomUp},
}};

#define ILI9225_DRIVER_OUTPUT_CTRL      0x01  // Driver Output Control
#define ILI9225_LCD_AC_DRIVING_CTRL     0x02  // LCD AC Driving Control
#define ILI9225_ENTRY_MODE              0x03  // Entry Mode
#define ILI9225_DISP_CTRL1              0x07  // Display Control 1
#define ILI9225_BLANK_PERIOD_CTRL1      0x08  // Blank Period Control
#define ILI9225_FRAME_CYCLE_CTRL        0x0B  // Frame Cycle Control
#define ILI9225_INTERFACE_CTRL          0x0C  // Interface Control
#define ILI9225_OSC_CTRL                0x0F  // Osc Control
#define ILI9225_POWER_CTRL1             0x10  // Power Control 1
#define ILI9225_POWER_CTRL2             0x11  // Power Control 2
#define ILI9225_POWER_CTRL3             0x12  // Power Control 3
#define ILI9225_POWER_CTRL4             0x13  // Power Control 4
#define ILI9225_POWER_CTRL5             0x14  // Power Control 5
#define ILI9225_VCI_RECYCLING           0x15  // VCI Recycling
#define ILI9225_RAM_ADDR_SET1           0x20  // Horizontal GRAM Address Set
#define ILI9225_RAM_ADDR_SET2           0x21  // Vertical GRAM Address Set
#define ILI9225_GRAM_DATA_REG           0x22  // GRAM Data Register
#define ILI9225_GATE_SCAN_CTRL          0x30  // Gate Scan Control Register
#define ILI9225_VERTICAL_SCROLL_CTRL1   0x31  // Vertical Scroll Control 1 Register
#define ILI9225_VERTICAL_SCROLL_CTRL2   0x32  // Vertical Scroll Control 2 Register
#define ILI9225_VERTICAL_SCROLL_CTRL3   0x33  // Vertical Scroll Control 3 Register
#define ILI9225_PARTIAL_DRIVING_POS1    0x34  // Partial Driving Position 1 Register
#define ILI9225_PARTIAL_DRIVING_POS2    0x35  // Partial Driving Position 2 Register
#define ILI9225_HORIZONTAL_WINDOW_ADDR1 0x36  // Horizontal Address Start Position
#define ILI9225_HORIZONTAL_WINDOW_ADDR2 0x37  // Horizontal Address End Position
#define ILI9225_VERTICAL_WINDOW_ADDR1   0x38  // Vertical Address Start Position
#define ILI9225_VERTICAL_WINDOW_ADDR2   0x39  // Vertical Address End Position
#define ILI9225_GAMMA_CTRL1             0x50  // Gamma Control 1
#define ILI9225_GAMMA_CTRL2             0x51  // Gamma Control 2
#define ILI9225_GAMMA_CTRL3             0x52  // Gamma Control 3
#define ILI9225_GAMMA_CTRL4             0x53  // Gamma Control 4
#define ILI9225_GAMMA_CTRL5             0x54  // Gamma Control 5
#define ILI9225_GAMMA_CTRL6             0x55  // Gamma Control 6
#define ILI9225_GAMMA_CTRL7             0x56  // Gamma Control 7
#define ILI9225_GAMMA_CTRL8             0x57  // Gamma Control 8
#define ILI9225_GAMMA_CTRL9             0x58  // Gamma Control 9
#define ILI9225_GAMMA_CTRL10            0x59  // Gamma Control 10

#define ILI9225C_INVOFF                 0x20
#define ILI9225C_INVON                  0x21

#define ILI9225_START_BYTE              0x005C

#define COLOUR_BLACK                     0x0000      //   0,   0,   0
#define COLOUR_WHITE                     0xFFFF      // 255, 255, 255
#define COLOUR_BLUE                      0x001F      //   0,   0, 255
#define COLOUR_GREEN                     0x07E0      //   0, 255,   0
#define COLOUR_RED                       0xF800      // 255,   0,   0
#define COLOUR_NAVY                      0x000F      //   0,   0, 128
#define COLOUR_DARKBLUE                  0x0011      //   0,   0, 139
#define COLOUR_DARKGREEN                 0x03E0      //   0, 128,   0
#define COLOUR_DARKCYAN                  0x03EF      //   0, 128, 128
#define COLOUR_CYAN                      0x07FF      //   0, 255, 255
#define COLOUR_TURQUOISE                 0x471A      //  64, 224, 208
#define COLOUR_INDIGO                    0x4810      //  75,   0, 130
#define COLOUR_DARKRED                   0x8000      // 128,   0,   0
#define COLOUR_OLIVE                     0x7BE0      // 128, 128,   0
#define COLOUR_GRAY                      0x8410      // 128, 128, 128
#define COLOUR_GREY                      0x8410      // 128, 128, 128
#define COLOUR_SKYBLUE                   0x867D      // 135, 206, 235
#define COLOUR_BLUEVIOLET                0x895C      // 138,  43, 226
#define COLOUR_LIGHTGREEN                0x9772      // 144, 238, 144
#define COLOUR_DARKVIOLET                0x901A      // 148,   0, 211
#define COLOUR_YELLOWGREEN               0x9E66      // 154, 205,  50
#define COLOUR_BROWN                     0xA145      // 165,  42,  42
#define COLOUR_DARKGRAY                  0x7BEF      // 128, 128, 128
#define COLOUR_DARKGREY                  0x7BEF      // 128, 128, 128
#define COLOUR_SIENNA                    0xA285      // 160,  82,  45
#define COLOUR_LIGHTBLUE                 0xAEDC      // 172, 216, 230
#define COLOUR_GREENYELLOW               0xAFE5      // 173, 255,  47
#define COLOUR_SILVER                    0xC618      // 192, 192, 192
#define COLOUR_LIGHTGRAY                 0xC618      // 192, 192, 192
#define COLOUR_LIGHTCYAN                 0xE7FF      // 224, 255, 255
#define COLOUR_VIOLET                    0xEC1D      // 238, 130, 238
#define COLOUR_AZUR                      0xF7FF      // 240, 255, 255
#define COLOUR_BEIGE                     0xF7BB      // 245, 245, 220
#define COLOUR_MAGENTA                   0xF81F      // 255,   0, 255
#define COLOUR_TOMATO                    0xFB08      // 255,  99,  71
#define COLOUR_GOLD                      0xFEA0      // 255, 215,   0
#define COLOUR_ORANGE                    0xFD20      // 255, 165,   0
#define COLOUR_SNOW                      0xFFDF      // 255, 250, 250
#define COLOUR_YELLOW                    0xFFE0      // 255, 255,   0

template <typename T>
T clamp(T v, T min_v, T max_v) {
    /// Clamp value to boundaries.
    return std::min(std::max(v, min_v), max_v);
}

class ILI9225 {
    SPIClass *spi;

    int cs;
    int dc;
    int rst;

    int width;
    int maxX;
    int height;
    int maxY;
    int blitBufferSize;

    int orientation = 0;
    uint16_t bgColour = COLOUR_BLACK;

    void writeShort(uint16_t data) {
        spi->transfer16(data);
    }

    void writeBuffer(uint8_t *buffer, size_t len) {
        spi->transfer(buffer, len);
    }

public:
    ILI9225(SPIClass *spi, int cs, int dc, int rst, int sdi, int clk, int width=ILI9225_LCD_WIDTH, int height=ILI9225_LCD_HEIGHT, int blit_buffer_size=10240) : spi(spi), cs(cs), dc(dc), rst(rst), width(width), maxX(width), height(height), maxY(height), blitBufferSize(blit_buffer_size) {
        pinMode(rst, OUTPUT);
        digitalWrite(rst, LOW);

        pinMode(dc, OUTPUT);
        digitalWrite(dc, LOW);

        pinMode(cs, OUTPUT);
        digitalWrite(cs, HIGH);

        pinMode(sdi, OUTPUT);
        digitalWrite(sdi, LOW);
        pinMode(clk, OUTPUT);
        digitalWrite(clk, HIGH);

        digitalWrite(clk, LOW);
        digitalWrite(sdi, LOW);

        spi->begin();

        setOrientation(0);

        resetDevice();
        setupDevice();
        clearScreen();
    }

    void resetDevice() {
        /// Reset device.

        // Pull the reset pin high to release the ILI9225C from the reset status
        digitalWrite(rst, HIGH);
        delay(10);
        // Pull the reset pin low to reset ILI9225
        digitalWrite(rst, LOW);
        delay(10);
        // Pull the reset pin high to release the ILI9225C from the reset status
        digitalWrite(rst, HIGH);
        delay(50);
    }

    void setupDevice() {
        writeRegister(ILI9225_DRIVER_OUTPUT_CTRL, 0x031C);   // set the display line number and display direction
        writeRegister(ILI9225_LCD_AC_DRIVING_CTRL, 0x0100);  // set 1 line inversion
        writeRegister(ILI9225_ENTRY_MODE, 0x1030);           // set GRAM write direction and BGR=1.
        writeRegister(ILI9225_BLANK_PERIOD_CTRL1, 0x0808);   // set the back porch and front porch
        writeRegister(ILI9225_INTERFACE_CTRL, 0x0000);       // CPU interface
        writeRegister(ILI9225_OSC_CTRL, 0x0801);             // set Osc  /*0e01*/
        writeRegister(ILI9225_RAM_ADDR_SET1, 0x0000);        // RAM Address
        writeRegister(ILI9225_RAM_ADDR_SET2, 0x0000);        // RAM Address

        // Power On sequence
        delay(50);
        writeRegister(ILI9225_POWER_CTRL1, 0x0A00);  // set SAP,DSTB,STB
        writeRegister(ILI9225_POWER_CTRL2, 0x1038);  // set APON,PON,AON,VCI1EN,VC
        delay(50);
        writeRegister(ILI9225_POWER_CTRL3, 0x1121);  // set BT,DC1,DC2,DC3
        writeRegister(ILI9225_POWER_CTRL4, 0x0066);  // set GVDD
        writeRegister(ILI9225_POWER_CTRL5, 0x5F60);  // set VCOMH/VCOML voltage

        // Set GRAM area
        writeRegister(ILI9225_GATE_SCAN_CTRL, 0x0000);
        writeRegister(ILI9225_VERTICAL_SCROLL_CTRL1, 0x00DB);
        writeRegister(ILI9225_VERTICAL_SCROLL_CTRL2, 0x0000);
        writeRegister(ILI9225_VERTICAL_SCROLL_CTRL3, 0x0000);
        writeRegister(ILI9225_PARTIAL_DRIVING_POS1, 0x00DB);
        writeRegister(ILI9225_PARTIAL_DRIVING_POS2, 0x0000);
        writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR1, 0x00AF);
        writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR2, 0x0000);
        writeRegister(ILI9225_VERTICAL_WINDOW_ADDR1, 0x00DB);
        writeRegister(ILI9225_VERTICAL_WINDOW_ADDR2, 0x0000);

        // Adjust GAMMA curve
        writeRegister(ILI9225_GAMMA_CTRL1, 0x4000);
        writeRegister(ILI9225_GAMMA_CTRL2, 0x060B);
        writeRegister(ILI9225_GAMMA_CTRL3, 0x0C0A);
        writeRegister(ILI9225_GAMMA_CTRL4, 0x0105);
        writeRegister(ILI9225_GAMMA_CTRL5, 0x0A0C);
        writeRegister(ILI9225_GAMMA_CTRL6, 0x0B06);
        writeRegister(ILI9225_GAMMA_CTRL7, 0x0004);
        writeRegister(ILI9225_GAMMA_CTRL8, 0x0501);
        writeRegister(ILI9225_GAMMA_CTRL9, 0x0E00);
        writeRegister(ILI9225_GAMMA_CTRL10, 0x000E);

        delay(50);

        writeRegister(ILI9225_DISP_CTRL1, 0x1017);
    }

    void clearScreen(uint16_t colour) {
        /// Clear screen.

        auto old_orientation = orientation;
        orientation = 0;
        fillRectangle(0, 0, maxX, maxY, colour);
        orientation = old_orientation;
        delay(10);
    }


    void clearScreen() {
        /// Clear screen.

        clearScreen(bgColour);
    }

    void writeRegister(uint16_t reg, uint16_t data) {
        static const SPISettings settings(30000000L, MSBFIRST, SPI_MODE0);
        spi->beginTransaction(settings);

        digitalWrite(cs, LOW);
        digitalWrite(dc, LOW);

        writeShort(reg);
        digitalWrite(dc, HIGH);

        writeShort(data);
        digitalWrite(cs, HIGH);

        SPI.endTransaction();
    }

    void writeData(uint16_t data) {
        static const SPISettings settings(30000000L, MSBFIRST, SPI_MODE0);

        spi->beginTransaction(settings);

        digitalWrite(cs, LOW);
        digitalWrite(dc, HIGH);

        writeShort(data);
        digitalWrite(cs, HIGH);

        spi->endTransaction();
    }

    void writeCommand(uint16_t reg) {
        static const SPISettings settings(30000000L, MSBFIRST, SPI_MODE0);

        spi->beginTransaction(settings);

        digitalWrite(cs, LOW);
        digitalWrite(dc, LOW);

        writeShort(reg);
        digitalWrite(cs, HIGH);

        spi->endTransaction();
    }

    void fillRectangle(int x1, int y1, int width, int height, uint16_t colour) {
        /// Draw a filled rectangle.

        int x2 = x1 + width - 1;
        int y2 = y1 + height - 1;

        setWindow(x1, y1, x2, y2);

        int t = (y2 - y1 + 1) * (x2 - x1 + 1);

        digitalWrite(cs, LOW);
        digitalWrite(dc, HIGH);

        if (t > 0) {
            while (t > 0) {
                writeShort(colour);
                t -= 1;
            }

            digitalWrite(cs, HIGH);
        }

        resetWindow();
    }

    void blit(int x1, int y1, int width, int height, std::vector<uint16_t> bitmap) {
        /// Blit a bitmap to screen

        int x2 = x1 + width - 1;
        int y2 = y1 + height - 1;

        setWindow(x1, y1, x2, y2);

        digitalWrite(cs, LOW);
        digitalWrite(dc, HIGH);

        for (const auto colour : bitmap) {
            writeShort(colour);
        }

        digitalWrite(cs, HIGH);

        resetWindow();
    }


    std::pair<int, int> orientationCoordinates(int x1, int y1) {
        if (orientation == 0)
            return std::make_pair(x1, y1);

        if (orientation == 1) {
            y1 = maxY - y1 - 1;
            std::swap(x1, y1);
            return std::make_pair(x1, y1);
        }

        if (orientation == 2) {
            x1 = maxX - x1 - 1;
            y1 = maxY - y1 - 1;
            return std::make_pair(x1, y1);
        }

        if (orientation == 3) {
            x1 = maxX - x1 - 1;
            std::swap(x1, y1);
            return std::make_pair(x1, y1);
        }

        throw std::runtime_error("Unknown coordinate " + std::to_string(orientation));
    }

    void setWindow(int x0, int y0, int x1, int y1) {
        setWindowMode(x0, y0, x1, y1, BottomUp_L2R);
    }

    void setWindowMode(int x0, int y0, int x1, int y1, int mode) {
        // clip to TFT-Dimensions
        x0 = clamp(x0, 0, maxX-1);
        x1 = clamp(x1, 0, maxX-1);
        y0 = clamp(y0, 0, maxY-1);
        y1 = clamp(y1, 0, maxY-1);

        auto c0 = orientationCoordinates(x0, y0);
        auto c1 = orientationCoordinates(x1, y1);

        x0 = c0.first;
        y0 = c0.second;

        x1 = c1.first;
        y1 = c1.second;


        if (x1 < x0)
            std::swap(x0, x1);

        if (y1 < y0)
            std::swap(y0, y1);

        int dmode = modeTab[orientation][mode];

        writeRegister(ILI9225_ENTRY_MODE, 0x1000 | (dmode << 3));    // BGR | I/D | AM
        writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR1, x1);
        writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR2, x0);

        writeRegister(ILI9225_VERTICAL_WINDOW_ADDR1, y1);
        writeRegister(ILI9225_VERTICAL_WINDOW_ADDR2, y0);

        int dcase = dmode>>1;

        if (dcase == 0) {
            writeRegister(ILI9225_RAM_ADDR_SET1, x1);
            writeRegister(ILI9225_RAM_ADDR_SET2, y1);
        } else if (dcase == 1) {
            writeRegister(ILI9225_RAM_ADDR_SET1, x0);
            writeRegister(ILI9225_RAM_ADDR_SET2, y1);
        } else if (dcase == 2) {
            writeRegister(ILI9225_RAM_ADDR_SET1, x1);
            writeRegister(ILI9225_RAM_ADDR_SET2, y0);
        } else if (dcase == 3) {
            writeRegister(ILI9225_RAM_ADDR_SET1, x0);
            writeRegister(ILI9225_RAM_ADDR_SET2, y0);
        }

        writeCommand(ILI9225_GRAM_DATA_REG);
    }

    void resetWindow() {
        writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR1, 0x00AF);
        writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR2, 0x0000);
        writeRegister(ILI9225_VERTICAL_WINDOW_ADDR1, 0x00DB);
        writeRegister(ILI9225_VERTICAL_WINDOW_ADDR2, 0x0000);
    }

    void horizontalLine(int x, int y, int width, uint16_t colour) {
        /// Draw horizontal line on screen.

        fillRectangle(x, y, width, 1, colour);
    }

    void verticalLine(int x, int y, int height, uint16_t colour) {
        /// Draw vertical line on screen."""

        fillRectangle(x, y, 1, height, colour);
    }

    void setOrientation(int o) {
        /// Set orientation of screen.

        /*
        0=portrait
        1=right rotated landscape
        2=reverse portrait
        3=left rotated landscape
        */

        orientation = o % 4;

        switch (orientation) {
            case 0:
                maxX = ILI9225_LCD_WIDTH;
                maxY = ILI9225_LCD_HEIGHT;
                break;
            case 1:
                maxX = ILI9225_LCD_HEIGHT;
                maxY = ILI9225_LCD_WIDTH;
                break;
            case 2:
                maxX = ILI9225_LCD_WIDTH;
                maxY = ILI9225_LCD_HEIGHT;
                break;
            case 3:
                maxX = ILI9225_LCD_HEIGHT;
                maxY = ILI9225_LCD_WIDTH;
                break;
        }
    }

    uint16_t getBGColour() const {
        return bgColour;
    }
};

#endif // ILI9225_H_
