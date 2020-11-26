#ifndef PETTYCASHTEST_EDITBOX_H
#define PETTYCASHTEST_EDITBOX_H
#include <string>
#include <vector>
#include "IWin32Control.h"
#include "includes.h"

class Editbox : public IWin32Control
{
public:
    Editbox()
    {
        exStyle = WS_EX_CLIENTEDGE;
        type = CtlType::Edit;
    }
    Editbox(const Editbox&) = delete;
    Editbox& operator=(const Editbox&) = delete;

    explicit Editbox(DWORD style)
    {
        exStyle = WS_EX_CLIENTEDGE;
        type = CtlType::Edit;
        this->style = style;
    }

    explicit Editbox(HWND wndParent, int id)
    {
        exStyle = WS_EX_CLIENTEDGE;
        type = CtlType::Edit;
        this->wndParent = wndParent;
        this->id = id;
        wnd = GetDlgItem(wndParent, id);
        style = (int)GetWindowLong(wnd, GWL_STYLE);
    }

    virtual std::string GetText() const override
    {
        int len = GetLength();
        std::vector<char> tmp(len);

        if ( GetWindowText(wnd, tmp.data(), len) > 0 )
        {
            return std::string(tmp.data());
        }

        return std::string("0");
    }

    virtual void SetText(const std::string& text) override
    {
        SetWindowText(wnd, text.c_str());
    }

    void Create(HWND parent, int id, int x, int y, int width, int height)
    {
        if ( wnd )
        {
            throw std::runtime_error("Editbox already created.");
        }

        type = CtlType::Edit;
        wndParent = parent;
        this->id = id;

        wnd = CreateWindowEx(
                exStyle,
                "EDIT",
                "",
                style,
                x,
                y,
                width,
                height,
                wndParent,
                (HMENU)this->id,
                GetModuleHandle(nullptr),
                nullptr);

        if ( !wnd )
        {
            throw std::runtime_error("Editbox could not be created.");
        }
    }
};

#endif //PETTYCASHTEST_EDITBOX_H
