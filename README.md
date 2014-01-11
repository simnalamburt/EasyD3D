EasyD3D
=======

Make Direct3D11 application fast and easy with **EasyD3D**!

You can easily include EasyD3D project into your solution by a single git command.

    git submodule add git://github.com/simnalamburt/EasyD3D.git EasyD3D

Add the following line as the path of new additional include directories

    $(SolutionDir)EasyD3D\Inc

---

See how easily EasyD3D let you make a new window!

    #include <Windows.h>
    #include <EasyD3D/EasyD3D.h>
    
    int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int Show)
    {
        EasyD3D::WindowDesc desc;
        desc.WindowTitle(L"Hello, World!");
        desc.WindowSize(800, 600);

        EasyD3D::GdiWindow window(desc);
        window.Run(Show);
    }

---

###### Note
The official remote repositories of this project is only the sites below:

1. [hyeon.me](http://git.hyeon.me/simnalamburt/snucse-13-frontpage)
1. [GitHub](https://github.com/simnalamburt/_13FrontPage)