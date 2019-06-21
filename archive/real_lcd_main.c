#include<AT89C51XD2.h>

void lcd_init(void);	
void lcd_comm(void);		
void lcd_data(void);	
void clear_lcd(void);
void lcd_init1(void);	
void lcd_comm1(void);		
void lcd_data1(void);	
void clear_lcd1(void);	
void delay(unsigned char);		

unsigned char temp1,temp2;
unsigned char arr[17] = "DIP STATUS";
unsigned int read_switch;
unsigned char i;		

void main(void)
{
	unsigned char local_var;
	lcd_init();
	clear_lcd();
	P0=0xFF;
	temp1=0x80;
	lcd_comm();
	for(i=0;i<16;i++)
	{
		temp2=arr[i];
		lcd_data();
	}

	while(1)
	{
		temp1=0xC4;
		lcd_comm();
		read_switch = P0;
		for(i=0;i<8;i++)
		{
			local_var = read_switch>>i;
			temp2 = ((local_var & 0x01) == 0x01 ? '0' : '1');
			lcd_data();
			local_var=0;
		}
	}
}