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

    return 0;
}
```

##### *EasyD3D* is ...

* Modern C++
* Fully aware of C++11, C++14
* WinAPI wrapper
* OpenGL/Direct3D wrapper
* Windows Vista/7/8/8.1 compatible
* Visual Studio friendly

##### *EasyD3D* is not ...

* C
* [MFC](http://msdn.microsoft.com/en-us/library/d06h2x6e.aspx)
* [glut](http://freeglut.sourceforge.net), [glfw](http://glfw.org)
* [SDL](https://www.libsdl.org)

--------

### How to add *EasyD3D* into existing Visual Studio solution

1.  Checkout the source codes

    ```bash
    git submodule add --depth=1 git://github.com/simnalamburt/EasyD3D.git
    ```

1.  *Your Solution* → *Right Click* → `Add` → `Existing Project...` → Select `EasyD3D.vcxproj`

1.  *Your Project* → *Right Click* → `Properties`

    `Configuration:` → `All Configurations`

    1.  `Common Properties` → `References`

        `Add New Reference...` → Select `EasyD3D`

    1.  `Configuration Properties` → `C/C++` → `General`

        `Additional Include Directories` → `˅` → `<Edit...>`

        Add the following line

        ```
        $(SolutionDir)EasyD3D\Inc
        ```
