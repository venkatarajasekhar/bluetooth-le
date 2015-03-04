
#include "btle/gatt_services/cscservice.h"
#include "btle/gatt_services/gattserviceregisterer.h"

#include <stdio.h>
#include <string>
#include <time.h>

using namespace btle::gatt_services;

namespace {
    gattserviceregisterer<cscservice> registration;
}

cscservice::cscservice()
: wheel_size_(2000),
  curr_wheel_revs_(0),
  curr_crank_revs_(0),
  distance_(0),
  total_distance_(0),
  prev_wheel_event_(0),
  curr_wheel_event_(0),
  curr_crank_event_(0),
  prev_crank_event_(0),
  prev_wheel_revs_(0),
  prev_crank_revs_(0),
  exer_wheel_revs_(0),
  wheel_rounds_(0),
  wheel_event_(0),
  crank_event_(0),
  speed_(0),
  cadence_(0)
{
    service_ = CSC_SERVICE;
    mandatory_notifications_.push_back(CSC_MEASUREMENT);
    mandatory_notifications_.push_back(CSC_CONTOROL_POINT);
    max_wheel_time_ = (int)((wheel_size_*0.001*1*3.6)/CSC_MIN_SPEED_VALUE);
    speed_ = CSC_SPEED_UNINIT;
    cadence_ = CSC_CADENCE_UNINT;
    pending_operation_ = CSC_CS_NONE;
    completed_operation_ = CSC_CS_NONE;
}

void cscservice::process_service_data(const uuid &chr, const uint8_t *data, size_t size)
{
    switch (chr.uuid16bit())
    {
        case CSC_MEASUREMENT:
        {
            int offset(1);
            //memset(&csc_flags_,0,sizeof(csc_flags_));
            memcpy(&flags_,data,sizeof(flags_));
            if( flags_.wheel_revolutions_present_ )
            {
                offset += process_speed_measurement( (data+offset), 0 );
            }
            if( flags_.cranck_revolutions_present_ )
            {
                offset += process_cadence_measurement( (data+offset), 0 );
            }
            break;
        }
        case CSC_CONTOROL_POINT:
        {
            pending_operation_ = CSC_CS_NONE;
            if( *(data + 2) == 0x01 ) // OK
            {
                completed_operation_ = (csc_cs_operation)*(data+1);
            }
            else // FAIL
            {
                // save error code
                completed_operation_ = CSC_CS_FAILED;
            }
            break;
        }
    default:
        break;
    }
}

int cscservice::process_speed_measurement(const uint8_t* msg, int offset)
{
    time_t abs_time = time(NULL);
    prev_wheel_revs_ = curr_wheel_revs_;
    memcpy(&curr_wheel_revs_,(msg+offset),4);
    offset += 4;
    prev_wheel_event_ = curr_wheel_event_;
    uint16_t tmp_curr_wheel_event_(0);
    memcpy(&tmp_curr_wheel_event_,msg+offset,sizeof(tmp_curr_wheel_event_));
    curr_wheel_event_ = (double)tmp_curr_wheel_event_/1024.0;

    if( speed_ == CSC_SPEED_UNINIT )
    {
        speed_ = 0;
        wheel_event_  = abs_time;
    }
    else
    {
        double event_diff = curr_wheel_event_;

        if( prev_wheel_event_ )
        {
            if( prev_wheel_event_ <= curr_wheel_event_ )
                event_diff = curr_wheel_event_ - prev_wheel_event_;
            else
            {
                // rollover
                event_diff = curr_wheel_event_ + ( ((double)0xFFFF/1024.0) - prev_wheel_event_);
            }
        }

        unsigned int wheel_rounds = curr_wheel_revs_ - prev_wheel_revs_;

        if( curr_wheel_revs_ < prev_wheel_revs_ )
        {
            prev_wheel_revs_ = curr_wheel_revs_;
            wheel_rounds = 0;
        }

        if( wheel_rounds > 0 )
        {
            wheel_rounds_ = wheel_rounds;
        }

        exer_wheel_revs_ += wheel_rounds;

        double speed = 0;

        if( (!event_diff || !wheel_rounds) && (abs_time-wheel_event_) < max_wheel_time_ )
        {
            speed = speed_;
            exer_wheel_revs_ += wheel_rounds_;
        }
        if( event_diff && wheel_rounds )
        {
            speed = ((((double)wheel_size_*0.001)*wheel_rounds)/event_diff)*3.6;
            wheel_event_ = abs_time;
        }

        speed_ = speed;
        distance_ = ((double)wheel_size_*0.001)*exer_wheel_revs_;
        total_distance_ = ((double)wheel_size_*0.001)*curr_wheel_revs_;
    }

    offset += 2;

    return offset;
}

int cscservice::process_cadence_measurement(const uint8_t *msg, int offset)
{
    time_t abs_time = time(NULL);
    prev_crank_revs_ = curr_crank_revs_;
    memcpy(&curr_crank_revs_,msg+offset,2);
    offset += 2;

    int crank_rounds = curr_crank_revs_ - prev_crank_revs_;

    if( curr_crank_revs_ < prev_crank_revs_ )
    {
        prev_crank_revs_ = (0xFFFF - prev_crank_revs_);
        crank_rounds = curr_crank_revs_ - prev_crank_revs_;
    }

    prev_crank_event_ = curr_crank_event_;

    uint16_t tmp_curr_crank_event_(0);
    memcpy(&tmp_curr_crank_event_,msg+offset,sizeof(tmp_curr_crank_event_));
    curr_crank_event_ = (double)tmp_curr_crank_event_/1024.0;
    if( cadence_ == CSC_CADENCE_UNINT )
    {
        crank_event_ = abs_time;
        cadence_ = 0;
        offset += 2;
    }
    else
    {
        double event_diff = curr_crank_event_;

        if( prev_crank_event_ )
        {
            if( prev_crank_event_ <= curr_crank_event_ )
                event_diff = curr_crank_event_ - prev_crank_event_;
            else
            {
                event_diff = curr_crank_event_ + ( ((double)0xFFFF/1024.0) - prev_crank_event_);
            }
        }

        if( (!event_diff || !crank_rounds) && (abs_time-crank_event_) < CSC_MAX_CEVENT_TIME )
        {
            // do nothing
        }
        else if( event_diff && crank_rounds )
        {
            cadence_ = (int)((crank_rounds/event_diff)*60.0);
            crank_event_ = abs_time;
        }
        else
        {
            cadence_ = 0;
        }

        offset += 2;
    }

    return offset;
}

double cscservice::speed()
{
    return speed_;
}

int cscservice::cadence()
{
    return cadence_;
}

double cscservice::distance()
{
    return distance_;
}

double cscservice::total_distance()
{
    return total_distance_;
}

bool cscservice::is_speed_present()
{
    return flags_.wheel_revolutions_present_ != 0;
}

bool cscservice::is_cadence_present()
{
    return flags_.cranck_revolutions_present_ != 0;
}

unsigned int cscservice::wheel_revolutions()
{
    return curr_wheel_revs_;
}

unsigned int cscservice::cranck_revolutions()
{
    return curr_crank_revs_;
}

csc_cs_operation cscservice::completed_operation()
{
    return completed_operation_;
}
