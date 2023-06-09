/*
 * uart.c
 *
 * Created: 28-03-2023 16:29:51
 *  Author: sumit.chatterjee
 */ 

#include <avr/io.h>
#include "uart.h"

void UART_init(unsigned int ubrr)
{
	// Set Baud Rate
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	// Enable Receiver and Transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	// Set Frame Format
	UCSR0C = (1<<USBS0) | (3<<UCSZ00)|(0<<UMSEL00);
}

void UART_transmit(unsigned char data){
	while(!(UCSR0A & (1<<UDRE0))) {};
	UDR0 = data;
}

unsigned char UART_recieve(){
	while(!(UCSR0A & (1<<RXC0))) {};
	return UDR0;
}

void Write_char(char val){
	while(!(UCSR0A & (1<<UDRE0))) {};
	UDR0 = val;
}

char Read_char(){
	while(!(UCSR0A &(1<<RXC0))) {};
	return UDR0;
}

void WriteString(char *s){
	while (*s)
	{
		Write_char(*s);
		s++;
	}
}

void Write_String(char* StringPtr){
	while(*StringPtr != 0x00){
		Write_char(*StringPtr);
	StringPtr++;}
}

unsigned char UART_Available(void) {
	//return nonzero if char waiting polled version
	unsigned char b;
	b=0;
	if(UCSR0A & (1<<RXC0)) b=1;
	return b;
}
signed int DOR_error(){
	signed int a;
	a=0;
	if (UCSR0A & (1<<DOR0)) a=-1;
	return a;
}
signed int Frame_error(){
	signed int k;
	k=0;
	if (UCSR0A & (1<<FE0)) k=-1;
	return k;
}
signed int Parity_error(){
	signed int m;
	m=0;
	if (UCSR0A & (1<<UPE0)) m=-1;
	return m;
}


void Write_hex8(uint8_t val)
{
	// extract upper and lower nibbles from input value
	uint8_t upperNibble = (val & 0xF0) >> 4;
	uint8_t lowerNibble = val & 0x0F;

	// convert nibble to its ASCII hex equivalent
	upperNibble += upperNibble > 9 ? 'A' - 10 : '0';
	lowerNibble += lowerNibble > 9 ? 'A' - 10 : '0';

	// print the characters
	Write_char(upperNibble);
	Write_char(lowerNibble);
}

void Write_hex16(uint16_t val)
{
	// transmit upper 8 bits
	Write_hex8((uint8_t)(val >> 8));

	// transmit lower 8 bits
	Write_hex8((uint8_t)(val & 0x00FF));
}

void Write_dec8(uint8_t val)
{
	uint8_t dig1 = '0', dig2 = '0';

	// count value in 100s place
	while(val >= 100)
	{
		val -= 100;
		dig1++;
	}

	// count value in 10s place
	while(val >= 10)
	{
		val -= 10;
		dig2++;
	}

	// print first digit (or ignore leading zeros)
	if(dig1 != '0') Write_char(dig1);

	// print second digit (or ignore leading zeros)
	if((dig1 != '0') || (dig2 != '0')) Write_char(dig2);

	// print final digit
	Write_char(val + '0');
}

void Write_Ndec8(int8_t val)
{
	// check for negative number
	if(val & 0x80)
	{
		// print negative sign
		Write_char('-');

		// get unsigned magnitude
		val = ~(val - 1);
	}

	// print magnitude
	Write_dec8((uint8_t)val);
}

void Write_dec16(uint16_t val)
{
	uint8_t dig1 = '0', dig2 = '0', dig3 = '0', dig4 = '0';

	// count value in 10000s place
	while(val >= 10000)
	{
		val -= 10000;
		dig1++;
	}

	// count value in 1000s place
	while(val >= 1000)
	{
		val -= 1000;
		dig2++;
	}

	// count value in 100s place
	while(val >= 100)
	{
		val -= 100;
		dig3++;
	}

	// count value in 10s place
	while(val >= 10)
	{
		val -= 10;
		dig4++;
	}

	// was previous value printed?
	uint8_t prevPrinted = 0;

	// print first digit (or ignore leading zeros)
	if(dig1 != '0') {Write_char(dig1); prevPrinted = 1;}

	// print second digit (or ignore leading zeros)
	if(prevPrinted || (dig2 != '0')) {Write_char(dig2); prevPrinted = 1;}

	// print third digit (or ignore leading zeros)
	if(prevPrinted || (dig3 != '0')) {Write_char(dig3); prevPrinted = 1;}

	// print third digit (or ignore leading zeros)
	if(prevPrinted || (dig4 != '0')) {Write_char(dig4); prevPrinted = 1;}

	// print final digit
	Write_char(val + '0');
}

