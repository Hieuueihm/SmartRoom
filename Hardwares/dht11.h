#ifndef DHT11_H
#define DHT11_H
#include "stm32f10x.h"
#include <stdio.h>
#include "systick.h"
#include "gpio.h"

#define GPIOA_IDR_Addr    (0x40010808) //0x40010808 
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//Dia chi
#define GPIOA_ODR_Addr    (0x4001080C) //0x4001080C 
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //ngo ra
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //ngo vao
#define DHT11_IO_IN()  {GPIOA->CRL&=0XFFFFFFF0;GPIOA->CRL|=8<<0;}
#define DHT11_IO_OUT() {GPIOA->CRL&=0XFFFFFFF0;GPIOA->CRL|=3<<0;}
//IO										   
#define	DHT11_DQ_OUT PAout(0) 
#define	DHT11_DQ_IN  PAin(0) 


////////////////////////////////////////////////////////////////////////////////// 
//IO
//#define DHT11_IO_IN()  {GPIOA->CRH&=0XFFFFFFF0;GPIOA->CRH|=8<<0;}
//#define DHT11_IO_OUT() {GPIOA->CRH&=0XFFFFFFF0;GPIOA->CRH|=3<<0;}

//#define	DHT11_DQ_OUT PAout(8) 
//#define	DHT11_DQ_IN  PAin(8) 
 

u8 DHT11_Init(void);
u8 DHT11_Read_Data(u8 *temp,u8 *humi);
u8 DHT11_Read_Byte(void);
u8 DHT11_Read_Bit(void);
u8 DHT11_Check(void);
void DHT11_Rst(void);
	

#endif