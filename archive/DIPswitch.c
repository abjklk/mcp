#include<at89c51xd2.h>
void lcd_init(void);				//To initialise LCD device
void lcd_comm(void);				//To transmit commands
void lcd_data(void);				//To transmit data
void clear_lcd(void);				//To clear LCD
void wr_cn(void);					//Used to send 4 bytes at a time
void wr_dn(void);					//Same as above
void delay(unsigned int);			//Delay for proper LCD Output

unsigned char temp1;				//LCD command
unsigned char temp2;				//LCD data
unsigned char i;					//Iterator
unsigned char var;
unsigned char arr[18]="DIP switch status";
unsigned int read_switch;

void main(void)
{			
	unsigned char local_var;
	lcd_init();
	clear_lcd();
	//temp1=0x80;
	//lcd_comm();
	P0=0xFF;
	for(i=0;i<18;i++)
	{
		temp2=arr[i];
		lcd_data();
	}

	while(1)
	{
		temp1=0xC4;
		lcd_comm();
		read_switch=P0;
		for(i=0;i<8;i++)
		{
			local_var=read_switch>>i;
			temp2=((local_var&0x01)==0x01)?'0':'1';
			lcd_data();
			local_var=0;
		}
	}
}