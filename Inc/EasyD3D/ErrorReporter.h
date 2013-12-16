#pragma once
#include "Type.h"



namespace EasyD3D
{
    enum class ErrorCodeType { HR, Nonzero, False, Custom };
    enum class ErrorReportType { Error, Warning };

    void Report(ErrorReportType ReportType, int ErrorCode, ErrorCodeType ErrorCodeType,
        const wchar* FileName, size_t LineNumber, const wchar* Function, const wchar* Command, const wchar* Message);
}



// Macro Bodies
#define _HR(x, report_type, msg) \
do \
{ \
    int __code = (int)(x); \
if (FAILED(__code)) \
    ::EasyD3D::Report(report_type, __code, ::EasyD3D::ErrorCodeType::HR, __FILEW__, __LINE__, __FUNCTIONW__, L#x, msg); \
} \
while (false)

#define _NONZERO(x, report_type, msg) \
do \
{ \
    int __code = (int)(x); \
if (__code) \
    ::EasyD3D::Report(report_type, __code, ::EasyD3D::ErrorCodeType::Nonzero, __FILEW__, __LINE__, __FUNCTIONW__, L#x, msg); \
} \
while (false)

#define _FALSE(x, report_type, msg) \
do \
{ \
    int __code = (int)(x); \
if (!(__code)) \
    ::EasyD3D::Report(report_type, __code, ::EasyD3D::ErrorCodeType::False, __FILEW__, __LINE__, __FUNCTIONW__, L#x, msg); \
} \
while (false)

#define _CUSTOM(x, report_type, msg) \
    ::EasyD3D::Report(report_type, 0, ::EasyD3D::ErrorCodeType::Custom, __FILEW__, __LINE__, __FUNCTIONW__, L"", msg);


// Interface Macros
#define HR_ERROR_MSG(x, msg) _HR(x, ErrorReportType::Error, msg)
#define NONZERO_ERROR_MSG(x, msg) _NONZERO(x, ErrorReportType::Error, msg)
#define FALSE_ERROR_MSG(x, msg) _FALSE(x, ErrorReportType::Error, msg)
#define ERROR_MSG(msg) _CUSTOM(0, ErrorReportType::Error, msg)

#ifdef _DEBUG
#define HR_WARNING_MSG(x, msg) _HR(x, ErrorReportType::Warning, msg)
#define NONZERO_WARNING_MSG(x, msg) _NONZERO(x, ErrorReportType::Warning, msg)
#define FALSE_WARNING_MSG(x, msg) _FALSE(x, ErrorReportType::Warning, msg)
#define WARNING_MSG(msg) _CUSTOM(0, ErrorReportType::Warning, msg)
#else
#define HR_WARNING_MSG(x, msg) (x)
#define NONZERO_WARNING_MSG(x, msg) (x)
#define FALSE_WARNING_MSG(x, msg) (x)
#define WARNING_MSG(msg)
#endif

#define HR_ERROR(x) HR_ERROR_MSG(x, nullptr)
#define HR_WARNING(x) HR_WARNING_MSG(x, nullptr)
#define NONZERO_ERROR(x) NONZERO_ERROR_MSG(x, nullptr)
#define NONZERO_WARNING(x) NONZERO_WARNING_MSG(x, nullptr)
#define FALSE_ERROR(x) FALSE_ERROR_MSG(x, nullptr)
#define FALSE_WARNING(x) FALSE_WARNING_MSG(x, nullptr)
