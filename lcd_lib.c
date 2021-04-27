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
    __delay_ms(45);
    
    lcd_write(FUNCTION_SET_8_BIT,0,1);
    __delay_us(4500); // wait min 4.1ms
    
    lcd_write(FUNCTION_SET_8_BIT,0,1);
    __delay_us(250); // wait min 4.1ms
    
    lcd_write(FUNCTION_SET_4_BIT,0,1);
    
    lcd_command(FUNCTION_SET_4_BIT);
    
    // turn the display on with no cursor or blinking default
    lcd_command(LCD_ON);
    
    lcd_clrscr();
    
    lcd_command(ENTRY_MODE_SET);
}

void lcd_write(uint8_t data, uint8_t rs, uint8_t m)
{      
    LCD_RS = rs;
    
    uint8_t temp = data << 4;
    uint8_t datas[] = {data,temp};
    
    for(int i = 0; i<m; i++) {
        // Sending the high bits
        LCD_D7 = ((datas[i] >> 7) & 0x01);
        LCD_D6 = ((datas[i] >> 6) & 0x01);
        LCD_D5 = ((datas[i] >> 5) & 0x01);
        LCD_D4 = ((datas[i] >> 4) & 0x01);
        
        LCD_E = 1;
        __delay_us(1);
         LCD_E = 0;
        __delay_us(100);    
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