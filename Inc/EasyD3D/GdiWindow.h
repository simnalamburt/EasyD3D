#pragma once
#include "Window.h"

namespace EasyD3D
{
    // GDI ��ü�� �׸��� �׸� �� �ִ� Window�� �����Ѵ�
    class GdiWindow : public Window
    {
    private:
        std::function<void(HDC)> draw;

    public:
        // ���ο� GdiWindow Ŭ������ �ν��Ͻ��� �����Ѵ�.
        // Description : ������ ������ ���� ����
        GdiWindow(const WindowDesc& Description) : Window(Description) { }

        // �׸��⸦ ������ �ݹ��Լ��� ���Ѵ�
        // void Callback(HDC hdc) : �� ������ �������� ȣ��� �ݹ��Լ�
        //     hdc : �������� ���� DC �ڵ�
        void setDraw(const decltype(draw)& Callback) { draw = Callback; }
        // �׸��⸦ ������ �ݹ��Լ��� ���Ѵ�
        // void Callback(HDC hdc) : �� ������ �������� ȣ��� �ݹ��Լ�
        //     hdc : �������� ���� DC �ڵ�
        void setDraw(decltype(draw) && Callback) { draw = Callback; }

    protected:
        virtual void onDraw() override;
    };
}
