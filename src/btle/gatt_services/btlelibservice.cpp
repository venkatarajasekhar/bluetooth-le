
#include "btle/gatt_services/btlelibservice.h"
#include "btle/gatt_services/gattserviceregisterer.h"

#include <assert.h>
#include <sstream>

using namespace btle::gatt_services;

namespace {
    #if 0
    gattserviceregisterer<btlelibservice> registration;
    #endif
    
    enum transfer_status
    {
        idle,
        first_air_packet,
        streaming_in,
        streaming_out
    };
}

btlelibservice::btlelibservice()
: gattservicebase(),
  out_(),
  in_(),
  in_ctx_(),
  out_ctx_(),
  in_mutex_(),
  out_mutex_(),
  in_cond_(),
  out_cond_()
{
    service_ = uuid(BTLE_SERVICE);
    mandatory_notifications_.push_back(uuid(BTLE_MTU));
    included_characteristics_.push_back(uuid(BTLE_VERSION));
    included_characteristics_.push_back(uuid(BTLE_MTU));
}

void btlelibservice::process_service_notify_data(const uuid& chr, const uint8_t* data, size_t size)
{
    if( chr == BTLE_MTU )
    {
        /*switch(status_)
        {
            msg_payload payload = {0};
            memcpy(&payload, data, sizeof(payload));
            if( payload.more )
            {
                
            }
            else
            {
                // more = false, check all payload received
            }
        }*/
    }
}

void btlelibservice::process_service_value_read(const uuid& chr, const uint8_t* data, size_t size, const error& err)
{
    if( chr == BTLE_VERSION )
    {
        
    }
}

void btlelibservice::reset()
{
    
}

int btlelibservice::write_service_value(const uuid& chr, const std::string& data, device *dev, gattservicetx* tx)
{
    assert(chr == BTLE_MTU);

    out_mutex_.lock();
    out_.push_back(data);
    out_cond_.notify_all();
    out_mutex_.unlock();

    return 0;
}

void btlelibservice::packet_in(const std::string& data)
{
    in_mutex_.lock();
    in_.push_back(data);
    in_cond_.notify_all();
    in_mutex_.unlock();
}

std::string btlelibservice::take_last_message() const
{
    return "";
}

void btlelibservice::out_queue()
{
    do{
        std::unique_lock<std::mutex> lock(out_mutex_);
        out_cond_.wait(lock);
        if( out_.size() ){
            uint8_t rc(0);
            out_mutex_.lock();
            std::string message(out_.front());
            size_t total_size(message.size());
            out_.pop_front();
            out_mutex_.unlock();
            std::stringstream ss(message);
            // make first air packet
            first_air_packet sof = {0};
            sof.more = true;
            sof.first = true;
            sof.rc = rc++;
            sof.file_size = message.size();
            ss.read((char*)sof.payload[0],17);
            size_t count(ss.gcount());
            tx_->write_btle_ftp(*origin_,std::string((const char*)&sof,ss.gcount()+3));
            listener_->out_progress(origin_,0,(count/total_size)*100.0);
            if(!ss.eof())
            {
                do{
                    // ok to start pump packets
                    msg_payload payload={0};
                    payload.first = false;
                    payload.more = true;
                    payload.rc = rc == 0x10 ? rc=0 : rc++;
                    ss.read((char*)&payload.payload[0],19);
                    count += ss.gcount();
                    if(!ss.eof())
                    {
                        tx_->write_btle_ftp(*origin_,std::string((const char*)&payload,ss.gcount()+1));
                        listener_->out_progress(origin_,0,(count/total_size)*100.0);
                        if( rc == 0x0F )
                        {
                            // read ack
                        }
                    }
                    else
                    {
                        payload.more = false;
                        tx_->write_btle_ftp(*origin_,std::string((const char*)&payload,ss.gcount()+1));
                        listener_->out_progress(origin_,0,(count/total_size)*100.0);

                        // read ack
                        std::string ack;
                        if( int err = tx_->read_btle_ftp(*origin_,ack) )
                        {

                        }
                        break;
                    }
                }while(true);
            }
            else
            {
                // first and last packet
            }
        }
    }while (true);
}

void btlelibservice::in_queue()
{
    do{
        std::unique_lock<std::mutex> lock(in_mutex_);
        in_cond_.wait(lock);
        if(in_.size())
        {
            in_mutex_.lock();
            std::string packet=in_.front();
            in_.pop_front();
            in_mutex_.unlock();
            first_air_packet sof={0};
            memcpy(&sof,packet.c_str(),packet.size());
            assert(sof.first);
            if(sof.more)
            {

            }
            else
            {
                // first and last packet
            }
        }
    }while(true);
}

