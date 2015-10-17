/*
 * Program to control USER LEDs of BeagleBoard xm rev. C
 * Taras Zakharchenko 
 * taras.zakharchenko@gmail.com
 */
#include <common.h>
#include <exports.h>

#define GPIO_BASE 0x49056000
#define GPIO_OE (GPIO_BASE + 0x34)
#define GPIO_DIN (GPIO_BASE + 0x38)
#define GPIO_DOUT (GPIO_BASE + 0x3C)
#define LED1 0x00400000 //GPIO150
#define LED2 0x00200000 //GPIO149

volatile unsigned int *gpio_din = (unsigned int *)GPIO_DIN;
volatile unsigned int *gpio_dout = (unsigned int *)GPIO_DOUT;
volatile unsigned int *gpio_oe = (unsigned int *)GPIO_OE;

#define SET_BIT(reg,mask) \
do {\
	*reg |= mask;\
} while(0);

#define CLR_BIT(reg,mask) \
do {\
	*reg &= ~mask;\
} while(0);

#define RD_BIT(reg,mask) (*reg & mask)


int toggle_led(int argc, char * const argv[])
{
	app_startup(argv);
	printf("Toggling led\n");
	printf("LED1 OE %u\n", RD_BIT(gpio_oe, LED1)?1:0);
	if(RD_BIT(gpio_oe, LED1)) {
		CLR_BIT(gpio_oe, LED1);
	}
	printf("LED2 OE %d\n", RD_BIT(gpio_oe, LED2)?1:0);
	if(RD_BIT(gpio_oe, LED2)) {
		CLR_BIT(gpio_oe, LED2);
	}

	printf("LED1 OUT %u\n", RD_BIT(gpio_dout, LED1)?1:0);
	if(RD_BIT(gpio_dout, LED1)) {
		printf("Turning off LED1\n");
		CLR_BIT(gpio_dout, LED1);
	}
	else {
		printf("Turning on LED1\n");
		SET_BIT(gpio_dout, LED1);
	}
	
	printf("LED2 OUT %u\n", RD_BIT(gpio_dout, LED2)?1:0);
	if(RD_BIT(gpio_dout, LED2)) {
		printf("Turning off LED2\n");
		CLR_BIT(gpio_dout, LED2);
	}
	else {
		printf("Turning on LED2\n");
		SET_BIT(gpio_dout, LED2);
	}
	return (0);
}
