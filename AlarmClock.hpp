#ifndef ALARMCLOCK
#define ALARMCLOCK

#include <windows.h>
#include <chrono>

class AlarmClock
{
    private:
    unsigned Error;

    public:
    AlarmClock()
    {
        Error = 0;
    }

    void __fastcall SleepUs(unsigned Microseconds)
    {
        using namespace std::chrono;

        if(Error >= Microseconds)
        {
            Error -= Microseconds;
            return;
        }

        time_point<high_resolution_clock, microseconds> DueTime =
        time_point_cast<microseconds>(high_resolution_clock::now() + (microseconds)(Microseconds - Error));

        if(DueTime.time_since_epoch().count() > 2000)
        {
            timeBeginPeriod(1);
            Sleep((DueTime.time_since_epoch() / 1000).count() - 1);
            timeEndPeriod(1);
        }

        while(DueTime > time_point_cast<microseconds>(high_resolution_clock::now()))
        {
            continue;
        }
        Error = (time_point_cast<microseconds>(high_resolution_clock::now()) - DueTime).count();
    }

    void __fastcall operator() (int Microseconds)
    {
        return SleepUs(Microseconds);
    }

    void Reset()
    {
        Error = 0;
    }
};

#endif