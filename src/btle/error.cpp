
#include "btle/error.h"

using namespace btle;

error::error()
: base()
{
}

error::error(const error& other)
: base(other)
{
}

error::error(int code)
: base(),
  code_(code)
{
}

error::error(int code,const std::string& description)
: base("",description),
  code_(code)
{
}

int error::code() const
{
    return code_;
}

bool error::operator == (const error& other) const
{
    return this->code_ == other.code();
}


