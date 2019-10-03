#include <REGX51.H>
#define uint unsigned int
#define uchar unsigned char


uchar Receive,i,qj,yz,zz,ht;
uint n;
uchar Recive_table[40];



void ms_delay(uint t)
{
uint i,j;
for(i=t;i>0;i--)
for(j=110;j>0;j--);
}


void us_delay(uchar t)
{
while(t--);
}


void Uart_Init()
{
TMOD = 0x20;
SCON = 0x50;
TH1 = 0xFD;
TL1 = TH1;
PCON = 0x00;
EA = 1; 
ES = 1;
TR1 = 1;
}




void Send_Uart(uchar value)
{
ES=0;
TI=0; 
SBUF=value;
while(TI==0);
TI=0; 
ES=1; 
}






void ESP8266_Set(uchar *puf) 
{
while(*puf!='\0') 
{
Send_Uart(*puf);
us_delay(5);
puf++;
}
us_delay(5);
Send_Uart('\r');
us_delay(5);
Send_Uart('\n');
}





void main()
{
Uart_Init();
ms_delay(2000);
ESP8266_Set("AT+CWMODE=2");
ms_delay(2000);
// ESP8266_Set("AT+RST");
// ms_delay(2000);
ESP8266_Set("AT+CWSAP=\"wifi\",\"123456789\",11,4"); //AT+CWSAP="wifi","123456789",11,4
ms_delay(2000);
ESP8266_Set("AT+CIPMUX=1");
ms_delay(2000);
ESP8266_Set("AT+CIPSERVER=1,5000");
ms_delay(2000);
ESP8266_Set("AT+CIPSTO=0");
ES=1;
qj=1;
zz=1;
yz=1;
ht=1;
while(1)
{
if((Recive_table[0]=='c')&&(Recive_table[1]=='c')&&(Recive_table[2]=='o'))
{
if(Recive_table[3]=='k')
{
if(Recive_table[4]=='1')
{
qj=0; //前进
zz=1;
yz=1;
ht=1;
}
else
if (Recive_table[4]=='2')
{
qj=1;
zz=1;
yz=1;
ht=0; // 后退
}
else
if (Recive_table[4]=='3')
{
//qj=1; //
zz=1;
yz=0; //右转
// ht=1;
}
else
if (Recive_table[4]=='4')
{
// qj=1; //
zz=0; //左转
yz=1;
// ht=1;
}
else
if (Recive_table[4]=='0')
{
qj=1;//停止
zz=1;
yz=1;
ht=1;
}
}
}
if(qj==0)
{
if((zz==0)|(yz==0))
{
;
}
else
{
P2=0xaa;
}
}
if(ht==0)
{
if((zz==0)|(yz==0))
{
;
}
else
{
P2=0x55;
}
}
if(zz==0)
{
if(ht==1)
{
P2=0x02;
}
else
{
P2=0x01;
}
}
if(yz==0)
{
if(ht==1)
{
P2=0x08;
}
else
{
P2=0x40;
}
}
}
}






void Uart_Interrupt() interrupt 4
{
static uchar i=0;
if(RI==1)
{
RI=0;
Receive=SBUF;
Recive_table[ i]=Receive;
if((Recive_table[ i]=='\n'))
	{ i=0;} 
else i++; } else TI=0;
 }
