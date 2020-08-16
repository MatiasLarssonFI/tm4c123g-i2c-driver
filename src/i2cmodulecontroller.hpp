#ifndef I2CMODULECONTROLLER_CXX
#define I2CMODULECONTROLLER_CXX

#include <functional>
#include <cstdint>

#include "tm4c_cmsis.h"
#include "i2cinterruptcontext.hpp"


//! I2C module controller
/*!
 * Implements the OO interface for an I2C module.
 * \tparam TModule The I2C module to control
 */
template <class TModule>
class I2CModuleController {
    public:
        using t_int_callback = std::function<void(I2CInterruptContext)>;
        
        //! Returns the singleton instance.
        static I2CModuleController<TModule>& instance() {
            static I2CModuleController<TModule> instance;
            return instance;
        }
        
        
        //! Initialize the peripheral and module
        void initSlave(uint8_t address, t_int_callback cb) noexcept {
            this->initCommon();
            // Enable the I2C slave
            HWREG(TModule::masterCfgRegAddr) |= masterCfgSlaveEnable;
            HWREG(TModule::slaveCtlStatusRegAddr) = 1U;
            // Set slave own address
            HWREG(TModule::slaveOwnAddrRegAddr) = address;
            // Enable the I2C slave data interrupt
            HWREG(TModule::slaveIntMaskRegAddr) |= slaveDataInterrupt;
            m_intCB = std::move(cb);
            m_isInitialized = true;
        }
        
        
        //! Reset the peripheral
        void resetPeripheral() const noexcept {
            // set reset bit
            SRI2C_REG |= TModule::sysCtlPeripheral;
            // short delay here
            for(std::uint_fast8_t delay = 0; delay < 16U; ++delay)
                ;
            // clear reset bit
            SRI2C_REG &= ~TModule::sysCtlPeripheral;
        }
        
        
        //! Interrupt handler
        void interrupt() const noexcept {
            if (m_isInitialized) {
                m_intCB(I2CInterruptContext{
                    HWREG(TModule::slaveCtlStatusRegAddr) & slaveStatusBits,
                    HWREG(TModule::slaveDataRegAddr) & slaveDataBits
                });
                HWREG(TModule::slaveIntClearRegAddr) = 1U; // clear the interrupt
            }
        }
        
        
        I2CModuleController(I2CModuleController const &) = delete;
        I2CModuleController& operator = (I2CModuleController const &) = delete;
        
        
        static constexpr std::uint_fast8_t slaveStatusFBR = 0x5U;
        static constexpr std::uint_fast8_t slaveStatusRREQ = 0x1U;
    private:
        I2CModuleController()
            : m_isInitialized(false)
            {}
        
        void initCommon() const noexcept {
            // system control: enable I2C module clock
            RCGCI2C_REG |= TModule::sysCtlPeripheral;
            // reset peripheral
            resetPeripheral();
            // system control: enable GPIO module clock
            RCGCGPIO_REG |= TModule::sysCtlGPIOPeripheral;
            // Select peripheral (i.e. I2C) function for the pins
            HWREG(TModule::gpioAFSelRegAddr) |= (TModule::gpioPortDataPin | TModule::gpioPortClockPin);
            // Enable data pin for open drain
            HWREG(TModule::gpioOpenDrainRegAddr) |= TModule::gpioPortDataPin;
            // Assing I2C signals to pins
            HWREG(TModule::gpioPortCtlRegAddr) |= TModule::gpioPortCtlMask;
            // Select digital enable for the pins
            HWREG(TModule::gpioDigitalEnableRegAddr) |= (TModule::gpioPortDataPin | TModule::gpioPortClockPin);
            // Enable the I2C NVIC interrupt
            HWREG(TModule::nvicIntEnableRegAddr) |= TModule::nvicIntEnableMask;
        }
        
        
        bool m_isInitialized;
        t_int_callback m_intCB;
        
        static constexpr std::uint_fast8_t masterCfgSlaveEnable = (1U << 5);
        static constexpr std::uint_fast8_t slaveDataInterrupt = 1U;
        static constexpr std::uint_fast8_t slaveStatusBits = 0xf;
        static constexpr std::uint_fast32_t slaveDataBits = 0xff;
};

#endif
