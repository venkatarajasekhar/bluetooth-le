
#include "btle/attributerequest.h"

using namespace btle;

attributerequest::attributerequest()
: base(),
  err_()
{
}

attributerequest::attributerequest(const std::string& value, const error& err)
: base(value),
  err_(err)
{
}

attributerequest::attributerequest(const attributerequest& other)
: base(other.string_value()),
  err_(other.err_)
{
}

const error& attributerequest::err() const
{
    return err_;
}
