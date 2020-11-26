#include "includes.h"
#include "WndProc.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    const char* CLASS_NAME = "PettyCashClass";
    const char* WINDOW_NAME = "Petty Cash";

    WNDCLASSEX wc = {};
    wc.hInstance = GetModuleHandle(nullptr);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = CLASS_NAME;
    wc.lpfnWndProc = WndProc;
    wc.cbSize = sizeof(wc);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(nullptr, "No se pudo registrar la aplicacion", "Error!", MB_ICONERROR);
        return -1;
    }

    HWND hwnd = CreateWindow(
            CLASS_NAME,
            WINDOW_NAME,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            1031,
            585,
            nullptr,
            nullptr,
            GetModuleHandle(nullptr),
            nullptr);

    if(!hwnd)
    {
        MessageBox(nullptr, "No se pudo crear la ventana", "Error!", MB_ICONERROR);
        return -1;
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg = {};
    BOOL bRet;

    while((bRet = GetMessage(&msg, nullptr, 0, 0)) != 0)
    {
        if(bRet == -1)
        {}
        else
        {
            if(!IsDialogMessage(hwnd, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    return msg.wParam;
}

