#pragma once
#include <minwindef.h>
#include <string>
#include "Type.h"

namespace EasyD3D
{
    // Window Ŭ������ �����ϱ����� ���������� �����ִ� ���� Ŭ�����Դϴ�.
    class WindowDesc
    {
        friend class Window;
        static size_t Counter;

    protected:
        HINSTANCE instanceHandle;
        uint width;
        uint height;
        std::wstring title;
        std::wstring className;
        bool fullscreen;
        bool resizeable;

    public:
        // ���ο� WindowDesc ��ü�� �����մϴ�.
        WindowDesc();

        virtual ~WindowDesc() { }

        // ��������� ������ �����찡 ���ӵ� ���α׷��� �ν��Ͻ� �ڵ��� �������ݴϴ�.
        // �ν��Ͻ� �ڵ��� ���������� �ʾ������� �⺻����, WindowDesc ��ü�� ������ �������� �ν��Ͻ��Դϴ�.
        // InstanceHandle : ������ �����찡 ���ӵ� ���α׷��� �ν��Ͻ�
        void Instance(HINSTANCE InstanceHandle) { instanceHandle = InstanceHandle; }

        // ��������� ������ �������� ���� �� ���� ���̸� �������ݴϴ�.
        // ���α��̿� ���α����� �������� �ʾ������� �⺻����, CW_USEDEFAULT �Դϴ�.
        // Width : ������ �������� �ʱ� ���α���
        // Height : ������ �������� �ʱ� ���α���
        void WindowSize(uint Width, uint Height) { width = Width; height = Height; }

        // ������ �������� Ÿ��Ʋ�� �� ���ڿ��� ��������� �����մϴ�.
        // ���������� ������, Ÿ��Ʋ�� �ƹ� ���ڿ��� ǥ�õ��� �ʽ��ϴ�.
        // Title : ������ �������� Ÿ��Ʋ ���ڿ�
        template <typename String> void WindowTitle(const String& Title) { title = Title; }
        // ������ �������� Ÿ��Ʋ�� �� ���ڿ��� ��������� �����մϴ�.
        // ���������� ������, Ÿ��Ʋ�� �ƹ� ���ڿ��� ǥ�õ��� �ʽ��ϴ�.
        // Title : ������ �������� Ÿ��Ʋ ���ڿ�
        template <typename String> void WindowTitle(String&& Title) { title = Title; }

        // ������ �������� Ŭ���� �̸��� ��������� �����մϴ�.
        // ClassName : ������ �������� Ŭ���� �̸�
        template <typename String> void ClassName(const String& ClassName) { className = ClassName; }
        // ������ �������� Ŭ���� �̸��� ��������� �����մϴ�.
        // ClassName : ������ �������� Ŭ���� �̸�
        template <typename String> void ClassName(String&& ClassName) { className = ClassName; }

        // ������ �������� ��üȭ�� ���θ� ��������� �����մϴ�.
        // �������� �������, �⺻������ â���� �����˴ϴ�.
        // FullScreen : ��üȭ�� ����
        void FullScreenState(bool Fullscreen) { fullscreen = Fullscreen; }

        // ����ڰ� �������� ũ�⸦ �ٲ� �� �ִ��� ���θ� ��������� �����մϴ�.
        void Resizeable(bool Resizeable) { resizeable = Resizeable; }
    };
}
