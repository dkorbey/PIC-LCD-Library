#ifndef LCD_LIB_H
#define LCD_LIB_H

/* 
 * File: lcd_lib.h
 * Author: Korbey
 * Comments: It's a LCD library for PIC microcontrollers (the one I used is PIC18F4585)
 * Revision history: version 2.1 
 */

/* Includes ------------------------------------------------------------------*/
#include <xc.h>
#include <stdint.h> // for the uint8_t

// Crystal Frequency 
#define _XTAL_FREQ  16000000

/* Pins ----------------------------------------------------------------------*/
#define LCD_D7      LATDbits.LATD7
#define LCD_D6      LATDbits.LATD6
#define LCD_D5      LATDbits.LATD5
#define LCD_D4      LATDbits.LATD4
#define LCD_RS      LATDbits.LATD2
// RW is connected to the ground
#define LCD_E       LATDbits.LATD3

// LCD Dimensions (Not used for now)
#define NB_LINES    2                   // Number of display lines
#define NB_COL      16                  // Number of characters per line

/* Instruction register bit positions, see HD44780U data sheet ---------------*/
#define LCD_DDRAM          7 /* DB7: set DD RAM address             */   
#define LCD_CGRAM          6 /* DB6: set DD RAM address             */   
#define LCD_START_LINE1 0x00 /* DDRAM address of first char of line 1 */
#define LCD_START_LINE2 0x40 /* DDRAM address of first char of line 2 */

/* Command Set ---------------------------------------------------------------*/
// Instruction: Clear Display
#define LCD_CLEAR               0x01
// Instruction: Return Home
#define LCD_HOME                0x02
// Instruction: Entry Mode Set
#define LCD_CURSOR_INC_FW       0x06
#define LCD_CURSOR_INC_BW       0x04
// Instruction: Display on/off control
#define LCD_OFF                 0x08
#define LCD_ON                  0x0C
#define LCD_ON_CURSOR           0x0E
#define LCD_ON_CURSOR_BLINK     0x0F
// Instruction: Cursor or Display Shift
#define CURSOR_MOVE_RIGHT       0x14
#define CURSOR_MOVE_LEFT        0x10
#define DISP_MOVE_RIGHT         0x1C
#define DISP_MOVE_LEFT          0x18

// For LCD init
#define FUNCTION_SET_4_BIT      0x28    // 4 bit interface, 2 lines, 5x8 font    
#define FUNCTION_SET_8_BIT      0x30    // 0b00110000
#define ENTRY_MODE_SET          0x06    // Cursor Increment Forward  

/* Functions with define tag--------------------------------------------------*/

// Clear Screen and Home Functions
//#define lcd_clrscr() do{lcd_command(LCD_CLEAR);__delay_us(2000);}while(0)
//#define lcd_home() do{lcd_command(LCD_HOME);__delay_us(2000);}while(0)

/* Function Prototypes--------------------------------------------------------*/

/**
 * Initialize the LCD in 4-bit, 2 lines and 5x8 dots mode
 * For the initialize process check the HD44780 datasheet page 46
 */
void lcd_init(void);

/**
 * 
 * @param data  8-bit Data or Instruction
 * @param rs    Register Select
 * @param m     1: Only High 4 Bits (I add this parameter to use in init process)
 *              2: High and Low 4 Bits
 */
void lcd_write(uint8_t data, uint8_t rs, uint8_t m);

/**
 * Sending instructions to the LCD
 * @param cmd
 */
void lcd_command(uint8_t cmd);

/**
 * Sending data to be displayed to the LCD
 * @param c
 */
void lcd_putc(uint8_t c);

/**
 * Writing string on the LCD
 * @param str
 */
void lcd_puts(const char *str);

/**
 * Move the cursor to the position (x:col,y:line)
 * @param x     columns: 0-15    
 * @param y     line: 0-1
 */
void lcd_gotoxy(uint8_t x, uint8_t y);

/**
 * Clear the display screen
 */
void lcd_clrscr(void);

/**
 *  Move the cursor 1st line 1st bar
 */
void lcd_home(void);


void lcd_customchar(uint8_t location, uint8_t customChar[]);

#endif