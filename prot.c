#include "G:\emc\at89c51xd2.h"

void lcd_data(unsigned char);
void lcd_init();
void lcd_cmd(unsigned char);
void msdelay(unsigned int);

sbit c1=P1^4;
sbit c2=P1^5;
sbit c3=P1^6;
sbit r1=P1^0;
sbit r2=P1^1;
sbit r3=P1^2;
sbit r4=P1^3;
sbit dc1=P3^0;
int eflag=0;
int cl=0;

void lock();
void unlock();
void row_finder1();
void row_finder2();
void row_finder3();
void print_wc();
void print_enter();
void print_grant();
void print_deny();
int strcheck(char [],char []);

unsigned char wc[8]="Welcome!";
unsigned char en[15]="Enter Password.";
unsigned char grant[15]="Access Granted!";
unsigned char deny[14]="Access Denied!";
unsigned char pass[5]="12345";
unsigned char ip[5]="";

void main()
{
	dc1=0;
    //unsigned char a[15]="hex value is";    //string of 14 characters with a null terminator.
    /*while(a[l] != '\0') // searching the null terminator in the sentence
    {
        lcd_data(a[l]);
        l++;
        msdelay(50);
    }  */
	print_wc();
	msdelay(100);
	print_enter();
	lcd_cmd(0xc4);
	
		 msdelay(30); 
		 //do{
		 while(1)
		 {
		 	c1=c2=c3=1;
         	r1=r2=r3=r4=0;
			 if(c1==0)
	           row_finder1();
	         else if(c2==0)
	           row_finder2();
	         else if(c3==0)
	           row_finder3();
			if(eflag==1)
			break;
			msdelay(30);
		}	   
		if(strcheck(pass,ip)==0)
		{
			print_grant();
			unlock();
			msdelay(200);
			lock();
			msdelay(200);
		}
		else
		print_deny();

		 	//}while(eflag!=1);
}

void print_wc()
{
	int l=0;
	lcd_init();
	while(wc[l] != '\0') // searching the null terminator in the sentence
    {
        lcd_data(wc[l]);
        l++;
        msdelay(5);
    }
}

void print_enter()
{
	int l=0;
	lcd_init();
	while(en[l] != '\0') // searching the null terminator in the sentence
    {
        lcd_data(en[l]);
        l++;
        msdelay(5);
    }
}

void print_grant()
{
	int l=0;
	lcd_init();
	for(l=0;l<14;l++)
	{
		lcd_data(grant[l]);
		msdelay(5);
	}
	/*while(grant[l] != '\0') // searching the null terminator in the sentence
    {
        lcd_data(grant[l]);
        l++;
        msdelay(5);
    }			 */
}

void print_deny()
{
	int l=0;
	lcd_init();
	for(l=0;l<14;l++)
	{
		lcd_data(deny[l]);
		msdelay(5);
	}
	/*while(deny[l] != '\0') // searching the null terminator in the sentence
    {
        lcd_data(deny[l]);
        l++;
        msdelay(5);
    }*/
}


int strcheck(char p[],char b[])
{
	int c;
	int flag=0;
	while(p[c]!= '\0' )
	{							//checks passwords
		if(p[c]!=b[c])
			 flag=1;
		c++;
	}
	return flag;
}


void row_finder1() //Function for finding the row for column 1
{
	r1=r2=r3=r4=1;
	c1=c2=c3=0;
	
	if(r1==0)
	{
		lcd_data('1');
		ip[cl]='1';
		cl++;
	 }
	if(r2==0)
	{
		lcd_data('4');
		ip[cl]='4';
		cl++;
	}
	if(r3==0)
	{
	lcd_data('7');
	ip[cl]='7';
		cl++;
	 }
	if(r4==0)
	{
	lcd_data('*');
	ip[cl]='*';
		cl++;
	}
}

void row_finder2() //Function for finding the row for column 2
{
	r1=r2=r3=r4=1;
	c1=c2=c3=0;
	
	if(r1==0)
	{
	lcd_data('2');
	ip[cl]='2';
		cl++;
	}
	if(r2==0)
	{
	lcd_data('5');
	ip[cl]='5';
		cl++;
	}
	if(r3==0)
	{
	lcd_data('8');
	ip[cl]='8';
		cl++;
	}
	if(r4==0)
	{
	lcd_data('0');
	ip[cl]='0';
		cl++;
	}
}

void row_finder3() //Function for finding the row for column 3
{
	r1=r2=r3=r4=1;
	c1=c2=c3=0;
	
	if(r1==0)	  {
	lcd_data('3');
	ip[cl]='3';
		cl++;
		}
	if(r2==0)
	{
	lcd_data('6');
	ip[cl]='6';
		cl++;
	}
	if(r3==0)
	{
	lcd_data('9');
	ip[cl]='9';
		cl++;
	}
	if(r4==0)
	{
		lcd_data('#');
		eflag=1;
	}
}

void lock()
{
	dc1=0;
}

void unlock()
{
	dc1=1;
}