#include "i2c.h"

#define GPIO_B       		 (*((volatile unsigned long *) 0x40010C00))
#define RCC_APBENR       (*((volatile unsigned long *) 0x40021018))
#define  OUT50     3
#define O_AF_OD 3


Status I2C_Init( unsigned short speed_mode){
	
	volatile unsigned long * CR;
	unsigned short offset = 0x00;
	
	RCC->APB2ENR  |= 1;
	RCC->APB1ENR |= (1 << 21);

	RCC_APBENR |= 0x8;
	CR = (volatile unsigned long *)(&GPIO_B+ offset);
	
	*CR &= ~(0xf<<(6)*4);
	*CR |= ((OUT50<<(6*4)) | (O_AF_OD<<(6*4+2)));
	
	*CR &= ~(0xf<<(7)*4);
	*CR |= ((OUT50<<(7*4)) | (O_AF_OD<<(7*4+2)));
	
	// reset I2C
	I2C1->CR1 |= (1 << 15);
	I2C1->CR1 &= ~ (1 << 15);
	
	// set frequency // 0b1000
	I2C1->CR2 =0x8;
	I2C1->CCR = speed_mode;
	I2C1->CR1 |= 1;

	
	
	return Success;

	

}
Status I2C_Start(){
	
	I2C1->CR1 |= 0x100;
	while (!(I2C1->SR1 & (1 << 0))){};
	return Success;
}
Status I2C_Add(char address, char RW){

	volatile int tmp;
	I2C1->DR = (address|RW);
	while((I2C1->SR1 & (1 << 1))==0){};
	while((I2C1->SR1 & (1 << 1))){
		tmp = I2C1->SR1;
		tmp = I2C1->SR2;
		if((I2C1->SR1 & (1 << 1))==0)
		{
			break;
		}
	}
	
	return Success;
}
Status I2C_Data(char data){

	while((I2C1->SR1 & (1 << 7)) == 0){}
	I2C1->DR = data;
	while((I2C1->SR1 & (1 << 7)) == 0){}
	return Success;
}
Status I2C_Stop(){

	I2C1->CR1 |= (1 << 9);
	return Success;
}
Status I2C_Write(char address, char data[]){
	int i = 0;
	
	I2C_Start();
	
	I2C_Add(address,0);
	
	while(data[i]!='\0')
		{
			I2C_Data(data[i]);
			i++;
		}
	I2C_Stop();
	return Success;
}
