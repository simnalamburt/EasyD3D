#include "pch.h"
#include "Stopwatch.h"
#include "PerformanceCounter.h"



const llong Stopwatch::CountPerSecond = QueryPerformanceFrequency();

Stopwatch::Stopwatch(StopwatchStatus Status)
{
    countStarted = countLastTick = QueryPerformanceCounter();
    countPaused = Status == StopwatchStatus::Paused ? 0 : countStarted;
}

void Stopwatch::Start()
{
    if ( countPaused )
    {
        llong delta = QueryPerformanceCounter() - countPaused;
        countStarted += delta;
        countLastTick += delta;
        countPaused = 0;
    }
}

void Stopwatch::Pause()
{
    if ( !countPaused )
    {
        countPaused = QueryPerformanceCounter();
    }
}

double Stopwatch::getTime() const
{
    return (double)((countPaused ? countPaused : QueryPerformanceCounter()) - countStarted)/(double)CountPerSecond;
}

double Stopwatch::Tick()
{
    llong now = countPaused ? countPaused : QueryPerformanceCounter();
    double elapsed = (double)(now - countLastTick)/(double)CountPerSecond;
    countLastTick = now;
    return elapsed;
}
