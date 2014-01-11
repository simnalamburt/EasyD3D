EasyD3D
=======

Make Direct3D11 application fast and easy with **EasyD3D**!

You can easily include EasyD3D project into your solution by a single git command.

    git submodule add git://github.com/simnalamburt/EasyD3D.git EasyD3D

See how easily EasyD3D let you make a new window!

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
