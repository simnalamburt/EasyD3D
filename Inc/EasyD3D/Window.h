#pragma once
#include <minwindef.h>
#include <string>
#include <functional>
#include "Stopwatch.h"

namespace EasyD3D
{
    class WindowDesc;

    enum class WindowStatus { Ready, Running, Finished };

    // �� �����츦 �����ϴ� Ŭ�����̴�. WinAPI �Լ����� �����ϴ� Ŭ�����̴�.
    class Window
    {
    private:
        const HINSTANCE instanceHandle;
        const std::wstring className;
        const bool fullscreen;

        HWND windowHandle;
        WindowStatus status;
        Stopwatch stopwatch;
        std::function<bool(double)> idle;
        std::function<void(ushort, ushort)> resize;

    public:
        // ���ο� Window Ŭ������ �ν��Ͻ��� �����Ѵ�.
        // Description : ������ ������ ���� ����
        Window(const WindowDesc& Description);

        virtual ~Window();

        // �� ���޽ð����� ȣ��� �ݹ��Լ��� ���Ѵ�.
        // bool Callback(double Elapsed) : �� ���޽ð����� ȣ��� �ݹ�
        //     Elapsed : ������ �־��� ȣ��κ��� �帥 �ð�
        //     ��ȯ�� : true to receive more idle processing time; false if no more idle time is needed.
        void setIdle(const decltype(idle)& Callback) { idle = Callback; }
        // �� ���޽ð����� ȣ��� �ݹ��Լ��� ���Ѵ�.
        // bool Callback(double Elapsed) : �� ���޽ð����� ȣ��� �ݹ�
        //     Elapsed : ������ �־��� ȣ��κ��� �帥 �ð�
        //     ��ȯ�� : true to receive more idle processing time; false if no more idle time is needed.
        void setIdle(decltype(idle) && Callback) { idle = Callback; }

        // �������� ũ�Ⱑ ���Ҷ����� ȣ��� �ݹ��� �����Ѵ�.
        // void Callback(ushort Width, ushort Height) : �������� ũ�Ⱑ ���Ҷ����� ȣ��� �ݹ�
        //     Width : �������� �� ���α���
        //     Height : �������� �� ���α���
        void setResize(const decltype(resize)& Callback) { resize = Callback; }
        // �������� ũ�Ⱑ ���Ҷ����� ȣ��� �ݹ��� �����Ѵ�.
        // void Callback(ushort Width, ushort Height) : �������� ũ�Ⱑ ���Ҷ����� ȣ��� �ݹ�
        //     Width : �������� �� ���α���
        //     Height : �������� �� ���α���
        void setResize(decltype(resize) && Callback) { resize = Callback; }

        // ������� ������ �ν��Ͻ��� ȭ��� ǥ���ϰ�, �޼��������� �����Ѵ�.
        // Run() �Լ��� �� ��ü�� ���� 2ȸ �̻� ȣ��� �� ����.
        // ShowCommand : �����찡 �����Ǿ����� �������� ����(�ʱ�ȭ����, ��üȭ��, ��..)
        // ��ȯ�� : The exit code given in the PostQuitMessage function
        WPARAM Run(int ShowCommand);

        // �����찡 ���ӵǾ��ִ� �ν��Ͻ� �ڵ�(HINSTANCE)�� ��ȯ�Ѵ�.
        // ��ȯ�� : �ν��Ͻ� �ڵ�(HINSTANCE)
        HINSTANCE getInstanceHandle() const { return instanceHandle; }
        // �������� Ŭ���� �̸��� ��ȯ�Ѵ�.
        // ��ȯ�� : Ŭ���� �̸�
        const std::wstring& getClassName() const { return className; }
        // �������� ��üȭ�� ���θ� ��ȯ�Ѵ�.
        // ��ȯ�� : ��üȭ�� ����
        bool getFullscreenStatus() const { return fullscreen; }
        // Window Ŭ������ ���� ������ ������ �ڵ�(HWND)�� ��ȯ�Ѵ�.
        // ��ȯ�� : ������ �ڵ�(HWND)
        HWND getWindowHandle() const { return windowHandle; }
        // ���� Window Ŭ������ ������������, ����������, ������ �������� ���θ� ��ȯ�Ѵ�.
        // ��ȯ�� : WindowStatus ��
        WindowStatus getStatus() const { return status; }

    private:
        static LRESULT CALLBACK wndProc_temp(HWND, UINT, WPARAM, LPARAM);
        static LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);
        LRESULT messageHandler(HWND, UINT, WPARAM, LPARAM);

    protected:
        // WM_PAINT �޼����� ���� �� ����� �����̴�. ���������Լ�.
        virtual void onDraw() = 0;
        // WM_SIZE �޼����� ���� �� ����� �����̴�. �������̵�� �� �ִ�.
        virtual void onResize(ushort Width, ushort Height) { }
        // �����찡 ��üȭ����� �� �� ����� �����̴�. �������̵�� �� �ִ�.
        virtual void onEnterFullscreenMode();
        // �����찡 ��üȭ���忡�� �������� �� ����� �����̴�. �������̵�� �� �ִ�.
        virtual void onLeaveFullscreenMode();
    };
}
