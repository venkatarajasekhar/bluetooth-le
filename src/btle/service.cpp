
#include "btle/service.h"

using namespace btle;

service::service()
: base(),
  uuid_(),
  characteristics_(),
  start_handle_(0),
  end_handle_(0)

{
}

service::service(const btle::uuid& uid)
: base(),
  uuid_(uid),
  characteristics_(),
  start_handle_(0),
  end_handle_(0)
{
}

service::service(
    const btle::uuid& uid,
    long int instance_id)
: base(),
  uuid_(uid),
  characteristics_(),
  start_handle_(0),
  end_handle_(0),
  instance_id_(instance_id)
{
}

service::service(
    const btle::uuid& uid,
    uint16_t start_handle,
    uint16_t end_handle)
: base(),
  uuid_(uid),
  characteristics_(),
  start_handle_(start_handle),
  end_handle_(end_handle)
{
}

service::service(const service& other)
: base(other),
  uuid_(other.uuid_),
  characteristics_(other.characteristics_),
  start_handle_(other.start_handle_),
  end_handle_(other.end_handle_),
  instance_id_(other.instance_id_)
{
}

service& service::operator << (const characteristic& chr)
{
    for( chr_iterator it = characteristics_.begin(); it != characteristics_.end(); ++it )
    {
        if( (*it) == chr )
        {
            return *this;
        }
    }
    characteristics_.push_back(chr);
    return *this;
}

service& service::operator << (const std::vector<characteristic>& chrs)
{
    if( characteristics_.size() == 0 )
        characteristics_ = chrs;
    return *this;
}

bool service::operator == (const btle::uuid& uid) const
{
    return uuid_ == uid;
}

bool service::operator == (const service& other) const
{
    return uuid_         == other.uuid() &&
           start_handle_ == other.start_handle() &&
           end_handle_   == other.end_handle();
}

const characteristic& service::operator [](int index) const
{
    return characteristics_[index];
}

const std::vector<characteristic>& service::characteristics() const
{
    return characteristics_;
}

std::vector<characteristic>& service::characteristics()
{
    return characteristics_;
}

const btle::uuid& service::uuid() const
{
    return uuid_;
}

uint16_t service::start_handle() const
{
    return start_handle_;
}

uint16_t service::end_handle() const
{
    return end_handle_;
}

long int service::instance_id() const
{
    return instance_id_;
}

std::string service::to_string() const
{
    return uuid_.to_string();
}

void service::invalidate()
{
    characteristics_.clear();
    start_handle_ = 0;
    end_handle_ = 0;
}
