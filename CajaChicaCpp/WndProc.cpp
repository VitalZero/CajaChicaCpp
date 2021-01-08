#include "WndProc.h"
#include "controller.h"


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    static Controller ctlr(hwnd);

    switch(msg)
    {
        case WM_CREATE:
            return ctlr.OnCreate(wparam, lparam);

        case WM_PAINT:
            return ctlr.OnPaint(wparam, lparam);

        case WM_NOTIFY:
        {
            NMHDR* nmhdr = (NMHDR*)lparam;
            switch(nmhdr->code)
            {
                case TBN_DROPDOWN:
                    return ctlr.OnTbnDropDown(wparam, lparam);
                    break;

                case NM_CUSTOMDRAW:
                    //return ctlr.OnNmCustomDraw(wparam, lparam);
                    break;
            }
        }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}
