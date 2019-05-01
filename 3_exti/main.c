#include <stdint.h>
#include "reg.h"
#include "blink.h"

int main(void)
{
	//RCC Enable GPIOA
	SET_BIT(RCC_BASE+RCC_AHB1ENR_OFFSET,0);

	//GPIO Configurations
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA)+GPIOx_MODER_OFFSET,MODERy_1_BIT(0));
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA)+GPIOx_MODER_OFFSET,MODERy_0_BIT(0));
	//RCC Enable SYSCFG
	SET_BIT(RCC_BASE+RCC_AHB2ENR_OFFSET,SYSCFGEN_BIT);

	//SYSCFG Configurations
	WRITE_BITS(SYSCFG_BASE+SYSCFG_EXTICR1_OFFSET,EXT10_3_BIT,EXI0_0_BIT,0);

	//EXTI Configurations
	SET_BIT(EXT1_BASE+EXT1_IMR_OFFSET,0);
	SET_BIT(EXT1_BASE+EXT1_RTSR_OFFSET,0);

	//NVIC Configurations
	SET_BIT(NVIC_ISER_BASE + NVIC_ISERn_OFFSET(0), 6); //IRQ6

	blink(LED_BLUE);
}

void exti0_handler(void)
{
	blink_count(LED_ORANGE, 10);

	//clear pending
	SET_BIT(EXTI_BASE + EXTI_PR_OFFSET, 0);
}
