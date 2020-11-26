#ifndef PETTYCASHTEST_LABEL_H
#define PETTYCASHTEST_LABEL_H
#include <string>
#include <vector>
#include "IWin32Control.h"
#include "includes.h"

class Label : public IWin32Control
{
public:
    Label()
    {
        type = CtlType::Static;
    }
    Label(const Label&) = delete;
    Label& operator=(const Label&) = delete;

    explicit Label(DWORD style)
    {
        type = CtlType::Static;
        this->style = style;
    }

    explicit Label(HWND wndParent, int id)
    {
        type = CtlType::Static;
        this->wndParent = wndParent;
        this->id = id;
        wnd = GetDlgItem(wndParent, id);
        style = (int)GetWindowLong(wnd, GWL_STYLE);
    }

    size_t GetLength() const
    {
        return GetWindowTextLength(wnd) + 1;
    }

    std::string GetText() const
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
            throw std::runtime_error("Label already created.");
        }

        type = CtlType::Static;
        wndParent = parent;
        this->id = id;

        wnd = CreateWindowEx(
                exStyle,
                "STATIC",
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
            throw std::runtime_error("Label could not be created.");
        }
    }
};
#endif //PETTYCASHTEST_LABEL_H
