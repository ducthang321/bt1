#include "stm32f4xx.h"                  // CMSIS core header file for STM32F4xx series
#include "stm32f4xx_ll_gpio.h"          // CMSIS LL GPIO header file
#include "stm32f4xx_ll_utils.h"         // CMSIS LL Utility header file

#define LED_PIN LL_GPIO_PIN_13          // GPIO pin connected to the LED (in this case, GPIO pin 13)

volatile uint32_t ticks = 0;            // Global variable to store SysTick ticks

void SysTick_Handler(void) {
    ticks++;                            // Increase the ticks count on each SysTick interrupt
}

void delay_ms(uint32_t ms) {
    uint32_t start = ticks;
    while ((ticks - start) < ms) {}     // Wait until the desired time has passed
}

int main(void) {
    // Initialize SysTick timer to interrupt every millisecond
    LL_InitTick(SystemCoreClock, 1000);

    // Enable GPIOC peripheral clock using LL
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

    // Configure GPIOC pin 13 as output using LL
    LL_GPIO_SetPinMode(GPIOC, LED_PIN, LL_GPIO_MODE_OUTPUT);

    while (1) {
        // Toggle the LED pin using LL
        LL_GPIO_TogglePin(GPIOC, LED_PIN);

        // Delay for 1 second
        delay_ms(1000);
    }
}
