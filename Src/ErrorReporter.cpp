#include "pch.h"
#include "ErrorReporter.h"



namespace EasyD3D
{
    void Report(ErrorReportType ReportType, int ErrorCode, ErrorCodeType ErrorCodeType,
        const wchar* FileName, size_t LineNumber, const wchar* Function, const wchar* Command, const wchar* Message)
    {
        // Making error message
        std::wostringstream buffer(L"\n\n"
            L"==============================================================================\n");
        buffer << FileName << L'(' << LineNumber << L")\nFunction \t: " << Function << L"\nCommand \t: " << Command << L'\n';
        switch (ErrorCodeType)
        {
        case ErrorCodeType::HR:
            if (ErrorCode) buffer << L"HRESULT \t: " << _com_error(ErrorCode).ErrorMessage() << L" (0x" << ErrorCode << L")\n";
            break;
        case ErrorCodeType::Nonzero:
            if (ErrorCode) buffer << L"ErrorCode \t: " << ErrorCode << L'\n';
            break;
        case ErrorCodeType::False:
            buffer << L"Command has returned false(0)\n";
            break;
        }
        buffer << L"GetLastError() \t: " << GetLastError() << L'\n';
        if (Message)
        {
            size_t len = wcslen(Message);
            if (len > 0)
            {
                buffer << Message;
                if (Message[len - 1] != L'\n')
                    buffer << L'\n';
            }
        }
        buffer << L"------------------------------------------------------------------------------\n";

        // Present error message
        if (IsDebuggerPresent())
        {
            OutputDebugString(buffer.str().c_str());
            DebugBreak();
        }
        else
        {
            AllocConsole();
            AttachConsole(GetCurrentProcessId());
            FILE* dummy;
            _wfreopen_s(&dummy, L"CON", L"w", stdout);
            _wsetlocale(LC_ALL, L"");
            _putws(buffer.str().c_str());
            _wsystem(L"pause");
            FreeConsole();
        }

        // Terminate program if it's needed
        if (ReportType == ErrorReportType::Error)
        {
            ExitProcess(EXIT_FAILURE);
        }
    }
}
