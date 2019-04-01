#include "G:\emc\project\at89c51xd2.h"
unsigned char temp1;
unsigned char temp2;
unsigned char LCD_CODE[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
sbit dc1=P0^6;
sbit dc2=P0^7;
unsigned char wc[8]="Welcome!";
unsigned char en[15]="Enter Password.";
unsigned char grant[15]="Access Granted!";
unsigned char deny[14]="Access Denied!";
unsigned char i;
unsigned char pass[5]="abcde";
unsigned char ip[5]="";

void lcd_init();
void clear_lcd();
void lcd_comm();
void lcd_data();
void print_wc();
int strcheck(char [], char []);
void print_enter();
void print_grant();
void print_deny();
void Tdelay();
void hex_input();
void lock();
void unlock();


void main()
{
	print_wc();						 //print welcome!
	for(i=0;i<3;i++)			   	 //wait 3s
		Tdelay();
	while(1)
	{
		print_enter();				 //print enter pswd
		temp1=0xc4;
		lcd_comm();
		hex_input();				 //takes hexkeypad input
		Tdelay();			  			//some delay 
		if(strcheck(pass,ip)==0)		//compares passwds
		{	
			print_grant();				 //print access granted
			unlock();					 //turn motor
			for(i=0;i<5;i++)
				Tdelay();
			lock();						  //lock again after some time.
		}
		else
		{								//intruder
			print_deny();			   //prints denial
			for(i=0;i<3;i++)			//delay and back to enter password.
				Tdelay();
		}
	}
}


void print_wc()
{
	lcd_init();		//check
	clear_lcd();
	temp1=0x80;
	lcd_comm();
	for(i=0;i<8;i++)
	{
		temp2=wc[i];
		lcd_data();
	}
}


void print_enter()
{
	lcd_init();		//check
	clear_lcd();
	temp1=0x80;
	lcd_comm();
	for(i=0;i<15;i++)
	{
		temp2=en[i];
		lcd_data();
	}
}

void print_grant()
{
	lcd_init();		//check
	clear_lcd();
	temp1=0x80;
	lcd_comm();
	for(i=0;i<15;i++)
	{
		temp2=grant[i];
		lcd_data();
	}
}

void print_deny()
{
	lcd_init();		//check
	clear_lcd();
	temp1=0x80;
	lcd_comm();
	for(i=0;i<14;i++)
	{
		temp2=deny[i];
		lcd_data();
	}
}




void Tdelay()
{
	int i;
	//71.1ms x 14 = 1s delay
	TMOD=0x01;
	for(i=0;i<14;i++)
	{
		TL0=0x00;
		TH0=0x00;
		TR0=1;
		while(!TF0);
		TR0=0;
		TF0=0;
	}
}

void hex_input()
{
	int x=0;
	unsigned char key,row,col,mask,val;
	do{
		for(row=0x00;row<=0x03;++row)
		{
			P0=~(0x01<<row);
			key=P0;
			if((key&0xF0)!=0xF0)
			{
				for(mask=0x10,col=0x00;mask&key;mask<<=1)
				++col;
				val=col*4+row;
				ip[i]=LCD_CODE[val];   //add each char of input to array? 
				i++;
				temp2='X';
				lcd_data();	
			}
		}
	}while(x<5);
}

int strcheck(char a[],char b[])
{
	int c;
	int flag=0;
	for(c=0;c<5;c++)
	{						//checks passwords
		if(a[c]!=b[c])
			 flag=1;
	}
	return flag;
}

void lock()
{
	int i;
	dc1=0;
	dc2=1;
	for(i=0;i<3;i++)	   //change motor time here
		Tdelay();
	dc1=1;
	dc2=1;
}

void unlock()
{
	int i;
	dc1=1;
	dc2=0;
	for(i=0;i<3;i++)		 //change motor time here
		Tdelay();
	dc1=1;
	dc2=1;
}