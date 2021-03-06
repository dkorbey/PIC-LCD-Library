/*
 * File:   lcd_lib.c
 * Author: dkorb
 *
 * Created on 25 Nisan 2021 Pazar, 12:25
 */

#include "lcd_lib.h"

void lcd_init(void)
{        
    LCD_D7 = 0;
    LCD_D6 = 0;
    LCD_D5 = 0;
    LCD_D4 = 0;
    LCD_RS = 0;
    LCD_E = 0;
    
    /* Look datasheet page 46 */
    
    // required by display controller to allow power to stabilize
    __delay_ms(50);
    
    lcd_write(FUNCTION_SET_8_BIT,0,1);
    __delay_us(4500); // wait more than 4.1ms(4100us)
    
    lcd_write(FUNCTION_SET_8_BIT,0,1);
    __delay_us(250); // wait more than 100us
    
    lcd_write(FUNCTION_SET_8_BIT,0,1);
    
    // Set to 4 bit interface
    lcd_write(FUNCTION_SET_4_BIT,0,1);
    
    // 4 bit interface, 2 lines, 5x8 font
    lcd_command(FUNCTION_SET_4_BIT);
    
    // Turn the display on with no cursor or blinking default
    lcd_command(LCD_ON);
    
    // Clear Screen
    lcd_clrscr();
    
    // Cursor Increment Forward  
    lcd_command(ENTRY_MODE_SET);
}

void lcd_write(uint8_t data, uint8_t rs, uint8_t m)
{      
    LCD_RS = rs;
    LCD_E = 0;
    
    uint8_t datas[] = {data,data << 4};
    
    for(int i = 0; i<m; i++) {
        // Sending the high bits
        LCD_D7 = ((datas[i] >> 7) & 0x01);
        LCD_D6 = ((datas[i] >> 6) & 0x01);
        LCD_D5 = ((datas[i] >> 5) & 0x01);
        LCD_D4 = ((datas[i] >> 4) & 0x01);
        
        __delay_us(1);
        LCD_E = 1;
        __delay_us(1);
         LCD_E = 0;
        __delay_us(750);    
    }
}

void lcd_command(uint8_t cmd)
{
    lcd_write(cmd,0,2);
}

void lcd_putc(uint8_t c)
{
    lcd_write(c,1,2);
}

void lcd_puts(const char *str)
{
    uint8_t i=0;
    
    // While string has not been fully traveresed
    while (str[i])
    {
        // Go display current char
        lcd_putc(str[i++]);
    }
}

void lcd_gotoxy(uint8_t x, uint8_t y)
{
    if (y == 0)
        lcd_command((1 << LCD_DDRAM) + LCD_START_LINE1 + x);
    else
        lcd_command((1 << LCD_DDRAM) + LCD_START_LINE2 + x);    
}

void lcd_clrscr(void)
{
    lcd_command(LCD_CLEAR);
    __delay_us(2000);
}

void lcd_home(void)
{
    lcd_command(LCD_HOME);
    __delay_us(2000);
}

void lcd_customchar(uint8_t location, uint8_t customChar[])
{
    // Location should be between 0 and 7, because of that we need only 
    // the right most 3 bits of the location
    location &= 0x07;
    
    // Sets the CGRAM adress location as wanted
    lcd_command((1 << LCD_CGRAM) + (location << 3));
    
    for(uint8_t i = 0; i<8; i++)
    {
        // Store custom char to memory line by line
        lcd_putc(customChar[i]);
    }
    
    // Set DDRAM address
    lcd_command(1 << LCD_DDRAM);
}