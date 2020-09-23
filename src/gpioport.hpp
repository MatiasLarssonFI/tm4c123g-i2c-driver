#ifndef GPIOPORT_CXX
#define GPIOPORT_CXX

#include <cstdint>

#include "bsp.h"
#include "i2ctypes.hpp"


/*
 * GPIO ports
 * 
 * Each GPIO port defines the parameter values such as bit positions
 * in registers for a single GPIO hardware port.
 */


//! GPIO port
/*!
 * \tparam PortNumber GPIO port number (a, b, c, d or f)
 */
template <std::uint_least8_t PortNumber>
class GPIOPort {};


//! GPIO Port A
template <>
class GPIOPort<0xA> {
    public:
        static constexpr t_register_addr AFSelRegAddr = GPIOAFSEL_PORTA;
        static constexpr t_register_addr openDrainRegAddr = GPIOODR_PORTA;
        static constexpr t_register_addr ctlRegAddr = GPIOPCTL_PORTA;
        static constexpr t_register_addr digitalEnableRegAddr = GPIODEN_PORTA;
        
        static constexpr std::uint_fast8_t sysCtlPeripheral = (1U << 0);
};

#endif
