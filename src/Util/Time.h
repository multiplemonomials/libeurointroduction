
//NOTE: This file has been modified from a library written by Randall Smith

#ifndef TIME_H_
#define TIME_H_

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <chrono>

/*-----------------------------------------------------------------------------
    Very thin adaptor to bring the boost::posix_time stuff out in a more
    concise, convenient, and easy to remember form (and hopefully with a lot
    less time spent consulting the web site

        http://www.boost.org/doc/libs/1_54_0/doc/html/date_time/posix_time.html

    for particulars.)

    No intention to re-do anything; should be interchangeable and interoperable
    with the original Boost formulations.
 ----------------------------------------------------------------------------*/

struct Time
{
    /*-----------------------------------------------------------------------------
        Basic types.
     ----------------------------------------------------------------------------*/

    typedef boost::posix_time::ptime            Timepoint;

    typedef boost::posix_time::time_duration    Duration;

    typedef boost::posix_time::time_period      Period;


    /*-----------------------------------------------------------------------------
        Initialization.
     ----------------------------------------------------------------------------*/

    static Duration Hours(long const & val)
    {
        return boost::posix_time::hours(val);
    }

    static Duration Minutes(long const & val)
    {
        return boost::posix_time::minutes(val);
    }

    static Duration Seconds(long const & val)
    {
        return boost::posix_time::seconds(val);
    }

    static Duration Milliseconds(long const & val)
    {
        return boost::posix_time::milliseconds(val);
    }

    static Duration Microseconds(long const & val)
    {
        return boost::posix_time::microseconds(val);
    }


    /*-----------------------------------------------------------------------------
        Time of day.
     ----------------------------------------------------------------------------*/

    // Get time of day in GMT.
    static Timepoint GetTime()
    {
        return boost::posix_time::microsec_clock::universal_time();
    }

    // Get time of day in local timezone.
    static Timepoint GetLocalTime()
    {
        return boost::posix_time::microsec_clock::local_time();
    }


    /*-----------------------------------------------------------------------------
        Sleep.
     ----------------------------------------------------------------------------*/

    // Sleep current thread for specified duration.
    static void Sleep(Duration const & duration)
    {
        boost::this_thread::sleep(duration);
    }


    /*-----------------------------------------------------------------------------
        String conversion.
     ----------------------------------------------------------------------------*/

    // "Regular" strings.

    // To "2002-Jan-01 10:00:01.123456789"
    // Note:  Does not alpha sort properly!
    static std::string ToString(Timepoint const & timepoint)
    {
        return boost::posix_time::to_simple_string(timepoint);
    }

    // To "10:00:01.123456789"
    static std::string ToString(Duration const & duration)
    {
        return boost::posix_time::to_simple_string(duration);
    }

    // From "2002-01-20 23:59:59.000"
    static Timepoint TimepointFromString(std::string const & timepointAsString)
    {
        return boost::posix_time::time_from_string(timepointAsString);
    }

    // From "23:59:59.000"
    static Duration DurationFromString(std::string const & durationAsString)
    {
        return boost::posix_time::duration_from_string(durationAsString);
    }



    // ISO strings.

    // To "20020131T100001,123456789"
    static std::string ToIsoString(Timepoint const & timepoint)
    {
        return boost::posix_time::to_iso_string(timepoint);
    }

    // To "100001,123456789"
    static std::string ToIsoString(Duration const & duration)
    {
        return boost::posix_time::to_iso_string(duration);
    }

    // From "20020131T235959"
    static Timepoint FromIsoString(std::string const & timepointAsString)
    {
        return boost::posix_time::from_iso_string(timepointAsString);
    }



    // Extended ISO strings.

    // To "2002-01-31T10:00:01,123456789"
    static std::string ToIsoExtendedString(Timepoint const & timepoint)
    {
        return boost::posix_time::to_iso_extended_string(timepoint);
    }

    /*-----------------------------------------------------------------------------
        std::chrono conversion.
     ----------------------------------------------------------------------------*/

    //convert Time::Timepoint to std::chrono::time_point
    //accurate to the nanosecond
    inline static std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> TimepointToChrono(const boost::posix_time::ptime& from)
    {
        boost::posix_time::time_duration const time_since_epoch = from - boost::posix_time::from_time_t(0);
        std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> t = std::chrono::system_clock::from_time_t(time_since_epoch.total_seconds());
        long nsec = time_since_epoch.fractional_seconds() * (1000000000 / time_since_epoch.ticks_per_second());
        return t + std::chrono::nanoseconds(nsec);

    }

    template <class Clock, class Duration>
    inline static Timepoint ChronoToTimepoint(const std::chrono::time_point<Clock, Duration>& from)
    {
        typedef std::chrono::nanoseconds duration_t;
        typedef duration_t::rep rep_t;
        rep_t d = std::chrono::duration_cast<duration_t>(from.time_since_epoch()).count();
        rep_t sec = d/1000000000;
        rep_t nsec = d%1000000000;
        return boost::posix_time::from_time_t(0)+
        boost::posix_time::seconds(static_cast<long>(sec))+
        #ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
        boost::posix_time::nanoseconds(nsec);
        #else
        boost::posix_time::microseconds((nsec+500)/1000);
        #endif
    }
};

#endif /* TIME_H_ */
