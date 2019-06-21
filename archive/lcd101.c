 #include<AT89C51XD2.h>
extern void lcd_comm(void);
extern void wr_cn(void);
extern void wr_dn(void);
void delay(unsigned int);

extern unsigned char temp1;
extern unsigned char temp2;
unsigned char var;	

void lcd_init(void)
{
	temp1=0x30;		//Set P2.4=1(VCC) and P2.5=1(R'/W)
	wr_cn();
	delay(500);
	
	temp1=0x28;		//4-bit, 2 lines and 5*7 matrix
	lcd_comm();
	delay(500);
	
	temp1=0x0f;		//display on,cursor on, curosr blinking
	lcd_comm();
	delay(500);
	
	temp1=0x06;
	lcd_comm();
	delay(500);
	
	temp1=0x80;
	lcd_comm();
	delay(500);
	
}

void lcd_comm(void)
{
	var=temp1;
	temp1=temp1&0xf0;
	temp1=temp1>>4;
	wr_cn();
	
	temp1=var&0x0f;
	wr_cn();
	delay(60);
}

void lcd_data(void)
{
	var=temp2;
	temp2=temp2&0xf0;
	temp2=temp2>>4;
	wr_dn();
	
	temp2=var&0x0f;
	wr_dn();
	
	delay(60);
}

void wr_cn(void)
{
	temp1=temp1&0x7f;
	temp1=temp1|0x40;
	P2=temp1;
	delay(450);
	temp1=temp1&0xbf;
	P2=temp1;
}

void wr_dn(void)
{
	temp2=temp2|0xc0;
	temp2=temp2&0xdf;
	P2=temp2;
	
	delay(450);
	
	temp2=temp2&0xbf;
	P2=temp2;
}

void clear_lcd(void)
{
	temp1=0x01;
	lcd_comm();
	delay(500);	
}

void delay(unsigned int count)
{
	unsigned int i;
	for(i=0;i<count;i++);
}
