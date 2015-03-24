
#include "btle/utility.h"
#include <sstream>
#include <iomanip>

using namespace btle;

std::string utility::to_string(int value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

std::string utility::to_string(unsigned int value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

std::string utility::to_string(double value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

std::string utility::to_hex_string(const uint8_t* data, size_t size, char separator)
{
    std::stringstream ss_hex;
    for( unsigned int i=0; i < size; ++i )
    {
        ss_hex << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)(unsigned char)*(data+i) << separator;
    }
    return ss_hex.str();
}

std::string utility::to_hex_string(const std::string& data, char separator)
{
    return to_hex_string((const uint8_t*)data.c_str(),data.size(),separator);
}

int utility::to_int(const std::string& data)
{
    std::stringstream ss;
    ss << data;
    int value(0);
    ss >> value;
    return value;
}

unsigned int utility::to_uint(const std::string& data)
{
    std::stringstream ss;
    ss << data;
    unsigned int value(0);
    ss >> value;
    return value;
}


