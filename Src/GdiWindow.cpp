#include "pch.h"
#include "GdiWindow.h"



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
