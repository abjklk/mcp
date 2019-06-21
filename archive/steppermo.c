#include<at89C51XD2.h>

void delay(unsigned int x)
{
 for(;x>0;x--) ;
}
main()
{
 unsigned char val , i;
 while(1)
 {
  val=0x08;
  for(i=0;i<4;i++)
  {
   P0=val;
   val=val>>1;
    delay(1000);
  }
 /* delay(1000)	;
   {
  val=0x01;
  for(i=0;i<4;i++)
  {
   P0=val;
   val=val<<1;
    delay(1500);
  }
  }*/
}
}