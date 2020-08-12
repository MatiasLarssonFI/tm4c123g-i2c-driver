#ifndef I2CINTERRUPTCONTEXT_CXX
#define I2CINTERRUPTCONTEXT_CXX

#include <cstdint>

struct I2CInterruptContext {
    const std::uint_fast32_t slaveStatus;
    const std::uint_fast32_t slaveData;
};

#endif
