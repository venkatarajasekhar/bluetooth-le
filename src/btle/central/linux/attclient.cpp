
#include "btle/central/linux/attclient.h"

#include <cstring>

using namespace btle;
using namespace btle::central;
using namespace btle::central::linux_platform;

attclient::attclient()
{
}

void attclient::read_by_group_type(uint16_t start, uint16_t end)
{
    uint8_t packet[6];
    std::memcpy(&packet[0],&start,sizeof(start));
    std::memcpy(&packet[2],&end,sizeof(end));
    std::memcpy(&packet[4],"2800",sizeof(end)); // primary service

}

void attclient::request(int opcode, std::string& data)
{
}
