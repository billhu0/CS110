#include <stdio.h>
#include <string.h>

#include "lcd/lcd.h"

void Inp_init(void) {
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
}

void Adc_init(void) {
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1);
    RCU_CFG0 |= (0b10 << 14) | (1 << 28);
    rcu_periph_clock_enable(RCU_ADC0);
    ADC_CTL1(ADC0) |= ADC_CTL1_ADCON;
}

void IO_init(void) {
    Inp_init();  // inport init
    Adc_init();  // A/D init
    Lcd_Init();  // LCD init
}

int Get_Button(int ch) {
    ADC_RSQ2(ADC0) = 0;
    ADC_RSQ2(ADC0) = ch;
    ADC_CTL1(ADC0) |= ADC_CTL1_ADCON;
    while (!(ADC_STAT(ADC0) & ADC_STAT_EOC))
        ;
    uint16_t ret = ADC_RDATA(ADC0) & 0xFFFF;
    ADC_STAT(ADC0) &= ~ADC_STAT_EOC;
    return (ret == 4095);
}

int Get_BOOT0(void) { return (int)(gpio_input_bit_get(GPIOA, GPIO_PIN_8)); }

int add_function(int, int, int);  // implemented in risc-v
void draw();                      // implemented in risc-v

int main(void) {
    IO_init();  // init OLED
    LCD_Clear(BLACK);
    BACK_COLOR = BLACK;

    int a = add_function(3, 4, 5);  // call risc-v function in C
    LCD_ShowNum(0, 0, a, 3, WHITE);

    LCD_ShowString(0, 16, (u8 *)("Hello World! Line 2"), BLUE);
    LCD_ShowString(0, 32, (u8 *)("Hello World! Line 3"), BRED);  // purple
    LCD_ShowString(0, 48, (u8 *)("Hello World! Line 4"), GBLUE);  // cyan
    LCD_ShowString(0, 64, (u8 *)("Hello World! Line 5"), RED);  // real red

    while (!Get_BOOT0()) {
        delay_1ms(50);
        if (Get_BOOT0()) break;
    }

    LCD_Clear(BLACK);
    draw();   // call risc-v function
    
    return 0;
}
