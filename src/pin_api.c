#include "pin_api.h"

// Enable GPIO clock and return GPIO base address
uint32_t Set_GPIO_Clock(uint32_t port_idx)
{
    uint32_t gpio_add = 0;
    switch (port_idx) {
        case PortA:
            gpio_add = GPIOA_BASE;
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
            break;
        case PortB:
            gpio_add = GPIOB_BASE;
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
            break;
        case PortC:
            gpio_add = GPIOC_BASE;
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
            break;
        case PortD:
            gpio_add = GPIOD_BASE;
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
            break;
        default:
            error("Port number is not correct.");
            break;
    }
    return gpio_add;
}

void hal_pin_mode(PinName pin, PinMode mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    uint32_t port_index = STM_PORT(pin);
    uint32_t pin_index  = STM_PIN(pin);

    // Enable GPIO clock
    uint32_t gpio_add = Set_GPIO_Clock(port_index);
    GPIO_TypeDef *gpio = (GPIO_TypeDef *)gpio_add;

    // Configure open-drain and pull-up/down
    /*
    switch (mode) {
        case PullNone:
            return;
        case PullUp:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
            break;
        case PullDown:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
            break;
        case OpenDrain:
            if (pin_index < 8) {
                if ((gpio->CRL & (0x03 << (pin_index * 4))) > 0) { // MODE bits = Output mode
                    gpio->CRL |= (0x04 << (pin_index * 4)); // Set open-drain
                }
            } else {
                if ((gpio->CRH & (0x03 << ((pin_index % 8) * 4))) > 0) { // MODE bits = Output mode
                    gpio->CRH |= (0x04 << ((pin_index % 8) * 4)); // Set open-drain
                }
            }
            return;
        default:
            break;
    }

    // Configure GPIO
    GPIO_InitStructure.GPIO_Pin   = (uint16_t)(1 << pin_index);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(gpio, &GPIO_InitStructure);
    */
    switch(mode) 
    {
    case OUTPUT:
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      break;

    case INPUT:
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      break;

    case INPUT_PULLUP:
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
      break;

    case INPUT_PULLDOWN:
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
      break;

    case AF_OUTPUT_PUSHPULL:  //Used internally for Alternate Function Output Pushpull(TIM, UART, SPI etc)
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      break;

    case AF_OUTPUT_DRAIN:  //Used internally for Alternate Function Output Drain(I2C etc)
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      break;
    case AN_INPUT: // Used internally for ADC Input
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
      break;
    default:
      break;
    }

    // Configure GPIO
    GPIO_InitStructure.GPIO_Pin   = (uint16_t)(1 << pin_index);
    GPIO_Init(gpio, &GPIO_InitStructure);

}
