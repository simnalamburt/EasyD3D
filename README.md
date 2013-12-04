EasyD3D
=======

Make Direct3D11 application fast and easily with **EasyD3D**!

    #include <Windows.h>
    #include <EasyD3D/EasyD3D.h>
    
    int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int Show)
    {
        EasyD3D::WindowDesc desc;
        desc.WindowTitle(L"Hello, World!");
        desc.WindowSize(800, 600);

        EasyD3D::Window window(desc);
        window.Run(Show);
    }
