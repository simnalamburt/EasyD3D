#pragma once

namespace EasyD3D
{
    // 클래스 Uncopyable. 이 클래스를 상속하는 모든 클래스는 복사연산이 불가능해진다.
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
