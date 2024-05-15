#include "i2c.h"


Status i2c_init( unsigned short speed_mode){
	
	
	RCC->APB2ENR  |= 1;
	RCC->APB1ENR |= (1 << 21);
	
	gpio_init(PortB, 6, OUT_AF_OD, OUT50);
	gpio_init(PortB, 7, OUT_AF_OD, OUT50);

	// set frequency // 0b1000
	I2C1->CR2 =0x8;
	I2C1->CCR = speed_mode;
	I2C1->CR1 |= 1;
	
	return Success;

}
Status i2c_start(){
	
	I2C1->CR1 |= 0x100;
	while (!(I2C1->SR1 & (1 << 0))){};
	return Success;
}
Status i2c_add(char address, char RW){

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
Status i2c_data(char data){

	while((I2C1->SR1 & (1 << 7)) == 0){}
	I2C1->DR = data;
	while((I2C1->SR1 & (1 << 7)) == 0){}
	return Success;
}
Status i2c_stop(){

	I2C1->CR1 |= (1 << 9);
	return Success;
}
Status i2c_write(char address, char data[]){
	int i = 0;
	
	i2c_start();
	
	i2c_add(address,0);
	
	while(data[i]!='\0')
		{
			i2c_data(data[i]);
			i++;
		}
	i2c_stop();
	return Success;
}
