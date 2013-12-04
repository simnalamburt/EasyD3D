#pragma once
#include <minwindef.h>

namespace EasyD3D
{
    // Windows API QueryPerformanceFrequency()의 간편화된 형태
    LONGLONG QueryPerformanceFrequency();
    // Windows API QueryPerformanceCounter()의 간편화된 형태
    LONGLONG QueryPerformanceCounter();
}
