#ifndef __BSP_H__
#define __BSP_H__

#define SYS_CLOCK_HZ 16000000U

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

#include "tm4c_cmsis.h"

#define HWREG(x) (*((volatile uint32_t *)(x)))

// I2C run mode clock gating control
#define RCGCI2C_REG HWREG(SYSCTL_BASE + 0x620U)

// I2C sw reset
#define SRI2C_REG HWREG(SYSCTL_BASE + 0x520U)

// GPIO run mode clock gating control
#define RCGCGPIO_REG HWREG(SYSCTL_BASE + 0x608U)

// Address of alternate function select register for GPIO port A
#define GPIOAFSEL_PORTA (GPIO_PORTA_BASE + 0x420U)

// Address of open drain select register for GPIO port A
#define GPIOODR_PORTA (GPIO_PORTA_BASE + 0x50CU)

// Address of digital enable for GPIO port A
#define GPIODEN_PORTA (GPIO_PORTA_BASE + 0x51CU)

// Address of port control for GPIO port A
#define GPIOPCTL_PORTA (GPIO_PORTA_BASE + 0x52CU)

// Address of I2C1 master configuration register
#define I2C1_MCR (I2C1_MASTER_BASE + 0x20U)

// Address of I2C1 slave control/status register
#define I2C1_SLAVE_SCSR (I2C1_SLAVE_BASE + 4U)

// Address of I2C1 slave data register
#define I2C1_SLAVE_DATA (I2C1_SLAVE_BASE + 8U)

// Address of I2C1 slave interrupt mask register
#define I2C1_SLAVE_IM (I2C1_SLAVE_BASE + 0xCU)

// Address of I2C1 slave interrupt clear register
#define I2C1_SLAVE_SICR (I2C1_SLAVE_BASE + 0x18U)

// Address of I2C1 NVIC interrupt enable register
#define I2C1_NVIC_INT_ENABLE_R (0xE000E104) // interrupt 37

#endif // __BSP_H__
