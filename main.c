/*
 * Gnss_rtk.c
 *
 * Created: 28-03-2023 20:36:51
 * Author : sumit.chatterjee
 */ 

#include <avr/io.h>
#include <string.h>
#include "uart.h"
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#define Baud
#define BaudRate(Baud) (((F_CPU /(Baud * 16UL)))-1)

int main(void)
{
    /* Replace with your application code */
	UART_init(BaudRate(9600));
	char * data;
	int i=0;
	char defa[82]={'\0'};
    while (1) 
    {
		while(UART_Available()>0){
			*data=UART_recieve();
			if (*data == '\n'|| *data == '\r')
			{
				defa[i+1]='\n';
				break;
			}
			if (*data != '\0')
			{
				if(*data=='$'){
					memset(defa,0,sizeof(defa));
					i=0;
					defa[i]=*data;
				}
				else if(*data != '$'){
					i+=1;
					defa[i]=*data;
				}
				}
			}
				//Write_String("hhh");
				Write_String(defa);	
		}
	}

		
/*	if(UART_Available()>0){
k=1;
while(k>0){
char data = Read_char();
Write_char(data);
if (data !='\n'){
if (data !='\0'){
j++;
}
buff[j]=data;
k++;
}
else{
if (buff[1]=='$')
{

Write_String("Val:");
for (int m=1; m<k; m+=1)
{
if((buff[m]=='$')&&(buff[m+1]=='G')&&(buff[m+2]=='N')){
if ((buff[m]=='$')&&(buff[m+1]=='G')&&(buff[m+2]=='N')&&(buff[m+3]=='R')&&(buff[m+4]=='M')&&(buff[m+5]=='C'))
{
Write_String("ID:GNRMC......\n");
if (buff[m+6]==','){
int z=6;
while(z>0){
z+=1;
Write_char(buff[m+z]);
if (buff[m+z]==','){
break;
}
}
}
}
else if ((buff[m]=='$')&&(buff[m+1]=='G')&&(buff[m+2]=='N')&&(buff[m+3]=='G')&&(buff[m+4]=='G')&&(buff[m+5]=='A'))
{
Write_String("ID:GNGGA......\n");
}
}

Write_char(buff[m]);
}
Write_char('\r');
}
k=0;
j=0;
}
}
}
}
//Write_dec16(num);
//((char)getSize(data));
*/