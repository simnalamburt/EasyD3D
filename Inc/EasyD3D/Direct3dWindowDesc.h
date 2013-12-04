#pragma once
#include "WindowDesc.h"

namespace EasyD3D
{
    enum class MSAA { None, _2X, _4X, _8X, _16X };

    class Direct3dWindowDesc : public WindowDesc
    {
        friend class Direct3dWindow;

    protected:
        bool vSync = true;
        MSAA msaa = MSAA::_4X;

    public:
        // ������ Direct3d �������� ��������ȭ ���θ� ��������� �����Ѵ�.
        // �������� ��������� �⺻���� true �̴�.
        // VSync : ��������ȭ ����
        void VSyncStatus(bool VSync) { vSync = VSync; }

        // ������ Direct3d �������� ��Ƽ���ø� ǰ���� ��������� �����Ѵ�.
        // �������� �������, 4x MSAA �� �⺻������ �����ȴ�.
        // Msaa : ��Ƽ���ø�
        void MultisamplingQuality(MSAA MSAA) { msaa = MSAA; }
    };
}
