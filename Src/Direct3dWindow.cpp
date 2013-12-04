#include "pch.h"
#include "Direct3dWindow.h"
#include "Direct3dWindowDesc.h"
#include "ErrorReporter.h"

using namespace std;



Direct3dWindow::Direct3dWindow(const Direct3dWindowDesc& Description) :
Window(Description), vSync(Description.vSync)
{
    ComPtr<IDXGIFactory> factory;
    ComPtr<IDXGIAdapter> adapter;
#pragma region Create a DirectX graphics interface factory, Enumerate the display adapters
    HR_ERROR(CreateDXGIFactory(IID_PPV_ARGS(&factory)));
    HR_ERROR(factory->EnumAdapters(0, &adapter));
#pragma endregion
#pragma region Create a device and device context those represent the display adapter
    uint deviceFlags = 0;
#ifdef _DEBUG
    deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL featureLevel;
    HR_ERROR(D3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, nullptr,
        deviceFlags, 0, 0, D3D11_SDK_VERSION, &device, &featureLevel, &deviceContext));
    FALSE_WARNING_MSG(featureLevel == D3D_FEATURE_LEVEL_11_0, L"Direct3D11 지원이 되지 못하고있습니다.");
#pragma endregion

    uint sampleCount, msaaQuality;
#pragma region Get the number of quality levels available during multisampling
    if (Description.msaa != MSAA::None)
    {
        switch (Description.msaa)
        {
        case MSAA::_2X: sampleCount = 2; break;
        case MSAA::_4X: sampleCount = 4; break;
        case MSAA::_8X: sampleCount = 8; break;
        case MSAA::_16X: sampleCount = 16; break;
        }
        HR_WARNING(device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, sampleCount, &msaaQuality));
        FALSE_WARNING_MSG(msaaQuality > 0, L"하드웨어가 사용자가 요청한 품질의 멀티샘플링을 지원하지 못하고있습니다.");
    }
    else
    {
        sampleCount = msaaQuality = 1;
    }
#pragma endregion
#pragma region Create a swap chain
    // Make a setting of desired display mode
    DXGI_MODE_DESC desiredMode = {};
    desiredMode.Width = Description.width;
    desiredMode.Height = Description.height;
    desiredMode.RefreshRate.Numerator = 60;
    desiredMode.RefreshRate.Denominator = 1;
    desiredMode.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desiredMode.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    desiredMode.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    // Enumerate the primary display ouput, find the display mode which most closely matches the desired display mode
    ComPtr<IDXGIOutput> output;
    HR_WARNING(adapter->EnumOutputs(0, &output));
    DXGI_MODE_DESC displayMode;
    HR_WARNING(output->FindClosestMatchingMode(&desiredMode, &displayMode, device));

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc = displayMode;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = getWindowHandle();
    swapChainDesc.SampleDesc.Count = sampleCount;
    swapChainDesc.SampleDesc.Quality = msaaQuality - 1;
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    // Create a swap chain
    HR_ERROR(factory->CreateSwapChain(device, &swapChainDesc, &swapChain));
#pragma endregion

#pragma region Create a render-target view, depth-stencil buffer and depth-stencil view. Then bind it to the OM
    // Create a render-target view
    ComPtr<ID3D11Texture2D> backBuffer;
    HR_ERROR(swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer)));
    HR_ERROR(device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView));

    // Create a depth-stencil buffer
    D3D11_TEXTURE2D_DESC depthStencilBufferDesc = {};
    depthStencilBufferDesc.Width = Description.width;
    depthStencilBufferDesc.Height = Description.height;
    depthStencilBufferDesc.MipLevels = 1;
    depthStencilBufferDesc.ArraySize = 1;
    depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilBufferDesc.SampleDesc.Count = sampleCount;
    depthStencilBufferDesc.SampleDesc.Quality = msaaQuality - 1;
    depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilBufferDesc.CPUAccessFlags = 0;
    depthStencilBufferDesc.MiscFlags = 0;
    HR_ERROR(device->CreateTexture2D(&depthStencilBufferDesc, nullptr, &depthStencilBuffer));

    // Create a depth-stencil view
    HR_ERROR(device->CreateDepthStencilView(depthStencilBuffer, nullptr, &depthStencilView));

    // Bind the render-target view and depth-stencil view to the output-merger
    ID3D11RenderTargetView* renderTargetViewList[] = { renderTargetView };
    deviceContext->OMSetRenderTargets(ARRAYSIZE(renderTargetViewList), renderTargetViewList, depthStencilView);
#pragma endregion

    // Bind the viewport to the rasterizer
    D3D11_VIEWPORT viewports[] =
    {
        { 0.0f, 0.0f, (float)Description.width, (float)Description.height, 0.0f, 1.0f }
    };
    deviceContext->RSSetViewports(ARRAYSIZE(viewports), viewports);

    // Make some miscellaneous settings
    HR_WARNING(factory->MakeWindowAssociation(getWindowHandle(), DXGI_MWA_NO_ALT_ENTER));
    HR_WARNING(factory->MakeWindowAssociation(getWindowHandle(), DXGI_MWA_NO_WINDOW_CHANGES));
}

Direct3dWindow::~Direct3dWindow()
{
    HR_WARNING(swapChain->SetFullscreenState(FALSE, nullptr));
}

void Direct3dWindow::onDraw()
{
    if (draw) draw(deviceContext);
    HR_WARNING(swapChain->Present(vSync ? 1 : 0, 0));
}

void Direct3dWindow::onResize(ushort Width, ushort Height)
{
    deviceContext->OMSetRenderTargets(0, nullptr, nullptr);

    // Release all outstanding references to the swap chain's buffers.
    renderTargetView.Release();

    // Preserve the existing buffer count and format. Automatically choose the width and height to match the client rect for HWNDs.
    HR_WARNING(swapChain->ResizeBuffers(0, Width, Height, DXGI_FORMAT_UNKNOWN, 0));

    // Get buffer and create a render-target-view.
    ComPtr<ID3D11Texture2D> buffer;
    HR_ERROR(swapChain->GetBuffer(0, IID_PPV_ARGS(&buffer)));
    HR_ERROR(device->CreateRenderTargetView(buffer, nullptr, &renderTargetView));

    ID3D11RenderTargetView* renderTargetViewList[] = { renderTargetView };
    deviceContext->OMSetRenderTargets(ARRAYSIZE(renderTargetViewList), renderTargetViewList, depthStencilView);

    // Bind a new viewport to the rasterizer
    D3D11_VIEWPORT viewports[] =
    {
        { 0.0f, 0.0f, (float)Width, (float)Height, 0.0f, 1.0f }
    };
    deviceContext->RSSetViewports(ARRAYSIZE(viewports), viewports);
}

void Direct3dWindow::onEnterFullscreenMode()
{
    // Detect if newly created full-screen swap chain isn't actually full screen. If not full screen, enable full screen again.
    ComPtr<IDXGIOutput> target;
    BOOL isFullscreen;
    HR_WARNING(swapChain->GetFullscreenState(&isFullscreen, &target));
    if (!isFullscreen) swapChain->SetFullscreenState(TRUE, nullptr);
}

void Direct3dWindow::onLeaveFullscreenMode()
{
    HR_WARNING(swapChain->SetFullscreenState(FALSE, nullptr));
}