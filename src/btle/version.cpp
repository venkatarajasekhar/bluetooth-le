
#include "btle/version.h"

using namespace btle;

namespace {
    #define MAJOR 0
    #define MINOR 0

}

/**
 * @brief version::version_string, this will be implemented later, requires scripts to be run before build
 * @return version string in format MAJOR.MINOR.PATCH ex 1.1.1
 */
const std::string& version::version_string()
{
    static std::string version_str = "0.0.0";
    return version_str;
}

/**
 * @brief version::version_number
 * @return version in integer format
 */
unsigned int version::version_number()
{
    return 0;
}


