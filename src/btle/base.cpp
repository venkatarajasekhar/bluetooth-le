#include "base.h"

btle::base::base()
: _value(),
  _description()
{
}

btle::base::base(
    const std::string& value,
    const std::string& description)
: _value(value),
  _description(description)
{
}

btle::base::base(const base& other)
: _value(other._value),
  _description(other._description)
{
}

btle::base::~base()
{
}

bool btle::base::operator == (const btle::base& other)
{
    return _value.compare(other._value) != std::string::npos;
}

std::string btle::base::to_string() const
{
    return _value;
}

int btle::base::to_int(int base)
{
    return 0;
}

const std::string& btle::base::string_value() const
{
    return _value;
}

const std::string& btle::base::description() const
{
    return _description;
}

