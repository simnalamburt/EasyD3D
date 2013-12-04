#include "pch.h"
#include "GdiWindow.h"



namespace EasyD3D
{
    void GdiWindow::onDraw()
    {
        if (draw)
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(getWindowHandle(), &ps);
            draw(hdc);
            EndPaint(getWindowHandle(), &ps);
        }
    }
}
