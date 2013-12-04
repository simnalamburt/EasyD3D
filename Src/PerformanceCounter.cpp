#include "pch.h"
#include "PerformanceCounter.h"
#include "ErrorReporter.h"



LONGLONG QueryPerformanceFrequency()
{
    LARGE_INTEGER freq;
    FALSE_ERROR(QueryPerformanceFrequency(&freq));
    return freq.QuadPart;
}

LONGLONG QueryPerformanceCounter()
{
    LARGE_INTEGER count;
    FALSE_ERROR(QueryPerformanceCounter(&count));
    return count.QuadPart;
}
