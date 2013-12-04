#pragma once
#include <dxgi.h>
#include <d3d11.h>
#include "Window.h"

namespace EasyD3D
{
    class Direct3dWindowDesc;

    // Direct3D�� ȭ���� �������ϴ� Window�� �����Ѵ�
    class Direct3dWindow : public Window
    {
    private:
        ComPtr<ID3D11Device> device;
        ComPtr<ID3D11DeviceContext> deviceContext;
        ComPtr<IDXGISwapChain> swapChain;

        ComPtr<ID3D11RenderTargetView> renderTargetView;
        ComPtr<ID3D11Texture2D> depthStencilBuffer;
        ComPtr<ID3D11DepthStencilView> depthStencilView;

        const bool vSync;

        std::function<void(ComPtr<ID3D11DeviceContext>)> draw;

    public:
        // ���ο� Window Ŭ������ �ν��Ͻ��� �����Ѵ�.
        // Description : ������ ������ ���� ����
        Direct3dWindow(const Direct3dWindowDesc& Description);

        virtual ~Direct3dWindow();

        // �׸��⸦ ������ �ݹ��Լ��� ���Ѵ�
        // void Callback() : �� ������ �������� ȣ��� �ݹ��Լ�
        //     ComPtr<ID3D11Device> : �׸��⿡ ���� Direct3D Device Context
        void setDraw(const decltype(draw)& Callback) { draw = Callback; }
        // �׸��⸦ ������ �ݹ��Լ��� ���Ѵ�
        // void Callback() : �� ������ �������� ȣ��� �ݹ��Լ�
        //     ComPtr<ID3D11Device> : �׸��⿡ ���� Direct3D Device Context
        void setDraw(decltype(draw) && Callback) { draw = Callback; }

        // Direct3dWindow Ŭ������ ���� ������ Direct3D11 Device�� ��ȯ�Ѵ�
        // ��ȯ�� : Direct3D11 Device
        ComPtr<ID3D11Device> getDevice() const { return device; }

    protected:
        virtual void onDraw() override;
        virtual void onResize(ushort Width, ushort Height) override;
        virtual void onEnterFullscreenMode() override;
        virtual void onLeaveFullscreenMode() override;
    };
}
