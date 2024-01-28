#include "stm32f4xx.h"  // Thư viện CMSIS cho STM32F4
#include "main.h"
// Định nghĩa GPIO cho LED
#define LED_PIN GPIO_PIN_13
#define LED_PORT GPIOC

// Khai báo biến đếm thời gian
volatile uint32_t ticks = 0;

// Khởi tạo hàm delay sử dụng SysTick timer
void delay(uint32_t ms) {
    uint32_t start = ticks;
    while ((ticks - start) < ms);
}

// Hàm chính
int main(void) {
    // Khởi tạo cấu hình cho SysTick timer
    SysTick_Config(SystemCoreClock / 1000); // Tạo ngắt mỗi 1ms

    // Khởi tạo cấu hình cho GPIO
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // Bật clock cho GPIOC
    GPIOC->MODER |= GPIO_MODER_MODER13_0; // Cấu hình PC13 là output

    while (1) {
        // Bật LED
        GPIOC->BSRR = LED_PIN;
        // Đợi 1 giây
        delay(1000);
        // Tắt LED
        GPIOC->BSRR = LED_PIN << 16;
        // Đợi 1 giây
        delay(1000);
    }
}

void HAL_IncTick(void)
{
	ticks++;
}
