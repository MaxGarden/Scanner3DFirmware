#pragma once

#include <assert.h>
#include <memory>

namespace Scanner3DFirmware
{
    using byte = unsigned char;
    
    #define FIRMWARE_ASSERT(expression) assert(expression)
}
