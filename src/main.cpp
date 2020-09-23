#include <cstdint>
#include <cstdbool>

#include "bsp.h"
#include "tm4c_cmsis.h"
#include "i2cmodule.hpp"

using I2CModule1 = I2CModule<1U>;

I2CModule1 i2cModule1{};

int main() {
    SYSCTL->RCGC2 |= (1U << 5); // enable clock for GPIOF
    SYSCTL->GPIOHSCTL |= (1U << 5); // enable AHB for GPIOF
    
    GPIOF_HS->DIR |= (LED_RED | LED_BLUE | LED_GREEN); // set led pins as outputs
    GPIOF_HS->DEN |= (LED_RED | LED_BLUE | LED_GREEN); // digital enable
    
    i2cModule1.initSlave(0x60U, [] (I2CInterruptContext ctx) {
        if (ctx.slaveStatus == I2CModule1::slaveStatusRREQ) {
            if (ctx.slaveData > 0U && ctx.slaveData < 4U) {
                // toggle requested LED
                const std::uint_fast8_t led = (1U << ctx.slaveData);
                GPIOF_HS->DATA_Bits[led] ^= led;
            }
        }
    });
    
    while (1)
        ;
    //return 0;
}
