#pragma once
#include <functional>
#include "Uncopyable.h"

namespace EasyD3D
{
    class Raii : Uncopyable
    {
        std::function<void()> code;
    public:
        template <typename Func> Raii(Func&& Code) : code(std::move(Code)) { }
        ~Raii() { code(); }
    };
}

// Usage
//     RAII { /* Do something release in here */ };
//     RAII
//     {
//         CoUninitialize();
//         CoTaskMemFree(mem);
//     };
//
// RAII�� ����� ������ �������� ����Ǹ�, RAII �ȿ� ����� �ڵ尡 ����ȴ�
#define RAII_HELPER2(n) __raiiObject##n
#define RAII_HELPER1(n) ::EasyD3D::Raii RAII_HELPER2(n) = [&]()
#define RAII RAII_HELPER1(__COUNTER__)