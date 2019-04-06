
#include "G:\emc\at89c51xd2.h"
#define display_port P2      //Data pins connected to port 2 on microcontroller
sbit rs = P3^5;  //RS pin connected to pin 2 of port 3
sbit rw = P3^6;  // RW pin connected to pin 3 of port 3
sbit e =  P3^7;  //E pin connected to pin 4 of port 3

extern void msdelay(unsigned int time)  // Function for creating delay in milliseconds.
{
    unsigned i,j ;
    for(i=0;i<time;i++)    
    for(j=0;j<1275;j++);
}
extern void lcd_cmd(unsigned char command)  //Function to send command instruction to LCD
{
    display_port = command;
    rs= 0;
    rw=0;
    e=1;
    msdelay(1);
    e=0;
}

extern void lcd_data(unsigned char disp_data)  //Function to send display data to LCD
{
    display_port = disp_data;
    rs= 1;
    rw=0;
    e=1;
    msdelay(1);
    e=0;
}

extern void lcd_init()    //Function to prepare the LCD  and get it ready
{
    lcd_cmd(0x38);  // for using 2 lines and 5X7 matrix of LCD
    msdelay(10);
    lcd_cmd(0x0F);  // turn display ON, cursor blinking
    msdelay(10);
    lcd_cmd(0x01);  //clear screen
    msdelay(10);
    lcd_cmd(0x80);  // bring cursor to position 1 of line 1
    msdelay(10);
}


 