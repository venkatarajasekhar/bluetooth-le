#include "base.h"

using namespace btle;

base::base()
: value_(),
  description_()
{
}

base::base(const std::string& value)
: value_(value),
  description_()
{
}

base::base(
    const std::string& value,
    const std::string& description)
: value_(value),
  description_(description)
{
}

base::base(const base& other)
: value_(other.value_),
  description_(other.description_)
{
}

base::~base()
{
}

bool base::operator == (const base& other)
{
    return value_.compare(other.value_) != std::string::npos;
}

std::string base::to_string() const
{
    return value_;
}

int base::to_int(int base)
{
    return 0;
}

const std::string& base::string_value() const
{
    return value_;
}

const std::string& base::description() const
{
    return description_;
}

void base::set_string_value(const std::string& value)
{
    value_ = value;
}