void Write_Ndec16(int16_t val)
{
	// check for negative number
	if(val & 0x8000)
	{
		// print minus sign
		Write_char('-');

		// convert to unsigned magnitude
		val = ~(val - 1);
	}

	// print unsigned magnitude
	Write_dec16((uint16_t) val);
}


void UART_transmitByte(uint8_t data) {
	/* Wait for empty transmit buffer */
	while(!(UCSR0A & (1<<UDRE0))) {};
	UDR0 = data;                                            /* send data */
}

uint8_t UART_receiveByte(void) {
	while(!(UCSR0A & (1<<RXC0))) {};       /* Wait for incoming data */
	return UDR0;                                /* return register value */
}


/* Here are a bunch of useful printing commands */

void UART_WrtiteString(const char myString[]) {
	uint8_t i = 0;
	while (myString[i]) {
		UART_transmitByte(myString[i]);
		i++;
	}
}


int Read_getSize (char * s) {
	char * t; // first copy the pointer to not change the original
	int size = 0;

	for (t = s; *t != '\0'; t++) {
		size++;
	}

	return size;
}

int Readline_getSize (char * s) {
	char * t; // first copy the pointer to not change the original
	int size = 0;

	for (t = s; *t != '\n'; t++) {
		size++;
	}

	return size;
}

int toString(char a[]) {
	int c, sign, offset, n;

	if (a[0] == '-') {  // Handle negative integers
		sign = -1;
	}

	if (sign == -1) {  // Set starting position to convert
		offset = 1;
	}
	else {
		offset = 0;
	}

	n = 0;

	for (c = offset; a[c] != '\0'; c++) {
		n = n * 10 + a[c] - '0';
	}

	if (sign == -1) {
		n = -n;
	}

	return n;
}

int StringtoInt(const char *s)
{
	int sign=1;
	if(*s == '-'){
		sign = -1;
		s++;
	}
	int num=0;
	while(*s){
		num=((*s)-'0')+num*10;
		s++;
	}
	return num*sign;
}

void UART_WriteByte(uint8_t byte) {
	/* Converts a byte to a string of decimal text, sends it */
	UART_transmitByte('0' + (byte / 100));                        /* Hundreds */
	UART_transmitByte('0' + ((byte / 10) % 10));                      /* Tens */
	UART_transmitByte('0' + (byte % 10));                             /* Ones */
}

void UART_WriteWord(uint16_t word) {
	UART_transmitByte('0' + (word / 10000));                 /* Ten-thousands */
	UART_transmitByte('0' + ((word / 1000) % 10));               /* Thousands */
	UART_transmitByte('0' + ((word / 100) % 10));                 /* Hundreds */
	UART_transmitByte('0' + ((word / 10) % 10));                      /* Tens */
	UART_transmitByte('0' + (word % 10));                             /* Ones */
}
/*
void printBinaryByte(uint8_t byte) {
	// Prints out a byte as a series of 1's and 0's 
	uint8_t bit;
	for (bit = 7; bit < 255; bit--) {
		if (bit_is_set(byte, bit))
		transmitByte('1');
		else
		transmitByte('0');
	}
}
*/

char UART_nibbleToHexCharacter(uint8_t nibble) {
	/* Converts 4 bits into hexadecimal */
	if (nibble < 10) {
		return ('0' + nibble);
	}
	else {
		return ('A' + nibble - 10);
	}
}

void UART_WriteHexByte(uint8_t byte) {
	/* Prints a byte as its hexadecimal equivalent */
	uint8_t nibble;
	nibble = (byte & 0b11110000) >> 4;
	UART_transmitByte(UART_nibbleToHexCharacter(nibble));
	nibble = byte & 0b00001111;
	UART_transmitByte(UART_nibbleToHexCharacter(nibble));
}

uint8_t UART_getNumber(void) {
	// Gets a numerical 0-255 from the serial port.
	// Converts from string to number.
	char hundreds = '0';
	char tens = '0';
	char ones = '0';
	char thisChar = '0';
	do {                                                   /* shift over */
		hundreds = tens;
		tens = ones;
		ones = thisChar;
		thisChar = UART_receiveByte();                   /* get a new character */
		UART_transmitByte(thisChar);                                    /* echo */
		} while (thisChar != '\r');                     /* until type return */
		return (100 * (hundreds - '0') + 10 * (tens - '0') + ones - '0');
	}
