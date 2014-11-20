EasyD3D
========

Make Windows application fast and easy with *EasyD3D*

```cpp
#include <Windows.h>
#include <EasyD3D/EasyD3D.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int Show)
{
    EasyD3D::WindowDesc desc;
    desc.WindowTitle(L"Hello, World!");
    desc.WindowSize(800, 600);

    EasyD3D::GdiWindow window(desc);
    window.Run(Show);
}
```

You can easily include *EasyD3D* into your Visual Studio solution with a single git command

```bash
git submodule add git://github.com/simnalamburt/EasyD3D.git EasyD3D
```

Add the following line to the `Additional Include Directories` in `C/C++` config

```
$(SolutionDir)EasyD3D\Inc
```

--------

*EasyD3D* is ...

* Modern C++
* Fully aware of C++11, C++14
* WinAPI wrapper
* OpenGL/Direct3D wrapper
* Windows Vista/7/8/8.1 compatible
* Visual Studio friendly

*EasyD3D* is not ...

* C
* [MFC](http://msdn.microsoft.com/en-us/library/d06h2x6e.aspx)
* [glut](/dcnieho/FreeGLUT), [glfw](/glfw/glfw)
* [SDL](https://www.libsdl.org)
