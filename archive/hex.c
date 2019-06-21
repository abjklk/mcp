	//LCD Function Prototype
#include "G:\gmc\at89c51xd2.h"
void lcd_init(void);		//to initialize the LCD 
void lcd_comm(void);		//to transmit commands to LCD
void lcd_data(void);		//to transmit data to LCD
void clear_lcd(void);		//to clear LCD screen
void delay(unsigned char);		//delay for proper LCD operation

unsigned char temp1;		//LCD Command
unsigned char temp2;		//LCD Data
unsigned char key,row,col,mask,val;
unsigned char arr[17]="KEY PRESSED IS";		//To be displayed on 1st line
unsigned char i;		//used in for loop for iteration count
unsigned char LCD_CODE[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void main()
{
	lcd_init();		//LCD initialisation
	clear_lcd();	//Clear LCD Screen
	temp1=0x80;		//Display the data from first position of first  
	lcd_comm();		//command writing
	
	for(i=0;i<6;i++)	//
	{
		temp2=arr[i];	//data to be displayed
		lcd_data();		//data writing
	}
	while(1)
	{
		temp1=0xc4;
		lcd_comm();
		for(row=0x00;row<=0x03;++row)
		{
			P0=~(0x01<<row);
			key=P0;
			if((key&0xF0)!=0xF0)
			{
				for(mask=0x10,col=0x00;mask&key;mask<<=1)
				++col;
				val=col*4+row;
				temp2=LCD_CODE[val];
				lcd_data();
			}
		}
	}
}