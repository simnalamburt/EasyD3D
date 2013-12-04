#include "pch.h"
#include "WindowDesc.h"



namespace EasyD3D
{
    size_t WindowDesc::Counter = 0;

    WindowDesc::WindowDesc()
    {
        instanceHandle = GetModuleHandle(nullptr);
        width = height = CW_USEDEFAULT;
        fullscreen = false;

        std::wostringstream stream;
        stream << L"EasyD3DWindow%u" << Counter++;
        className = stream.str();
    }
}
