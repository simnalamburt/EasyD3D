#pragma once

namespace EasyD3D
{
    // Ŭ���� Uncopyable. �� Ŭ������ ����ϴ� ��� Ŭ������ ���翬���� �Ұ���������.
    // Usage : class MyClass : Uncopyable { /* ... */ };
    class Uncopyable
    {
    protected:
        Uncopyable() = default;
        ~Uncopyable() = default;
        Uncopyable(const Uncopyable&) = delete;
        Uncopyable& operator=(const Uncopyable&) = delete;
    };
}
