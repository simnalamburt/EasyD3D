#pragma once
#include <minwindef.h>

namespace EasyD3D
{
    // Windows API QueryPerformanceFrequency()�� ����ȭ�� ����
    LONGLONG QueryPerformanceFrequency();
    // Windows API QueryPerformanceCounter()�� ����ȭ�� ����
    LONGLONG QueryPerformanceCounter();
}
