/*
 * uart.h
 *
 * Created: 23-03-2023 11:11:52
 *  Author: sumit.chatterjee
 */ 


#ifndef UART_H_
#define UART_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define Baud
#define BaudRate(Baud) (((F_CPU /(Baud * 16UL)))-1)


void UART_init(unsigned int ubrr);          /* Define a BaudRate to Initialize the UART */
unsigned char UART_recieve();               /* UART CHAR Receiver Function */
void UART_transmit(unsigned char data);     /* UART  unsigned CHAR Transmitter Function */
char Read_char();                           /* UART CHAR Read Function */
void Write_char(char val);                  /* UART CHAR Transmitter Function */
unsigned char UART_Available(void);         /* Check UART RECEIVED ANY DATA Function */
void WriteString(char *s);                  /* UART String Transmitter Function */
void Write_String(char* StringPtr);         /* UART String Transmitter Function */
void Write_Negative_dec16(int16_t val);     /* UART Negative Decimal 16bit Transmitter Function */
void Write_dec16(uint16_t val);             /* UART Decimal Transmitter 16bit Function */
void Write_Negative_dec8(int8_t val);       /* UART Negative Decimal 8bit Function */
void Write_dec8(uint8_t val);               /* UART Decimal 8bit Function */
signed int DOR_error();                     /* DataOverRun Error*/
signed int Frame_error();                   /* Frame Error*/
signed int Parity_error();                  /* Parity Error*/
void UART_transmitByte(uint8_t data);       /* transmit buffer */
uint8_t UART_receiveByte(void);             /* incoming data */
void UART_WrtiteString(const char myString[]); /* Write String Data */
void UART_WriteByte(uint8_t byte);           /* Prints a byte out as its 3-digit ascii equivalent */
void UART_WriteWord(uint16_t word);         /* Prints a word (16-bits) out as its 5-digit ascii equivalent */
//void UART_WriteBinaryByte(uint8_t byte);    /* Prints a byte out in 1s and 0s */
char UART_nibbleToHex(uint8_t nibble);
char UART_nibbleToHexCharacter(uint8_t nibble);
void UART_WriteHexByte(uint8_t byte);            /* Prints a byte out in hexadecimal */
uint8_t UART_getNumber(void);
int Readline_getSize (char * s);
int Read_getSize (char * s);
int toString(char a[]);
int StringtoInt(const char *s);



#endif /* UART_H_ */