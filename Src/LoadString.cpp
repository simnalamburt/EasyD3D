#include "pch.h"
#include "ErrorReporter.h"



std::string LoadStringA(_In_opt_ HINSTANCE InstanceHandle, _In_ UINT uID)
{
    const char* src; int len;
    FALSE_ERROR( len = LoadStringA(InstanceHandle, uID, reinterpret_cast<LPSTR>( &src ), 0) );
    return std::string(src, len);
}

std::wstring LoadStringW(_In_opt_ HINSTANCE InstanceHandle, _In_ UINT uID)
{
    const wchar* src; int len;
    FALSE_ERROR( len = LoadStringW(InstanceHandle, uID, reinterpret_cast<LPWSTR>( &src ), 0) );
    return std::wstring(src, len);
}
