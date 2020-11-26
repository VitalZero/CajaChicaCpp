#ifndef PETTYCASHTEST_REBAR_H
#define PETTYCASHTEST_REBAR_H
#include <string>
#include <vector>
#include "IWin32Control.h"
#include "includes.h"

//DWORD size = (DWORD)SendMessage(toolBar, TB_GETBUTTONSIZE, 0, 0);

//rebar.Create(wnd);
//rebar.InsertBand(toolBar, size);

class Rebar : public IWin32Control
{
public:
    Rebar()
    {
        wnd = nullptr;
        type = CtlType::Rebar;
    }

    void Create(HWND parent)
    {
        if ( wnd )
        {
            throw std::runtime_error("Rebar already created.");
        }

        type = CtlType::Rebar;
        wndParent = parent;
        this->id = id;

        INITCOMMONCONTROLSEX icex = {};
        icex.dwSize = sizeof(icex);
        icex.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES;
        InitCommonControlsEx(&icex);

        wnd = CreateWindowEx(
                WS_EX_TOOLWINDOW,
                REBARCLASSNAME,
                "",
                WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
                RBS_VARHEIGHT | CCS_NODIVIDER | RBS_BANDBORDERS | WS_BORDER,
                0, 0, 0, 0,
                wndParent,
                nullptr,
                GetModuleHandle(nullptr),
                nullptr);

        if ( !wnd )
        {
            throw std::runtime_error("Rebar could not be created.");
        }
    }

    void InsertBand(HWND child, DWORD size)
    {
        if(!wnd)
        {
            throw std::runtime_error("Rebar must be created first.");
        }

        REBARBANDINFO rBand = { sizeof(REBARBANDINFO) };
        //rBand.cbSize = sizeof(REBARBANDINFO);
        rBand.fMask = RBBIM_STYLE | RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_SIZE | RBBIM_TEXT;
        rBand.fStyle = RBBS_CHILDEDGE | RBBS_GRIPPERALWAYS;
        rBand.hwndChild = child;
        rBand.lpText = nullptr;
        rBand.cyChild = HIWORD(size);
        rBand.cxMinChild = LOWORD(size) * 2;
        rBand.cyMinChild = HIWORD(size);
        rBand.cx = 0;

        SendMessage(wnd, RB_INSERTBAND, (WPARAM)-1, (LPARAM)&rBand);
    }

private:
    virtual std::string GetText() const override { return ""; }
    virtual void SetText(const std::string& text) override {}
};

#endif //PETTYCASHTEST_REBAR_H
