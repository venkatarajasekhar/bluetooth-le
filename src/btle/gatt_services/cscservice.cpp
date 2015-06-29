
#include "btle/gatt_services/cscservice.h"
#include "btle/gatt_services/gattserviceregisterer.h"

#include <cstring>
#include <stdio.h>
#include <string>
#include <sstream>
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
    service_ = uuid(CSC_SERVICE);
    mandatory_notifications_.push_back(uuid(CSC_MEASUREMENT));
    mandatory_notifications_.push_back(uuid(CSC_CONTOROL_POINT));
    included_characteristics_.push_back(uuid(CSC_MEASUREMENT));
    included_characteristics_.push_back(uuid(CSC_CONTOROL_POINT));
    // note wheel size is in millimeters
    max_wheel_time_ = (int)((wheel_size_*0.001*1*3.6)/CSC_MIN_SPEED_VALUE);
    speed_ = CSC_SPEED_UNINIT;
    cadence_ = CSC_CADENCE_UNINT;
    pending_operation_ = CSC_CS_NONE;
    completed_operation_ = CSC_CS_NONE;
}

void cscservice::process_service_notify_data(const uuid &chr, const uint8_t *data, size_t size)
{
    switch (chr.uuid16bit())
    {
        case CSC_MEASUREMENT:
        {
            int offset(1);
            memset(&flags_,0,sizeof(flags_));
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
            // TODO implement properly
            break;
        }
    default:
        break;
    }
}

void cscservice::process_service_value_read(const uuid& chr, const uint8_t* data, size_t size, const error& err)
{

}

void cscservice::reset()
{
    speed_ = CSC_SPEED_UNINIT;
    cadence_ = CSC_CADENCE_UNINT;
    curr_wheel_revs_ = 0;
    curr_crank_revs_ = 0;
    distance_ = 0;
    total_distance_ = 0;
    prev_wheel_event_ = 0;
    curr_wheel_event_ = 0;
    curr_crank_event_ = 0;
    prev_crank_event_ = 0;
    prev_wheel_revs_ = 0;
    prev_crank_revs_ = 0;
    exer_wheel_revs_ = 0;
    wheel_rounds_ = 0;
    wheel_event_  = 0;
    crank_event_  = 0;
}

std::string cscservice::json() const
{
    std::stringstream ss;
    ss << "{\n \"speedValue\", ";
    if( is_speed_present() ) ss << speed();
    ss << ",\n \"excerciseDistance\", ";
    if( is_speed_present() ) ss << distance();
    ss << ",\n \"totalDistance\", ";
    if( is_speed_present() ) ss << total_distance();
    ss << ",\n \"cadenceValue\", ";
    if( is_cadence_present() ) ss << cadence();
    
    return ss.str();
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
    }
    offset += 2;
    return offset;
}

/**
 * @brief cscservice::speed, in km/h
 * @return
 */
double cscservice::speed() const
{
    return speed_ != CSC_SPEED_UNINIT ? speed_ : 0;
}

/**
 * @brief cscservice::cadence, RPM
 * @return
 */
int cscservice::cadence() const
{
    return cadence_ != CSC_CADENCE_UNINT ? cadence_ : 0;
}

/**
 * @brief cscservice::distance, meters, current session/connection distance
 * @return
 */
double cscservice::distance() const
{
    return distance_;
}

/**
 * @brief cscservice::total_distance, sensors life time distance
 * @return
 */
double cscservice::total_distance() const
{
    return total_distance_;
}

bool cscservice::is_speed_present() const
{
    return flags_.wheel_revolutions_present_ != 0;
}

bool cscservice::is_cadence_present() const
{
    return flags_.cranck_revolutions_present_ != 0;
}

unsigned int cscservice::wheel_revolutions() const
{
    return curr_wheel_revs_;
}

unsigned int cscservice::cranck_revolutions() const
{
    return curr_crank_revs_;
}

csc_cs_operation cscservice::completed_operation() const
{
    return completed_operation_;
}
