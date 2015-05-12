
#include "btle/smpkeys.h"
#include <cstring>

using namespace btle;

smpkeys::smpkeys()
: base()
{
}

smpkeys::smpkeys(
    uint16_t ldiversifier,
    uint8_t  lrandom[SMP_LRANDOM_LEN],
    uint8_t  ltk[SMP_LTK_LEN])
: base(),
  ldiversifier_(ldiversifier)
{
    memcpy(lrandom_,lrandom,SMP_LRANDOM_LEN);
    memcpy(ltk_,ltk,SMP_LTK_LEN);
}

smpkeys::smpkeys(const smpkeys& other)
: base(other),
  ldiversifier_(other.ldiversifier_)
{
    memcpy(lrandom_,other.lrandom_,SMP_LRANDOM_LEN);
    memcpy(ltk_,other.ltk_,SMP_LTK_LEN);
}
