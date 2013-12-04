#pragma once

// windows 헤더
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <comdef.h>

// Direct3D11
#pragma comment ( lib, "dxgi.lib" )
#include <dxgi.h>
#pragma comment ( lib, "d3d11.lib" )
#include <d3d11.h>

// COM 헤더
#include <atlbase.h>

// C++ 헤더
#include <string>
#include <sstream>
#include <memory>
#include <functional>
