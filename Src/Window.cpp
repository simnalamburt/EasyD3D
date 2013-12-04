#include "pch.h"
#include "Window.h"
#include "WindowDesc.h"
#include "ErrorReporter.h"
#include "RAII.h"

using std::wstring;



Window::Window(const WindowDesc& Description) :
instanceHandle(Description.instanceHandle), className(Description.className), fullscreen(Description.fullscreen), status(WindowStatus::Ready)
{
#pragma region Register a window class for subsequent use in calls to the CreateWindow
    WNDCLASSEX wcex = {};
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = wndProc_temp;
    wcex.lpszClassName = Description.className.c_str();
    wcex.hInstance = Description.instanceHandle;
    wcex.hIcon = wcex.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.cbWndExtra = sizeof(this);
    wcex.cbSize = sizeof(wcex);
    FALSE_ERROR(RegisterClassEx(&wcex));
#pragma endregion
#pragma region Create a window
    DWORD windowStyle = Description.fullscreen ? WS_POPUP : WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION | (Description.resizeable ? WS_SIZEBOX : 0);

    // Calculate desired size of the window
    RECT emptyRect = { 0, 0, Description.width, Description.height };
    FALSE_WARNING(AdjustWindowRect(&emptyRect, windowStyle, FALSE));

    // Create the window
    FALSE_ERROR(windowHandle = CreateWindow(Description.className.c_str(), Description.title.c_str(), windowStyle, CW_USEDEFAULT, CW_USEDEFAULT,
        emptyRect.right - emptyRect.left, emptyRect.bottom - emptyRect.top, nullptr, nullptr, Description.instanceHandle, this));
#pragma endregion
}

Window::~Window()
{
    if (IsWindow(windowHandle))
    {
        FALSE_WARNING(DestroyWindow(windowHandle));
        windowHandle = nullptr;
    }

    if (instanceHandle)
    {
        FALSE_WARNING(UnregisterClass(className.c_str(), instanceHandle));
    }
}

WPARAM Window::Run(int ShowCommand)
{
    if (status == WindowStatus::Ready)
    {
        status = WindowStatus::Running;
        RAII
        {
            status = WindowStatus::Finished;
        };

        ShowWindow(windowHandle, ShowCommand);
        FALSE_WARNING(SetForegroundWindow(windowHandle));
        FALSE_WARNING(SetFocus(windowHandle));

        MSG message = {};
        bool isIdleNeeded = true;
        while (true)
        {
            if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
            {
                if (message.message == WM_QUIT) return message.wParam;
                DispatchMessage(&message);
                continue;
            }

            if (isIdleNeeded && idle)
            {
                isIdleNeeded = idle(stopwatch.Tick());
            }
            else
            {
                isIdleNeeded = true;
                WaitMessage();
            }
        }
    }
    else
    {
        WARNING_MSG(L"Window::Run() 함수는 한 객체에 대해 2회 이상 호출될 수 없습니다.");
        return 0;
    }
}

// temporary window procedure of new window
LRESULT CALLBACK Window::wndProc_temp(HWND WindowHandle, UINT Message, WPARAM wParam, LPARAM lParam)
{
    // it change the window's WndProc when it set GWL_USERDATA to address of a Window object
    if (Message == WM_NCCREATE)
    {
        LPCREATESTRUCT CreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        SetWindowLongPtr(WindowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(CreateStruct->lpCreateParams));
        SetWindowLongPtr(WindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndProc));
        return wndProc(WindowHandle, Message, wParam, lParam);
    }

    return DefWindowProc(WindowHandle, Message, wParam, lParam);
}

// main window procedure
LRESULT CALLBACK Window::wndProc(HWND WindowHandle, UINT Message, WPARAM wParam, LPARAM lParam)
{
    Window* system = reinterpret_cast<Window*>(GetWindowLongPtr(WindowHandle, GWL_USERDATA));
    return system->messageHandler(WindowHandle, Message, wParam, lParam);
}

LRESULT Window::messageHandler(HWND WindowHandle, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
    case WM_PAINT:
        onDraw();
        return 0;
    case WM_ACTIVATE:
        if (LOWORD(wParam) != WA_INACTIVE)
        {
            stopwatch.Start();
            if (fullscreen) onEnterFullscreenMode();
        }
        else
        {
            stopwatch.Pause();
            if (fullscreen) onLeaveFullscreenMode();
        }
        return 0;
    case WM_SIZE:
        {
            ushort width = LOWORD(lParam);
            ushort height = HIWORD(lParam);
            onResize(width, height);
            if (resize) resize(width, height);
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(WindowHandle, Message, wParam, lParam);
    }
}

void Window::onEnterFullscreenMode()
{
    RECT windowRect;
    GetWindowRect(windowHandle, &windowRect);

    // change the display settings to full screen
    DEVMODE ScreenSettings = {};
    ScreenSettings.dmSize = sizeof(DEVMODE);
    ScreenSettings.dmPelsWidth = windowRect.right - windowRect.left;
    ScreenSettings.dmPelsHeight = windowRect.bottom - windowRect.top;
    ScreenSettings.dmBitsPerPel = 32;
    ScreenSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
    NONZERO_ERROR(ChangeDisplaySettings(&ScreenSettings, CDS_FULLSCREEN));
}

void Window::onLeaveFullscreenMode()
{
    NONZERO_WARNING(ChangeDisplaySettings(nullptr, 0));
}