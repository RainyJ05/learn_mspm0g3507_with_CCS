#include "ti_msp_dl_config.h"

volatile unsigned int delay_times = 0;

//搭配滴答定时器实现的精确ms延时
void delay_ms(unsigned int ms)
{
    delay_times = ms;
    while( delay_times != 0 );
}

int main(void)
{
    SYSCFG_DL_init();

    while (1)
    {
            //如果读取到的引脚值大于0，说明PA18引脚为高电平
            if( DL_GPIO_readPins(KEY_PORT, KEY_PIN_18_PIN) > 0 )
            {
                DL_GPIO_setPins(LED1_PORT,LED1_PIN_14_PIN);  //LED控制输出高电平
            }
            else//如果PA18引脚为低电平
            {
                DL_GPIO_clearPins(LED1_PORT,LED1_PIN_14_PIN);//LED控制输出低电平
            }

    }
}

//滴答定时器中断服务函数
void SysTick_Handler(void)
{
    if( delay_times != 0 )
    {
        delay_times--;
    }
}