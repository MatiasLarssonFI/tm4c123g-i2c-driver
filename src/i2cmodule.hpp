#ifndef I2CMODULE_CXX
#define I2CMODULE_CXX

#include <cstdint>

#include "bsp.h"
#include "i2cmodulecontroller.hpp"


/*
 * I2C Modules
 * 
 * Each I2C module defines the parameter values such as bit positions
 * in registers for a single I2C hardware module. It also exposes an
 * interface to interact with the module.
 */


//! I2C module
/*!
 * \tparam ModuleNumber I2C module number (0-n where n is the greatest possible I2C module number)
 */
template <uint8_t ModuleNumber>
class I2CModule {};


//! I2C module 1, GPIO Port A, pins 6 (clock) and 7 (data)
template <>
class I2CModule<1> {
    public:
        I2CModule()
            : m_cntl(t_cntl::instance())
            {}
        
        static constexpr std::uint_fast32_t slaveStatusFBR = I2CModuleController<I2CModule<1>>::slaveStatusFBR;
        static constexpr std::uint_fast32_t slaveStatusRREQ = I2CModuleController<I2CModule<1>>::slaveStatusRREQ;
            
        //! Initialize the perihperal and module
        void initSlave(uint8_t address, I2CModuleController<I2CModule<1>>::t_int_callback cb) noexcept {
            m_cntl.initSlave(address, std::move(cb));
        }
        
        //! Reset the peripheral
        void reset() const noexcept { m_cntl.resetPeripheral(); }
        
        //! Interrupt handler
        void interrupt() const noexcept { m_cntl.interrupt(); };
        
        static constexpr std::uint_fast8_t sysCtlPeripheral = (1U << 1);
        static constexpr std::uint_fast8_t sysCtlGPIOPeripheral = (1U << 0);
        
        static constexpr std::uint_fast32_t slaveOwnAddrRegAddr = I2C1_SLAVE_BASE;
        static constexpr std::uint_fast32_t slaveCtlStatusRegAddr = I2C1_SLAVE_SCSR;
        static constexpr std::uint_fast32_t slaveDataRegAddr = I2C1_SLAVE_DATA;
        static constexpr std::uint_fast32_t slaveIntMaskRegAddr = I2C1_SLAVE_IM;
        static constexpr std::uint_fast32_t slaveIntClearRegAddr = I2C1_SLAVE_SICR;
        
        static constexpr std::uint_fast32_t gpioAFSelRegAddr = GPIOAFSEL_PORTA;
        static constexpr std::uint_fast32_t gpioOpenDrainRegAddr = GPIOODR_PORTA;
        static constexpr std::uint_fast32_t gpioPortCtlRegAddr = GPIOPCTL_PORTA;
        static constexpr std::uint_fast32_t gpioDigitalEnableRegAddr = GPIODEN_PORTA;
        static constexpr std::uint_fast32_t masterCfgRegAddr = I2C1_MCR;
        static constexpr std::uint_fast32_t nvicIntEnableRegAddr = I2C1_NVIC_INT_ENABLE_R;
        
        static constexpr std::uint_fast8_t gpioPortDataPin = (1U << 7);
        static constexpr std::uint_fast8_t gpioPortClockPin = (1U << 6);
        static constexpr std::uint_fast32_t gpioPortCtlMask = (3U << 28) | (3U << 24);
        static constexpr std::uint_fast8_t nvicIntEnableMask = (1U << 5); // interrupt 37
        
    private:
        using t_cntl = I2CModuleController<I2CModule<1>>;
        
        t_cntl & m_cntl;
};

#endif